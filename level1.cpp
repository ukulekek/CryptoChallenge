#include<iostream>
#include<string>
#include "BitArray.hpp"

int main() {
    string hex; 
    cin >> hex;

    BitArray bit;
    bit.setHex(hex);

    cout << bit.getBase64();
}
