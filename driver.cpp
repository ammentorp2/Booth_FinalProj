#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;


void convertToBinary(int n, int* arr, int size) {
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        arr[i] = n & 1;
        n = n >> 1;
        i++;
    }
}

//We can change this return type/have way to store array
//change return type into the bool array

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

    if(argc == 4){
        //TODO logic for inserting message in file
        //argv[1] source image
        //argv[2] output image
        //argv[3] txt file of stuff

        FILE *file = fopen(argv[1],"rb");
        int *num;
        if (file != NULL) {
            int val;

            //TODO read in type and other attributes not in binary


            //sorry for the foreign c code
            //This the code for reading in the rgb values
            while(fread(&val,sizeof(int),1,file) != 0) {
                printf("Val is %d\n",val);
                //Sorry had to make it int
                num = new int[8];
                //init to zero
                for(int i = 0; i < 8; i++)
                    num[i] = 0;
                convertToBinary(val,num,8);

                for(int i = 7; i >= 0; i--){
                    cout << num[i] << " ";
                }
                cout << endl;
            }
            fclose(file);
        } else {
            //crash program
            assert(false);
        }

    }
    else if(argc == 3){
        //TODO logic for decrypting file
        //argv[1] image
        //argv[2] result .txt file (We make one here)
    }

    //Testing the file reader
    //the rb is read and binary



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


     cout<<"hello world!";
    //this is a encryption program

    //input file: image template, image destination, message file
    char *image_src_name = argv[1];
    char *image_dest_name = argv[2];
    char *text_name = argv[3];

    ofstream image_s(image_src_name);
    ifstream image_d(image_dest_name);
    ifstream text(text_name);

    //read in the size
    string type;
    int width, height, color_size;
    image_d >> type >> width >> height >> color_size;

    //destination image should have same type, width, height
    //and color size
    image_s << type << width << height << color_size;


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
