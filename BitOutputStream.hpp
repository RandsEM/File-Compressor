#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP
#include <iostream>
using namespace std;

class BitOutputStream {
    private:
        ostream& out;     // the output stream to use
        char buffer;      // one byte buffer of bits
        int buffer_index; // current index in buffer     

    public:
        BitOutputStream(ostream& s) : out(s), buffer(0), buffer_index(0) {}
        void writeBit(int bit);
        void writeInt(int i);
        void flush();
};
#endif 
