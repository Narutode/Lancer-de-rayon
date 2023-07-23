#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "scene.h"
#include "Matrice.h"
#include "Light.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"
#include "Plan.h"
#include "Camera.h"
#include "Sphere.h"
#include "Square.h"
#include "Cube.h"
#include "Cylinder.h"
#include "scene.h"

void performOperation(const std::string& operation, int width, int height, const std::string& outputname, bool ombre, const std::string& materiau);

Color getImpactColor(const Ray& ray, const Object& obj, const Point3D& impact, const Scene& scene);

void loadTextureImage(const std::string& texture);

std::vector<unsigned char> textureImage;
int textureWidth = 512;
int textureHeight = 512;

int main() {
    std::ifstream infile("process.txt");
    if (!infile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier process.txt" << std::endl;
        return 1;
    }
    std::string line;

    while (std::getline(infile, line)) {
        std::string operation, wordkey, outputname, widthString, heightString, ombreString, materiau;
        std::stringstream ss(line);
        ss >> operation  >> wordkey >> outputname >> widthString >> heightString >> ombreString >> materiau;
        int width = std::stoi(widthString);
        int height = std::stoi(heightString);
        bool ombre = std::stoi(ombreString);
        if(materiau=="danier"){
            std::string textureFilename = "texturedanier.png";
            loadTextureImage(textureFilename);
        }
        if(materiau=="ligne"){
            std::string textureFilename = "textureligne.png";
            loadTextureImage(textureFilename);
        }
        if(materiau=="texture"){
            std::string textureFilename = "texture_output.jpg";
            loadTextureImage(textureFilename);
        }
        performOperation(operation, width, height, outputname, ombre, materiau);
    }

    std::cout << "Execution terminee" << std::endl;
    return 0;
}

void performOperation(const std::string& operation, int width, int height, const std::string& outputname, bool ombre, const std::string& materiau) {
    std::vector<unsigned char> image(width * height * 3);
    Camera camera(45);
    camera.translate(1.1, 1.1, 100);
    Scene scene(Color(0.1,0.1,0.1),Color(0.2,0.2,0.2));
    Color d(1.0,1.0,1.0);
    Color s(1.0,1.0,1.0);
    Light light(d,s);



    if (operation == "exemple1") {
        light.translate(10,10,-5);
        Cube cube;
        cube.translate(-2, 0, -2);
        cube.rotateZ(45);
        cube.rotateX(45);
        cube.rotateY(45);
        cube.scale(0.5f);
        scene.addObject(&cube);
        Square carre;
        carre.translate(2, 2, 0);
        scene.addObject(&carre);

        Cylinder cylinder;
        cylinder.translate(4, 4, 0);
        scene.addObject(&cylinder);
        Sphere sphere;
        sphere.translate(1, -2, 0);
        scene.addObject(&sphere);
        Sphere sphere2;
        sphere2.translate(-3, -2, 0);
        scene.addObject(&sphere2);
    }
    else if (operation == "exemple2") {
        light.translate(-10,-10,-5);
        Cube cube;
        cube.translate(-2, 0, -2);
        cube.rotateZ(45);
        cube.rotateX(45);
        cube.rotateY(45);
        cube.scale(0.5f);
        scene.addObject(&cube);
        Square carre;
        carre.translate(2, 2, 0);
        scene.addObject(&carre);

        Cylinder cylinder;
        cylinder.translate(4, 4, 0);
        scene.addObject(&cylinder);
        Sphere sphere;
        sphere.translate(1, -2, 0);
        scene.addObject(&sphere);
        Sphere sphere2;
        sphere2.translate(-3, -2, 0);
        scene.addObject(&sphere2);
    }
    else if (operation == "exemple3") {
        light.translate(-10,10,-5);
        Cube cube;
        cube.translate(-2, 0, -2);
        cube.rotateZ(45);
        cube.rotateX(45);
        cube.rotateY(45);
        cube.scale(1.0f);
        scene.addObject(&cube);
        Square carre;
        carre.translate(2, 2, 0);
        scene.addObject(&carre);

        Cylinder cylinder;
        cylinder.translate(4, 4, 0);
        scene.addObject(&cylinder);
        Sphere sphere;
        sphere.translate(1, -2, 0);
        sphere.rotateX(90);
        scene.addObject(&sphere);
        Sphere sphere2;
        sphere2.translate(-3, -2, 0);
        scene.addObject(&sphere2);
    }
    else if (operation == "exemple4") {
        Plan plan;
        plan.translate(10, 10, 10);
        scene.addObject(&plan);

    }
    else {
        std::cerr << "Opération non prise en charge : " << operation << std::endl;
        return;
    }

    scene.addLight(&light);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calcul des coordonnées du pixel dans l'espace de projection
            float px = 2.0f * (x + 0.5f) / width - 1.0f;
            float py = 2.0f * (y + 0.5f) / height - 1.0f;

            // Création du rayon
            Ray ray = camera.getRay(px, py);

            // Intersection avec les objets de la scène
            Point3D impact(0.0f, 0.0f, 0.0f);
            Object* intersectedObject = scene.closer_intersected(ray, impact);

            if (intersectedObject != nullptr) {

                if(ombre){
                    if(materiau == "none"){
                        // Récupération de la couleur de l'impact
                        Color color = getImpactColor(ray, *intersectedObject, impact, scene);

                        // Coloriage du pixel avec la couleur de l'impact
                        image[(y * width + x) * 3] = static_cast<unsigned char>(color[0] * 255);     // Composante rouge
                        image[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color[1] * 255); // Composante verte
                        image[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color[2] * 255); // Composante bleue
                    }
                    else{
                        Point3D textureCoords = intersectedObject->getTextureCoordinates(impact);

                        // Vérifier que les coordonnées de texture sont dans l'intervalle [0, 1]
                        float texX = textureCoords[0];
                        float texY = textureCoords[1];

                        if (texX < 0.0f) texX = 0.0f;
                        if (texX > 1.0f) texX = 1.0f;
                        if (texY < 0.0f) texY = 0.0f;
                        if (texY > 1.0f) texY = 1.0f;

                        // Conversion des coordonnées de texture en coordonnées de pixel
                        int pixelX = static_cast<int>(texX * (textureWidth - 1));
                        int pixelY = static_cast<int>(texY * (textureHeight - 1));

                        // Récupération de la couleur de l'impact depuis la texture
                        unsigned char r = textureImage[(pixelY * textureWidth + pixelX) * 3];
                        unsigned char g = textureImage[(pixelY * textureWidth + pixelX) * 3 + 1];
                        unsigned char b = textureImage[(pixelY * textureWidth + pixelX) * 3 + 2];

                        // Application de la couleur du pixel comme couleur diffuse du matériau
                        image[(y * width + x) * 3] = r;
                        image[(y * width + x) * 3 + 1] = g;
                        image[(y * width + x) * 3 + 2] = b;
                    }

                }
                else{
                    Color color = intersectedObject->getMaterial(impact).kd;
                    // Coloriage du pixel avec la couleur de l'impact
                    image[(y * width + x) * 3] = static_cast<unsigned char>(color[0] * 255);     // Composante rouge
                    image[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color[1] * 255); // Composante verte
                    image[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color[2] * 255); // Composante bleue
                }
            }
            else {
                // Coloriage du pixel avec la couleur d'arrière-plan
                Color background = scene.getBackground();
                image[(y * width + x) * 3] = static_cast<unsigned char>(background[0] * 255);     // Composante rouge
                image[(y * width + x) * 3 + 1] = static_cast<unsigned char>(background[1] * 255); // Composante verte
                image[(y * width + x) * 3 + 2] = static_cast<unsigned char>(background[2] * 255); // Composante bleue
            }
        }
    }

    // Enregistrement de l'image au format JPG
    stbi_write_jpg(outputname.c_str(), width, height, 3, image.data(), 100);
}

void loadTextureImage(const std::string& textureFilename) {
    int channels;
    unsigned char* image = stbi_load(textureFilename.c_str(), &textureWidth, &textureHeight, &channels, 0);
    if (!image) {
        std::cerr << "Erreur lors du chargement de l'image de texture : " << textureFilename << std::endl;
        exit(1);
    }
    textureImage.assign(image, image + textureWidth * textureHeight * channels);
    stbi_image_free(image);
}

Color getImpactColor(const Ray& ray, const Object& obj, const Point3D& impact, const Scene& scene) {
    Material m = obj.getMaterial(impact);
    Ray normal = obj.getNormal(impact, ray.origin);
    Color c = m.ka.mul(scene.getAmbient());
    for (int l = 0; l < scene.nbLights(); l++) {
        const Light* light = scene.getLight(l);
        Vector3D lv = light->getVectorToLight(impact);
        float alpha = lv.dot(normal.vector);
        if (alpha > 0)
            c += (light->id) * m.kd * alpha;

        Vector3D rm = (normal.vector * lv.dot(normal.vector) * 2) - lv;

        float beta = -rm.dot(ray.vector);
        if (beta > 0)
            c += (light->is) * m.ks * pow(beta, m.shininess);
    }
    if(c.r>1 ) c.r=1;
    if(c.g>1 ) c.g=1;
    if(c.b>1 ) c.b=1;
    if(c.b<0 ) c.b=0;
    if(c.g<0 ) c.g=0;
    if(c.r<0 ) c.r=0;
    return c;
}

