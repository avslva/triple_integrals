#include "shape.h"

Shape::Shape(){}

Shape::Shape(double *num) {
    convert(num);
}

void Shape::convert(double *num) {
    this->D = num[0];
    this->E = num[1];
    this->F = num[2];

    this->x0 = num[6];
    this->y0 = num[7];
    this->z0 = num[8];

    this->a = num[10];
    this->b = num[11];
    this->c = num[12];

    this->R = num[9];
}
