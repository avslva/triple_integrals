#include "point.h"

Point::Point()
{
    setXYZ(0, 0, 0);
}

Point::Point(double x, double y, double z) {
    setXYZ(x, y, z);
}

void Point::setXYZ(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point* Point::vect_mult(Point *v2) {
    return new Point(this->y*v2->z - this->z*v2->y,
                     this->z*v2->x - this->x*v2->z,
                     this->x*v2->y - this->y*v2->x);
}

double Point::mod() {
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
