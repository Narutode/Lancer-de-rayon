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
#include "Matrice.h"
#include "Light.h"

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
        std::string operation, wordkey, outputname, widthString, heightString, ombreString, materiau;
        std::stringstream ss(line);
        ss >> operation  >> wordkey >> outputname >> widthString >> heightString >> ombreString >> materiau;
        int width = std::stoi(widthString);
        int height = std::stoi(heightString);
        bool ombre = std::stoi(ombreString);


        scene.performOperation(operation,width,height,outputname,ombre,materiau);
    }
    Matrix v = Matrix();
    Matrix w = Matrix();
    Matrix z = v*w;

// Afficher les valeurs de la matrice v
    std::cout << "Matrix v:" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << v(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix z:" << std::endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << z(i, j) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Excécution fini" << std::endl;
    return 0;
}

