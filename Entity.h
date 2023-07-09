//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_ENTITY_H
#define UNTITLED_ENTITY_H

#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"

class Entity {
public:
    Entity() : position(Point3D(0, 0, 0)), rotation(Vector3D(0, 0, 0)), scale_factor(1.0) {}

    void translate(float x, float y, float z) {
        position.x += x;
        position.y += y;
        position.z += z;
    }

    void rotateX(float deg) {
        rotation.x += deg;
    }

    void rotateY(float deg) {
        rotation.y += deg;
    }

    void rotateZ(float deg) {
        rotation.z += deg;
    }

    void scale(float factor) {
        scale_factor *= factor;
    }

    Point3D localToGlobal(const Point3D& local_point) const {
        // Appliquer les transformations locales pour convertir le point du référentiel local au référentiel global
        Point3D transformed_point = local_point;

        // Effectuer la translation
        transformed_point = transformed_point + position;


        // Effectuer les rotations
        // Rotation sur l'axe X
        float rad_x = rotation.x * M_PI / 180.0f;
        float sin_x = sin(rad_x);
        float cos_x = cos(rad_x);
        float temp_y = transformed_point.y * cos_x - transformed_point.z * sin_x;
        float temp_z = transformed_point.y * sin_x + transformed_point.z * cos_x;
        transformed_point.y = temp_y;
        transformed_point.z = temp_z;

        // Rotation sur l'axe Y
        float rad_y = rotation.y * M_PI / 180.0f;
        float sin_y = sin(rad_y);
        float cos_y = cos(rad_y);
        float temp_z2 = transformed_point.z * cos_y - transformed_point.x * sin_y;
        float temp_x = transformed_point.z * sin_y + transformed_point.x * cos_y;
        transformed_point.z = temp_z2;
        transformed_point.x = temp_x;

        // Rotation sur l'axe Z
        float rad_z = rotation.z * M_PI / 180.0f;
        float sin_z = sin(rad_z);
        float cos_z = cos(rad_z);
        float temp_x2 = transformed_point.x * cos_z - transformed_point.y * sin_z;
        float temp_y2 = transformed_point.x * sin_z + transformed_point.y * cos_z;
        transformed_point.x = temp_x2;
        transformed_point.y = temp_y2;

        // Effectuer le redimensionnement
        transformed_point.x *= scale_factor;
        transformed_point.y *= scale_factor;
        transformed_point.z *= scale_factor;

        return transformed_point;
    }

    Vector3D globalToLocal(const Vector3D& global_vector) const {
        // Appliquer les transformations inverses pour convertir le vecteur du référentiel global au référentiel local
        Vector3D transformed_vector = global_vector;

        // Effectuer le redimensionnement inverse
        transformed_vector = transformed_vector / scale_factor;

        // Effectuer les rotations inverses
        // Rotation inverse sur l'axe Z
        float rad_z = -rotation.z * M_PI / 180.0f;
        float sin_z = sin(rad_z);
        float cos_z = cos(rad_z);
        Vector3D temp_vector = transformed_vector;
        temp_vector.x = transformed_vector.x * cos_z - transformed_vector.y * sin_z;
        temp_vector.y = transformed_vector.x * sin_z + transformed_vector.y * cos_z;

        // Rotation inverse sur l'axe Y
        float rad_y = -rotation.y * M_PI / 180.0f;
        float sin_y = sin(rad_y);
        float cos_y = cos(rad_y);
        transformed_vector.x = temp_vector.z * sin_y + temp_vector.x * cos_y;
        transformed_vector.y = temp_vector.y;
        transformed_vector.z = temp_vector.z * cos_y - temp_vector.x * sin_y;

        // Rotation inverse sur l'axe X
        float rad_x = -rotation.x * M_PI / 180.0f;
        float sin_x = sin(rad_x);
        float cos_x = cos(rad_x);
        temp_vector = transformed_vector;
        transformed_vector.y = temp_vector.y * cos_x - temp_vector.z * sin_x;
        transformed_vector.z = temp_vector.y * sin_x + temp_vector.z * cos_x;

        return transformed_vector;
    }


private:
    Point3D position;
    Vector3D rotation;
    float scale_factor;
};


#endif //UNTITLED_ENTITY_H
