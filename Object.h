#pragma once
#include "Vector3.h"

double xl = 0, yl = 0, zl = 0;
double maxDist = 0;
double minDist = DBL_MAX;

struct Color {
    int red;
    int green;
    int blue;
    inline Color(int r = 0, int g = 0, int b = 0) {
        red = r;
        green = g;
        blue = b;
    }
};

class Object {
protected:
    Vector3 v0;
public:
    Color col;
    virtual bool intersect(double, double, double, double, double, double, double&, bool&, int&) = 0;
    virtual Color pixelColor(double, double, double, int&) = 0;
    virtual void setColor(Color) = 0;
    virtual Vector3 getCenter() = 0;
};
