#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

bool get_bit(char color) {
    if (color & 1)
        return true;
    return false;
}

//message is bool array extract from image
//fileName is the text file name
char convert_to_character(bool *character, int size, ifstream &src) {

    for (int i = 0; i < size && !src.eof(); i++) {
        char color;
        src.read(&color, sizeof(char));

        character[i] = get_bit(color);
    }

    char c = 0;
    //convert the bool array into a char
    for (int i = size - 1; i >= 0; i--) {
        int index_bool = size - i - 1;
        c = c << 1;
        if (character[index_bool])
            c + 1;

    }

    return c;

}


//fix the little endian issue
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
    //Test
    //Test push
    //Just quit if only 1 arg

    if (argc == 1)
        assert(false);

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

        //logic for inserting message in file
        string type;
        int width, length, c_size;
        src >> type >> width >> length >> c_size;
        //also write to the ofstream
        dest << type << width << length << c_size;

        //TODO calculate whether the image file is large enough to hide the message
        //find the size of message file(int bit)
        //if it is larger than width*length*3, then print error message exit the program


        bool *num;
        char color, new_color;
        if (!src.eof()) {
            //since one byte per each R, G, B
            char val;

            //I used fstream to skip the formating at the out of the loop
//            //read in type and other attributes not in binary
//            string type;
//            int width, length,c_size;



            //sorry for the foreign c code
            //This the code for reading in the rgb values
            //I used binary read for fstream instead sorry :)
            while (message.read(&val, sizeof(char))) {
//                printf("Val is %d\n",val);
                //Sorry had to make it int




                num = new bool[8];

                //init to zero
                for (int i = 0; i < 8; i++)
                    num[i] = 0;
                convertToBinary(val, num, 8);


                //cout<<"\nthe char read in is: "<<val;
//                cout<<"\tthe binary is: ";
//                for(int i=0;i<8;i++)
//                    cout<<num[i]<<" ";


                for (int i = 0; i < 8; i++) {
                    //assume the src file will not exhausted
                    src.read(&color, sizeof(char));
                    new_color = hide_binary(num[i], color);


                    //write to the dest file
                    dest.write(&new_color, sizeof(char));

                    //testing read in
//                    cout<<"\n original color is : "<<(unsigned short)color;
//                    cout<<"\tbit is: "<<num[i]<<"\t new color is"<<(unsigned short)new_color<<endl;


                }


                //fix memory leak
                delete[]num;
            }

            /*
                 * terminate sign input to the dest image
                 */

            for (int i = 0; i < 8; i++) {
                new_color = hide_binary(false, color);
                dest.write(&new_color, sizeof(char));
            }

            //if the source file didn't reach the end
            //keep read and write color into dest file
            while (!src.eof()) {
                src.read(&color, sizeof(char));
                dest.write(&color, sizeof(char));
            }


            src.close();
            dest.close();
            message.close();
        } else {
            //crash program
            assert(false);
        }

    } else if (argc == 3) {

        ifstream src(argv[1], ios::binary);
        ofstream text_file(argv[2], ios::binary);


        //skip format info
        string type;
        int width, length, c_size;
        src >> type >> width >> length >> c_size;


        bool terminate = false;
        while (!src.eof() && !terminate) {


            //initialing character array
            bool *character = new bool[8];
            for (int i = 0; i < 8; i++) {
                character[i] = 0;
            }

            char val = convert_to_character(character, 8, src);
            if (var == 0)
                terminate = true;

            text_file.write(&val, sizeof(char));


            delete[]character;
        }

        src.close();
        text_file.close();


    }

    //Testing the file reader
    //the rb is read and binary





    return 0;
}
