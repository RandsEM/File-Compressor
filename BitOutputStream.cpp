#include "BitOutputStream.hpp"

/*
 * out  is the output stream
 * buffer is 1 byte char buffer 
 * buffer_index is the current index of the buffer
 */

using namespace std; 

/*
 * Function will automatically flush once 
 * the buffer is 8 bits full 
 */
void BitOutputStream::writeBit(int bit){
    this->buffer = this->buffer << 1; 
    this->buffer += bit;
    this->buffer_index += 1; 
    if(this->buffer_index == 8){
        this->flush(); 
    }
}


void BitOutputStream::writeInt(int i){
    int ander = 255; 
    for(int j = 24; j >= 0; j-=8){
        this->buffer = ((i>>j) & ander);
        this->buffer_index = 8; 
        this->flush(); 
    }
}

void BitOutputStream::flush(){
    if(this->buffer_index == 8){
        this->out.put(this->buffer); 
        this->buffer = 0; 
        this->buffer_index = 0; 
    }else{
        this->buffer = this->buffer << (8-this->buffer_index); 
        this->out.put(this->buffer); 
        this->buffer = 0; 
        this->buffer_index = 0;
    }
    /*if(this->buffer_index == 7){
        this->out.put(this->buffer); 
    }else{
        int fakeZeros = 8-this->buffer_index+1; 
        this->out.put(this->buffer); 
        this->out.put(fakeZeros); 
    }
    this->buffer_index = 0; 
    */
}




