#include<iostream>
#include<string>
#include "BitArray.hpp"

int main() {
    string hex; 
    cin >> hex;
    BitArray bits;
    bits.setHex(hex);

    string hex2; 
    cin >> hex2;
    BitArray bits2;
    bits2.setHex(hex2);



    bits.bitXor(bits2);

    cout << bits.getHex();
}
