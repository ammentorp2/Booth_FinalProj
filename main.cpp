#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;


void convertToBinary(int n, bool binaryNum[]) {
    int i = 0;
    while (n > 0) {


        // storing remainder in binary array
        binaryNum[i] = n & 1;
        n = n >> 1;
        i++;
    }
}

//We can change this return type/have way to store array
//change return type into the bool array

//TODO change the return bool array which contains all the char binary:)
//TODO add null terminator(which is value 0) at the end of the array
//TODO can pass one parameter int size by reference to know the size of binary array?
// (8 bit for null terminator also included)
void textToBinary(char *theFile, int &size) {
    fstream file(theFile);

    if (file.is_open()) {
        char ch;
        int val;
        bool binaryNum[8];   //7 bits (ascii goes up to 127)
        while (file.get(ch)) {
            //cout << ch;
            val = (int) ch;
            cout << val << " ";
            cout << endl;
            convertToBinary(val, binaryNum);

            for (int i = 7; i >= 0; i--)
                cout << binaryNum[i] << " ";
            cout << endl;

        }
    } else {
        //crash program
        assert(false);
    }

    file.close();
}

//TODO hide_binary function
//it take the bool bit and hide to the last bit
//of c
int hide_binary(bool bit, int c);


int main(int argc, char *argv[]) {
    //Test
    //Test push
    //Just quit if only 1 arg
    if (argc == 1)
        assert(false);

     cout<<"hello world!";
    //this is a encryption program

    //input file: image template, image destination, message file
    char *image_src_name = argv[1];
    char *image_dest_name = argv[2];
    char *text_name = argv[3];

    ofstream image_s(image_temp_name);
    ifstream image_d(image_dest_name);
    ifstream text(text_name);

    //read in the size
    string type;
    int width, height, coor_size;
    image_s >> type >> width >> height >> color_size;

    //destination image should have same type, width, height
    //and color size
    image_d << type << width << height << color_size;


    //convert the text into binary
    int text_size = 0;
    bool *message = textToBinary(text_name, text_size);

    //TODO calculate whether image is large enough to contain the message
    //if not abort the program or print the error message

    //get the RGB and hide the message binary
    //into the pixel
    int color, index_text = 0;
    for (int i = 0; i < height * 3; i++) {
        for (int j = 0; j < width * 3; j++) {
            image_src_name >> color;

            //if not reach the end of the message
            if (index_text < text_size) {
                int new_color = hide_binary(message[index_text], color);
                image_d << new_color << " ";
                index_text++;
            } else {
                //if after reaching the end of message
                image_d << color << " ";
            }
        }
        image_d << endl;
    }

    image_d.close();
    image_s.close();
    text.close();

    return 0;
}
