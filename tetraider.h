#ifndef TETRAIDER_H
#define TETRAIDER_H

#include "line.h"
#include "plane.h"
#include <QVector>

class Tetraider
{
public:
    Point *A, *B, *C, *D;
    Line *AB, *AC, *AD, *BC, *BD, *CD;

    Tetraider();
    Tetraider(Point *A, Point *B, Point *C, Point *D);
    void setPoints(Point *A, Point *B, Point *C, Point *D);

    void calcLines();
    double calcV();
    Point* intersection(Plane *plane, Line *line);
    //Point*** getAllPoints();

    const double EPSILON = 0.01;
    const double MaxLToTetr = 100;

    QVector<QVector<Point *>> getAllPointsVect() const;

    void setAllPointsVect(const QVector<QVector<Point *> > &value);

private:
    //Point ***allPoints;

    QVector<QVector<Point*>> allPointsVect;

    Line* calcLine(Point *A, Point *B);
    Plane* getStartPlane();
    Plane* getStartPlane1();
    Plane* getStartPlaneA();
    Plane* getStartPlaneX();

    double calcS3(QVector<Point *> points);
    double calcS4(QVector<Point *> points);
};

#endif // TETRAIDER_H
