#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;


void convertToBinary(int n, bool binaryNum []){
    int i = 0;
    while (n > 0) {

        // storing remainder in binary array
        binaryNum[i] = n & 1;
        n = n >> 1;
        i++;
    }
}

//We can change this return type/have way to store array
void textToBinary(char * theFile){
    fstream file(theFile);

    if(file.is_open()){
        char ch;
        int val;
        bool binaryNum[8];   //7 bits (ascii goes up to 127)
        while(file.get(ch)) {
            //cout << ch;
            val = (int) ch;
            cout << val << " ";
            cout << endl;
            convertToBinary(val, binaryNum);
            for (int i = 7; i >= 0; i--)
                cout << binaryNum[i] << " ";
            cout << endl;
        }
    } else{
        //crash program
        assert(false);
    }

    file.close();
}


int main(int argc, char *argv[]) {
    //Test
    //Test push
    //Just quit if only 1 arg
    if(argc == 1)
        assert(false);

    //TODO change which arg is the file
    textToBinary(argv[1]);


    return 0;
}
