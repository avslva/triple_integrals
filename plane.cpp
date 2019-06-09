#include "plane.h"

// Ax+By+Cz+D=0
Plane::Plane()
{
     setValues(0, 0, 0, 0);
}

Plane::Plane(double A, double B, double C, double D) {
    setValues(A, B, C, D);
}

void Plane::setValues(double A, double B, double C, double D) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}

void Plane::setD(double D) {
    this->D = D;
}
