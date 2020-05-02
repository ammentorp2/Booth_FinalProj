/**
 * Booth Final Project
 *
 * This project can either encrypt a message in a txt file,
 * or decrypt a message depending on what the user specifies
 */
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

/**
 * get_bit
 *
 * Function gets if the last bit is 1
 *
 * @param color
 * @return
 */
bool get_bit(char color) {
    if (color & 1)
        return true;
    return false;
}

/**
 * This function gets the number of bytes in the file
 * @param fileName
 * @return
 */
int getFileSize(char *fileName)
{
    ifstream file(fileName, ifstream::in | ifstream::binary);

    if(!file.is_open())
    {
        return -1;
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

//message is bool array extract from image
//fileName is the text file name
/**
 * This function loads an array with 1s or 0s
 * @param character
 * @param size
 * @param src
 * @return
 */
char convert_to_character(bool *character, int size, ifstream &src) {

    //cout<<"\nconverting 8 character...\n";
    for (int i = 0; i < size && !src.eof(); i++) {
        char color;
        src.read(&color, sizeof(char));
        //cout<<"the color is: "<<color<<"\tthe last bit is: "<<get_bit(color)<<endl;
        character[i] = get_bit(color);
    }

    char c = 0;
    //convert the bool array into a char
    for (int i = 0; i<size; i++) {

        //cout<<"the bit is "<<(int)character[i];
        c = c << 1;
        if (character[i])
            c=c+1;
        //cout<<"\tc now is: "<<(int)c<<endl;

    }
    //cout<<"\nthe char is: "<<c<<endl;

    return c;

}


//fix the little endian issue
/**
 * This function converts a number n to is binary representation
 * @param n
 * @param arr
 * @param size
 */
void convertToBinary(char n, bool *arr, int size) {
    int i = size - 1;
    while (n > 0) {
        // storing remainder in binary array
        arr[i] = n & 1;
        n = n >> 1;
        i--;
    }
}

//We can change this return type/have way to store array
//change return type into the bool array

//it take the bool bit and hide to the last bit
//of c
/**
 * This function hides a bit
 * @param bit
 * @param c
 * @return
 */
char hide_binary(bool bit, char c) {
    if (c % 2 == 0) {
        if (bit) {
            return c + 1;
        }
    } else {
        if (!bit) {
            return c - 1;
        }
    }

    return c;
}


int main(int argc, char *argv[]) {

    //Just quit if only 1 arg (the exe itself)
    if (argc == 1)
        assert(false);

    //Encrypt
    if (argc == 4) {

        /*
         * input file order
         * argv[1] : src image file
         * argv[2] :  dest image file(empty image src)
         * argv[3]: message text file
         */

        ifstream src(argv[1], ios::binary);
        ofstream dest(argv[2], ios::binary);
        ifstream message(argv[3], ios::binary);

        //Get file data
        string type;
        int width, length, c_size;
        src >> type >> width >> length >> c_size;

        //test if the image is large enough
        int bit_message = (getFileSize(argv[3])+1)*8;
        if(width*length*3<bit_message){
            cout<<"error: image is not large enough!!!";
            return 1;
        }

        //cout<<"bit message is: "<<bit_message<<"\tpixel number: "<<width*length*3<<endl;
        //also write to the ofstream
        //write file data to output file
        dest << type<<endl << width<<" " << length<<endl<< c_size;

        //find the size of message file(int bit)
        //if it is larger than width*length*3, then print error message exit the program


        bool *num;
        char color, new_color;
        if (!src.eof()) {
            //since one byte per each R, G, B
            char val;

            //I used fstream to skip the formating at the out of the loop

            //This the code for reading in the rgb values
            //I used binary read for fstream instead sorry :)
            while (message.read(&val, sizeof(char))) {
//                printf("Val is %d\n",val);

                num = new bool[8];

                //init to zero
                for (int i = 0; i < 8; i++)
                    num[i] = 0;
                //Convert to binary
                convertToBinary(val, num, 8);


                //For each bit
                for (int i = 0; i < 8; i++) {
                    //assume the src file will not exhausted
                    src.read(&color, sizeof(char));
                    //Hide bit
                    new_color = hide_binary(num[i], color);


                    //write to the dest file
                    dest.write(&new_color, sizeof(char));

                }
                //fix memory leak, clear array
                delete[]num;
            }

            //terminate sign input to the dest image
            for (int i = 0; i < 8; i++) {
                //Get new color
                new_color = hide_binary(0, color);
                //cout<<"origin color is: "<<(int)color<<"\tcolor is: "<<(int)new_color<<endl;
                //Write encrypted data
                dest.write(&new_color, sizeof(char));
            }

            //if the source file didn't reach the end
            //keep read and write color into dest file
            while (!src.eof()) {
                //Left over bits
                src.read(&color, sizeof(char));
                dest.write(&color, sizeof(char));
            }


            //Close files
            src.close();
            dest.close();
            message.close();
        } else {
            //crash program
            assert(false);
        }

    }
    //Decrypt the message
    else if (argc == 3) {

        //Src file
        ifstream src(argv[1], ios::binary);
        //Output file of secret message
        ofstream text_file(argv[2], ios::binary);


        //skip format info
        string type;
        //File data
        int width, length, c_size;
        src >> type >> width >> length >> c_size;


        bool terminate = false;
        //While can process file AND not at end of text
        while (!src.eof() && !terminate) {


            //initialing character array
            bool *character = new bool[8];
            //Init to false
            for (int i = 0; i < 8; i++) {
                character[i] = 0;
            }

            //Get character
            char val = convert_to_character(character, 8, src);
            //End of text
            if (val == 0)
                terminate = true;

            //Write to text file
            text_file.write(&val, sizeof(char));


            //clear array
            delete[]character;
        }

        //close files
        src.close();
        text_file.close();


    }

    return 0;
}
