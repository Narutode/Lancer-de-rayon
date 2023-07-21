/*#include <iostream>
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
int main() {

    Scene scene(Color(0.1,0.1,0.1),Color(0.2,0.2,0.2));
    Camera camera(45);

    std::ifstream infile("process.txt");
    if (!infile.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier process.txt" << std::endl;
        return 1;
    }
    std::string line;

    while (std::getline(infile, line)) {
        std::string operation, wordkey, temp1, temp2, temp3, temp4, temp5,temp6,temp7;
        std::stringstream ss(line);
        ss >> operation  >> wordkey >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6 >> temp7;
        if (operation == "plan") {
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Plan plan;
            plan.translate(x, y, z);
            plan.rotateX(rotatex);
            plan.rotateY(rotatey);
            plan.rotateZ(rotatez);
            plan.scale(scale);
            scene.addObject(&plan);
        }
        else if (operation == "cube") {
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Cube cube;
            cube.translate(x, y, z);
            cube.rotateX(rotatex);
            cube.rotateY(rotatey);
            cube.rotateZ(rotatez);
            cube.scale(scale);
            scene.addObject(&cube);

        }
        else if (operation == "carre") {
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Square carre;
            carre.translate(x, y, z);
            carre.rotateX(rotatex);
            carre.rotateY(rotatey);
            carre.rotateZ(rotatez);
            carre.scale(scale);
            scene.addObject(&carre);
        }
        else if (operation == "triangle") {
            // Code pour l'opération "triangle"
        }
        else if (operation == "sphere") {
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Sphere sphere;
            sphere.translate(x, y, z);
            sphere.rotateX(rotatex);
            sphere.rotateY(rotatey);
            sphere.rotateZ(rotatez);
            sphere.scale(scale);
            scene.addObject(&sphere);
        }
        else if (operation == "cylindre") {
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Cylinder cylinder;
            cylinder.translate(x, y, z);
            cylinder.rotateX(rotatex);
            cylinder.rotateY(rotatey);
            cylinder.rotateZ(rotatez);
            cylinder.scale(scale);
            scene.addObject(&cylinder);
        }
        else if (operation == "cone") {
            // Code pour l'opération "cone"
        }
        else if (operation == "camera"){
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            //camera.translate(1, 1, 100);
            camera.translate(x,y,z);
            camera.rotateX(rotatex);
            camera.rotateY(rotatey);
            camera.rotateZ(rotatez);
            camera.scale(scale);
        }
        else if (operation == "light"){
            int x = std::stoi(temp1);
            int y = std::stoi(temp2);
            int z = std::stoi(temp3);
            int rotatex = std::stoi(temp4);
            int rotatey = std::stoi(temp5);
            int rotatez = std::stoi(temp6);
            float scale = std::stof(temp7);
            Color d(1.0,1.0,1.0);
            Color s(1.0,1.0,1.0);
            Light light(d,s);
            light.translate(x,y,z);
            light.rotateX(rotatex);
            light.rotateY(rotatey);
            light.rotateZ(rotatez);
            light.scale(scale);
            scene.addLight(&light);
        }
        else if(operation == "create"){
            std::string outputname = temp1;
            int width = std::stoi(temp2);
            int height = std::stoi(temp3);
            std::vector<unsigned char> image(width * height * 3);
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

                        // Récupération de la couleur de l'impact
                        Color color = getImpactColor(ray, *intersectedObject, impact, scene);

                        // Coloriage du pixel avec la couleur de l'impact
                        image[(y * width + x) * 3] = static_cast<unsigned char>(color[0] * 255);     // Composante rouge
                        image[(y * width + x) * 3 + 1] = static_cast<unsigned char>(color[1] * 255); // Composante verte
                        image[(y * width + x) * 3 + 2] = static_cast<unsigned char>(color[2] * 255); // Composante bleue

                    }
                    else if(scene.closer_intersected(scene.getLight(0)->getRayFromLight(impact),impact)){

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
        else {
            std::cerr << "Opération non prise en charge : " << operation << std::endl;
        }

    }

    std::cout << "Execution terminee" << std::endl;
    return 0;
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

    return c;
}

/*Cube cube;
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


camera in 1 1 100 0 0 0 1
light in 10 10 -5 0 0 0 1
cube in -2 0 -2 45 45 45 0.5
carre in 2 2 0 0 0 0 1
cylindre in 4 4 0 0 0 0 1
sphere in 1 -2 0 0 0 0 1
sphere in -3 -2 0 0 0 0 1
create in rendu.jpg 1000 1000


 cube in rendu.jpg 1000 1000 1 ligne
*/