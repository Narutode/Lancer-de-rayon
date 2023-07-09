#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "scene.h"

int main() {
    scene scene;
    std::ifstream infile("process.txt");
    if (!infile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier process.txt" << std::endl;
        return 1;
    }
    std::string line;

    unsigned char *img;
    if(img == nullptr) {
        printf("img null");
    }
    while (std::getline(infile, line)) {
        std::string operation, wordkey, outputname, widthString, heightString, ombre, materiau;
        std::stringstream ss(line);
        ss >> operation  >> wordkey >> outputname >> widthString >> heightString >> ombre >> materiau;
        int width = std::stoi(widthString);
        int height = std::stoi(heightString);
        scene.performOperation(operation,width,height,outputname,ombre,materiau);
    }

    std::cout << "Excécution fini" << std::endl;
    return 0;
}

