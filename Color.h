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
    float operator[](int index) const {
        if (index == 0) return r;
        if (index == 1) return g;
        if (index == 2) return b;
        return 0.0f;
    }
    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }

    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color& operator+=(const Color& other) {
        r += other.r;
        g += other.g;
        b += other.b;
        return *this;
    }
};


#endif //UNTITLED_COLOR_H
