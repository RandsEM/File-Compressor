#include<iostream> 
#include<vector>
#include<fstream>
#include"HCTree.hpp"
using namespace std;

/*
 * Main takes two command line arguments, the file to be compressed, the and compressed file
 */
int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "Error Usage. First command line argument should be file path of file to be compressed, second should be filepath of compressed file" << endl; 
        return 0; 
    }

    vector<int> storage(256, 0); //initlize vector size 256 of all zeros

    ifstream unCompFile(argv[1], std::ifstream::in);

    //track the frequencies
    int current = unCompFile.get(); 
    while(current != -1){
        storage[current] += 1;
        current = unCompFile.get();
    }
    unCompFile.close();

    //build the tree
    HCTree htree;
    htree.build(storage);

    ofstream compFile(argv[2], ios::binary);
    BitOutputStream bos(compFile); 

    /*
     * Write header
     */
    for(int i = 0; i < storage.size(); i++){
        bos.writeInt(storage[i]); 
    }

    //open the uncompressed file again
    ifstream unCompFile2(argv[1], std::ifstream::in);

    /*
     * Starting writing
     */
    current = unCompFile2.get();
    while(current != -1){
        htree.encode(current, bos); 
        current = unCompFile2.get(); 
    }

    //flush one last time here

    bos.flush();


    /*
     * Close shit  
     */
    unCompFile2.close(); 
    compFile.close();  

}
