//
// Created by zheng on 13/07/2023.
//

#ifndef UNTITLED_COLOR_H
#define UNTITLED_COLOR_H

class Color {
public:
    float r, g, b;

    Color(float red = 0.0f, float green = 0.0f, float blue = 0.0f)
            : r(red), g(green), b(blue) {}

    Color mul(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }
};


#endif //UNTITLED_COLOR_H
