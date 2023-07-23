//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_CYLINDER_H
#define UNTITLED_CYLINDER_H
#include "Object.h"
#include <vector>

class Cylinder: public Object {
    public:
    Cylinder() {
        // Ajouter ici les points du cylindre
        // Exemple : points.push_back(Point3D(x, y, z));

        // Initialiser minimumY et maximumY avec la première coordonnée Y
        if (!points.empty()) {
            minimumY = points[0][1];
            maximumY = points[0][1];
        }

        // Parcourir tous les points pour trouver les valeurs minimale et maximale de Y
        for (const Point3D& point : points) {
            if (point[1] < minimumY) {
                minimumY = point[1];
            }
            if (point[1] > maximumY) {
                maximumY = point[1];
            }
        }
    }
        bool intersect(const Ray& ray, Point3D& impact) const {
            Ray r = globalToLocal(ray).normalized();

            float a = r.vector.x * r.vector.x + r.vector.z * r.vector.z;
            float b = 2 * (r.vector.x * r.origin.x + r.vector.z * r.origin.z);
            float c = r.origin.x * r.origin.x + r.origin.z * r.origin.z - 1.0;
            float delta = b * b - 4 * a * c;

            if (delta < 0)
                return false;

            float t;
            if (delta < 0.0001) {
                t = -b / (2 * a);
            } else {
                t = (-b - std::sqrt(delta)) / (2 * a);
                if (t < 0)
                    t = (-b + std::sqrt(delta)) / (2 * a);
            }
            if (t < 0)
                return false;

            Point3D p = r.origin +  r.vector * t ;
            impact = localToGlobal(p);
            return true;
        }
    Material getMaterial(const Point3D& p) const{
        Material material;
        material.ka = Color(0, 0, 0);  // Composante ambiante
        material.kd = Color(0.0, 1.0, 0.0);  // Composante diffuse (vert)
        material.ks = Color(0.0, 0.0, 0.0);  // Composante spéculaire (noir)
        material.shininess = 0.0;  // Exposant de brillance (aucun effet de spécularité)
        return material;
    }
    Ray getNormal(const Point3D& p, const Point3D& o) const {
        Point3D lp = globalToLocal(p);
        Point3D lo = globalToLocal(o);
        Point3D temp=lo - Point3D(0, lo[1], 0);
        Vector3D normal = Vector3D(temp.x,temp.y,temp.z);
        if (normal.norm() > 1)
            return localToGlobal(Ray(lp, Vector3D(lp[0], 0, lp[2]))).normalized();

        return localToGlobal(Ray(lp, Vector3D(-lp[0], 0, -lp[2]))).normalized();
    }
    Point3D getTextureCoordinates(const Point3D& p) const {
        // Transformation des coordonnées locales en coordonnées cylindriques
        float radius = std::sqrt(p[0] * p[0] + p[2] * p[2]);
        float angle = std::atan2(p[2], p[0]);

        // Conversion de l'angle en coordonnées de texture (dans l'intervalle [0, 1])
        float texX = (angle + M_PI) / (2 * M_PI);
        float texY = (p[1] - minimumY) / (maximumY - minimumY);

        // Vérifier que les coordonnées de texture sont dans l'intervalle [0, 1]
        if (texX < 0.0f) texX = 0.0f;
        if (texX > 1.0f) texX = 1.0f;
        if (texY < 0.0f) texY = 0.0f;
        if (texY > 1.0f) texY = 1.0f;

        return Point3D(texX, texY, 0.0f);
    }
private:
    std::vector<Point3D> points;
    float minimumY;
    float maximumY;
};


#endif //UNTITLED_CYLINDER_H
