#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Matrice.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Ray.h"

class Entity {
public:
    Entity() : transformationMatrix(Matrix()) {}

    void translate(float x, float y, float z) {
        Matrix translationMatrix;
        translationMatrix(0, 3) = x;
        translationMatrix(1, 3) = y;
        translationMatrix(2, 3) = z;
        transformationMatrix = translationMatrix * transformationMatrix;
    }

    void rotateX(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(1, 1) = cos(rad);
        rotationMatrix(1, 2) = -sin(rad);
        rotationMatrix(2, 1) = sin(rad);
        rotationMatrix(2, 2) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void rotateY(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(0, 0) = cos(rad);
        rotationMatrix(0, 2) = sin(rad);
        rotationMatrix(2, 0) = -sin(rad);
        rotationMatrix(2, 2) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void rotateZ(float deg) {
        float rad = degToRad(deg);
        Matrix rotationMatrix;
        rotationMatrix(0, 0) = cos(rad);
        rotationMatrix(0, 1) = -sin(rad);
        rotationMatrix(1, 0) = sin(rad);
        rotationMatrix(1, 1) = cos(rad);
        transformationMatrix = rotationMatrix * transformationMatrix;
    }

    void scale(float factor) {
        Matrix scalingMatrix;
        scalingMatrix(0, 0) = factor;
        scalingMatrix(1, 1) = factor;
        scalingMatrix(2, 2) = factor;
        transformationMatrix = scalingMatrix * transformationMatrix;
    }

    Point3D localToGlobal(const Point3D& point) const {
        HPoint hPoint(point.x, point.y, point.z, 1.0);
        HPoint transformedPoint = transformationMatrix * hPoint;
        return Point3D(transformedPoint.x, transformedPoint.y, transformedPoint.z);
    }



    Vector3D localToGlobal(const Vector3D& vector) const {
        HVector hVector(vector.x, vector.y, vector.z, 0.0);
        HVector transformedVector = transformationMatrix * hVector;
        return Vector3D(transformedVector.x, transformedVector.y, transformedVector.z);
    }

    Point3D globalToLocal(const Point3D& point) const {
        Matrix inverseMatrix = transformationMatrix.inverse();
        HPoint hPoint(point.x, point.y, point.z, 1.0);
        HPoint transformedPoint = inverseMatrix * hPoint;
        return Point3D(transformedPoint.x, transformedPoint.y, transformedPoint.z);
    }

    Vector3D globalToLocal(const Vector3D& vector) const {
        Matrix inverseMatrix = transformationMatrix.inverse();
        HVector hVector(vector.x, vector.y, vector.z, 0.0);
        HVector transformedVector = inverseMatrix * hVector;
        return Vector3D(transformedVector.x, transformedVector.y, transformedVector.z);
    }
    Ray localToGlobal(const Ray& ray) const {
        Point3D origin = localToGlobal(ray.origin);
        Vector3D vector = localToGlobal(ray.vector);
        return Ray(origin, vector);
    }

    Ray globalToLocal(const Ray& ray) const {
        Point3D origin = globalToLocal(ray.origin);
        Vector3D vector = globalToLocal(ray.vector);
        return Ray(origin, vector);
    }

private:
    Matrix transformationMatrix;

    float degToRad(float deg) {
        return deg * M_PI / 180.0;
    }
};

#endif // ENTITY_HPP