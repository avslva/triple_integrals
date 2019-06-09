#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
private:

public:
    Shape();
    Shape(double *num);
    double D, E, F, R, x0, y0, z0, a, b, c;

    void convert(double *num);
};

#endif // SHAPE_H
