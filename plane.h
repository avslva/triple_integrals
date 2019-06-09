#ifndef PLANE_H
#define PLANE_H


class Plane
{
public:
    double A, B, C, D;
    Plane();
    Plane(double A, double B, double C, double D);
    void setValues(double A, double B, double C, double D);
    void setD(double D);
};

#endif // PLANE_H
