#ifndef POINT_H
#define POINT_H

#include <math.h>

class Point {
public:
    double x;
    double y;
    double z;
    Point();
    Point(double x, double y, double z);
    void setXYZ(double x, double y, double z);

    Point* vect_mult(Point *v2);
    double mod();
    const double E = 0.0000001;
};

#endif // POINT_H
