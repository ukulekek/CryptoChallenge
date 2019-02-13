#include<string>
#include<cmath>
#include<vector>

using namespace std;

class BitArray {
    public:

        //--------------------Set Value---------------------

        void setHex(const std::string& hexStr) {
            for(const char hex : hexStr) {
                int decValue = hexCharToInt(hex);
                vector<bool> hexVec = hexIntToBin(decValue);
                bits.insert(bits.end(), hexVec.begin(), hexVec.end());
            }
        }


        //---------------------Getter-----------------------
        vector<bool> getBits() const {
            return bits;
        }

        //--------------String Representations--------------

        string getBase64() const {
            vector<vector<bool>> arrays = separateBitsBy(6);
            string base64 = "";
            size_t sizeCnt = 0;
            for (const vector<bool>& array: arrays) {
                base64 += getBaseChar(toInt(array)); 
                sizeCnt += 6;
            }
            if (sizeCnt >= bits.size() ) {
                if (sizeCnt - bits.size() == 2) base64 += "=";
                if (sizeCnt - bits.size() == 4) base64 += "==";
            }
            base64 += "\n";
            return base64;
        }

        string getHex() {
            vector<vector<bool>> arrays = separateBitsBy(4);
            string hex = "";
            size_t sizeCnt = 0;
            for (const vector<bool>& array: arrays) {
                hex += getHexChar(toInt(array)); 
                sizeCnt += 6;
            }
            hex += "\n";
            return hex;
        }

        string getBin() const {
            string bin;
            for(bool bit : bits) {
                if (bit) bin += "1";
                else bin += "0";
            }
            bin = bin + "\n";
            return bin;
        }


        //------------------Operations----------------------

        void bitXor(BitArray otherBits) {
            for (size_t i = 0; i < bits.size(); i++) {
                bits[i] = (bits[i] != otherBits.getBits()[i]);
            }
        }

    private:
        //Big-endian representation 0x57 = 0101 0111 
        vector<bool> bits;

        //Separate the bits array to bits arrays with size of `size`
        vector<vector<bool>> separateBitsBy(int size) const {
            vector<vector<bool>> arrays;
            size_t i = 0;
            while (true) {

                //Making six bits array for returning a Base64 char
                vector<bool> array;
                for (int j = 0; j < size; j++) array.push_back(bits[i+j]);
                arrays.push_back(array);

                //End of cycle
                if ((i + size) >= bits.size() -1) break;
                i += size;

            }
            return arrays;

        }

        //Returns integer represantation of bits array
        int toInt(vector<bool> bits) const {
            int base = 0;
            for (size_t i = 0; i < bits.size(); i++) {
                base = base << 1;
                if (bits[i]) base += 1;
            }
            return base;
        }

        static char getHexChar(int index) {
            string hexLiterals = "0123456789abcdef";
                return hexLiterals[index];

        }

        static char getBaseChar(int index) {
            string baseLiterals = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
                return baseLiterals[index];

        }

        static int hexCharToInt(const char hex) {
            string hexLiterals = "0123456789abcdef";
            if (hexLiterals.find(tolower(hex)) == string::npos) {
                cerr << "String is not hex\n";
                exit(1);
            }
            return hexLiterals.find(tolower(hex));
        }

        static vector<bool> hexIntToBin(int decValue) {
            int counter = 0;
            vector<bool> hexBits;
            while (decValue > 1) {
                    if (decValue % 2 == 0) {
                        hexBits.insert(hexBits.begin(), false);
                        counter++;
                        decValue = decValue / 2;
                    } else {
                        hexBits.insert(hexBits.begin(), true);
                        counter++;
                        decValue = (decValue - 1)/ 2;
                    }
            } 
            if (decValue == 1) {
                hexBits.insert(hexBits.begin(), true);
                counter++;
            }
            while (counter < 4) {
                hexBits.insert(hexBits.begin(), false);
                counter++;
            }
            return hexBits;
        }
};
