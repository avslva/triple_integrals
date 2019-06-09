#include "line.h"

Line::Line()
{
    this->setValues(0, 0, 0, 0, 0, 0);
}

Line::Line(Point *a0, Point *v) {
    this->setValues(a0->x, a0->y, a0->z, v->x, v->y, v->z);
}

Line::Line(double x0, double y0, double z0, double a, double b, double c) {
    this->setValues(x0, y0, z0, a, b, c);
}

void Line::setValues(double x0, double y0, double z0, double a, double b, double c) {
    this->x0 = x0;
    this->y0 = y0;
    this->z0 = z0;
    this->a = a;
    this->b = b;
    this->c = c;
}

double mod(double x) {
    if (x >= 0)  {
        return x;
    }
    return -x;
}

bool Line::havePoint(Point *A) {
    if (((x0 - A->E < A->x && A->x - A->E < x0 + a) || (x0 + a - A->E <  A->x && A->x - A->E < x0)) &&
        ((y0 - A->E < A->y && A->y - A->E < y0 + b) || (y0 + b - A->E <  A->y && A->y - A->E < y0)) &&
        ((z0 - A->E < A->z && A->z - A->E < z0 + c) || (z0 + c - A->E <  A->z && A->z - A->E < z0)) )
    {
        return true;
    }
    return false;
}
