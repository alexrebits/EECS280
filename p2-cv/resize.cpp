#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "Image.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char **argv) {
    if(argc != 4 && argc !=5){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    ifstream fin;
    fin.open(argv[1]);
    if(!fin.is_open()){
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }
        Image img;
        Image_init(&img,fin);

    ofstream fout;
    fout.open(argv[2]);
    if(!fout.is_open()){
        cout << "Error opening file: " << argv[2] << endl;
        return 1;
    }
    int w = stoi(argv[3]);


    int h = Image_height(&img);
    if(argc == 5){
        h = stoi(argv[4]);
    }
    
    if(!(w>0 && w <= Image_width(&img) && h >0 && h <= Image_height(&img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    seam_carve(&img, w,h);
    Image_print(&img,fout);
    
    fout.close();
    return 0;
}