#include<iostream> 
#include<vector>
#include<fstream>
#include"HCTree.hpp"
using namespace std;


int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Error Usage. First command line argument should be file path of file to be compressed, second should be filepath of compressed file" << endl; 
        return 0; 
    }

    //create vector of size 256 all zeros
    vector<int> storage(256,0); 


    //open the compressed file 
    ifstream compressed(argv[1], std::ifstream::in);
    BitInputStream bis(compressed); 

    //read from the header in order to build the tree
    int current = bis.readInt(); 
    for(int i = 0; i <= 255; i++){
        storage[i] = current; 
        //dont read int again 
        if(i != 255){
            current = bis.readInt(); 
        }
    }




    HCTree htree;
    htree.build(storage); 


    //open the file to write to to get back original 
    ofstream outFile(argv[2], ios::binary);
    BitOutputStream bos(outFile);

    //count the number of characters to read 
    int total = 0; 
    for(int i = 0; i < storage.size(); i++){
        total = total + storage[i];
    }


    //looks good so far


    //call decode count amount of times 
    for(int i = 0; i < total; i++){
        int returned = htree.decode(bis);// gives me the ascii value of the character
        unsigned char casted = (unsigned char)returned; 
        for(int i = 7; i >= 0; i--){
            unsigned char workingWith = casted; 
            workingWith = workingWith >> i;
            workingWith = workingWith & 1;
            bos.writeBit(workingWith);
        }
    }


    compressed.close();
    outFile.close();

}
