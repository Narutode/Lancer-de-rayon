//
// Created by zheng on 09/07/2023.
//

#ifndef UNTITLED_HRAY_H
#define UNTITLED_HRAY_H

#include "HPoint.h"
#include "HVector.h"

class HRay {
public:
    HPoint origin;
    HVector vector;

    HRay(float ox, float oy, float oz, float vx, float vy, float vz) : origin(ox, oy, oz), vector(vx, vy, vz) {}

    HRay(const HPoint& p, const HVector& v) : origin(p), vector(v) {}
};


#endif //UNTITLED_HRAY_H
