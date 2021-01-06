#include "BitInputStream.hpp"

using namespace std; 
/*
 * Programming langauges have input and output streams so we don't need to worry
 * about bytewise buffers" 
 */

void BitInputStream::fill(){
    this->buffer = this->in.get(); 
    this->buffer_index = 0; 

}

int BitInputStream::readBit(){
    //need to shift then and with 1 
    if(this->buffer_index == 8){
        this->fill(); 
        //need to check if there is a negative one here 
        if(this->buffer == -1){
            return -1;
        }
    }

    bool actual = (this->buffer >> (7-this->buffer_index)) & 1;
    this->buffer_index++; 
    return actual; 
}

int BitInputStream::readInt(){
    int actual = 0; 
    for(int i = 0; i <= 3; i++){
        this->fill(); 
        if(this->buffer == -1){
            return -1; //means end of file
            //dont think this actually matters
        }
        if(i != 0){
            actual = actual << 8; 
        }
        actual = actual | this->buffer; 
        this->buffer_index = 8; 
    }
    return actual; 
}
