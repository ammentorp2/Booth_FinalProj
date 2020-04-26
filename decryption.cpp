#include <iostream>
#include <fstream>

using namespace std;

//TODO:get_bit
bool get_bit(int color);

//message is bool array extract from image
//fileName is the text file name
//TODO:convert_to_text
void convert_to_text(bool *message, int size, char *fileName);

//it will extract the last bit of the color and put into the array
//size will be the bool size
//I recommand using vector to push the bit and then convert to bool array
// when reach the null terminator(which is 8 '0') means end the text
//TODO:extract_bit
bool* extract_bit(char *image_name,int size);


int main(int argc, char **argv){

    char * image_name =argv[1];
    char * text_name = argv[2];

    ifstream image(image_name);
    ofstream  text_file(text_name);

    return 0;


}
