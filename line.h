#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
public:
    double x0, y0, z0;
    double a, b, c;
    Line();
    Line(Point *a0, Point *v);
    Line(double x0, double y0, double z0, double a, double b, double c);
    void setValues(double x0, double y0, double z0, double a, double b, double c);
    bool havePoint(Point *A);
};

#endif // LINE_H
