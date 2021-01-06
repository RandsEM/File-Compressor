#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP
#include <iostream>
using namespace std;

class BitInputStream {
    private:
        istream& in;      // the input stream to use
        char buffer;      // one byte buffer of bits
        int buffer_index; // current index in buffer

    public:
        BitInputStream(istream& s) : in(s), buffer(0), buffer_index(8) {}
        int readBit();
        int readInt();
        void fill(); 
};
#endif
