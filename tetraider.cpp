#include "tetraider.h"

Tetraider::Tetraider() {
    setPoints(nullptr, nullptr, nullptr, nullptr);
}

Tetraider::Tetraider(Point *A, Point *B, Point *C, Point *D) {
    this->setPoints(A, B, C, D);
}

void Tetraider::setPoints(Point *A, Point *B, Point *C, Point *D) {
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}

void Tetraider::calcLines() {
    this->AB = calcLine(this->A, this->B);
    this->AC = calcLine(this->A, this->C);
    this->AD = calcLine(this->A, this->D);
    this->BC = calcLine(this->B, this->C);
    this->BD = calcLine(this->B, this->D);
    this->CD = calcLine(this->C, this->D);
}

Line* Tetraider::calcLine(Point *A, Point *B) {
    Point *v = new Point(B->x - A->x, B->y - A->y, B->z - A->z);
    Line *res = new Line(A, v);
    delete v;
    return res;
}

Point* Tetraider::intersection(Plane *plane, Line *line) {
    double n = plane->A*line->a + plane->B*line->b + plane->C*line->c;
    if (n == 0) {
        return nullptr;
    }
    if (false) { // TODO: добавить условие того, что прямая целиком лежит на плоскости
        return nullptr;
    }
    double m = plane->A*line->x0 + plane->B*line->y0 + plane->C*line->z0 + plane->D;
    Point *result = new Point((line->x0*(n - plane->A*line->a) - line->a*(m-plane->A*line->x0))/n,
                              (line->y0*(n - plane->B*line->b) - line->b*(m-plane->B*line->y0))/n,
                              (line->z0*(n - plane->C*line->c) - line->c*(m-plane->C*line->z0))/n);
    if (!line->havePoint(result)) {
        delete result;
        return nullptr;
    }
    return result;
}

Plane* Tetraider::getStartPlaneA() {
    Plane *res = new Plane((B->x + C->x + D->x)/3 - A->x,
                           (B->y + C->y + D->y)/3 - A->y,
                           (B->z + C->z + D->z)/3 - A->z, 0);
    res->setD(-10);
//    res->setD(-(res->A*A->x + res->B*A->y + res->C*A->z));
    return res;
}

Plane* Tetraider::getStartPlaneX() {
    double min_x = A->x;
    if (B->x < min_x) { min_x = B->x; }
    if (C->x < min_x) { min_x = C->x; }
    if (D->x < min_x) { min_x = D->x; }
    return new Plane(-1, 0, 0, min_x);
}


Plane* Tetraider::getStartPlane1(){
    if( (A->x == B->x && A->x == C->x) || (A->x == C->x && A->x == D->x) ||  (A->x == B->x && A->x == D->x)){
        return new Plane( (1 / A->x), 0, 0, -1);
    }
    if(B->x == C->x && B->x == D->x){
        return new Plane( (1 / B->x), 0, 0, -1);
    }
    if( (A->y == B->y && (A->y == C->y || A->y == D->y)) || (A->y == C->y && A->y == D->y)){
        return new Plane(0, (1 / A->y), 0, -1);
    }
    if(B->y == C->y && B->y == D->y){
        return new Plane(0, (1 / B->y), 0, -1);
    }
    if( (A->z == B->z && (A->z == C->z || A->z == D->z)) || (A->z == C->z && A->z == D->z) || (B->z == C->z && B->z == D->z)){
        return new Plane(0, 0, (1 / A->z), -1);
    }
    if(B->z == C->z && B->z == D->z){
        return new Plane(0, 0, (1 / B->z), -1);
    } else {
        return getStartPlaneX();
    }
}

Plane* Tetraider::getStartPlane() {
  return new Plane(-1, 0, -1, 0); // y in plane , 45.
  //  return getStartPlaneA();
//    return getStartPlaneX();
    //return getStartPlane1();
}

double Tetraider::calcV() {
    Plane *plane = getStartPlane();
    double d = plane->D;
    int i, n, k = 0;
    //Point **resPoints;
    double resV = 0;
    bool isCross = false;
    const int AllS = 1000;
    //allPoints = new Point**[AllS];

    QVector<Point *> resPointsVect;

    while (true) {
        resPointsVect.clear();

        Point **points = new Point*[6];
        points[0] = intersection(plane, this->AB);
        points[1] = intersection(plane, this->AC);
        points[2] = intersection(plane, this->AD);
        points[3] = intersection(plane, this->BC);
        points[4] = intersection(plane, this->BD);
        points[5] = intersection(plane, this->CD);

        n = 0;

        QVector<Point *> blabla;
        for (i = 0; i < 6; i++) {
            if (points[i] != nullptr) {
                n++;
                blabla.push_back(points[i]);
            }
        }

        if(n == 3){
            resPointsVect = blabla;
        }

        if(n ==  4){
            double maxLen = 0, len = 0;
            Point *tmp1;
            Point *tmp3;
            for(int i = 0; i < 4; i++){
                Point *first = blabla.at(i);
                for(int j = i + 1; j < 4; j++){
                    Point *second = blabla.at(j);
                    len = pow((second->x - first->x), 2) + pow((second->y - first->y), 2) + pow((second->z - first->z), 2);
                    if(len > maxLen){
                        maxLen = len;
                        tmp1 = first;
                        tmp3 = second;
                    }
                }
            }
            blabla.remove(blabla.indexOf(tmp1));
            blabla.remove(blabla.indexOf(tmp3));
            resPointsVect.push_back(tmp1);
            resPointsVect.push_back(blabla.at(0));
            resPointsVect.push_back(tmp3);
            resPointsVect.push_back(blabla.at(1));
        }

        //resPoints = new Point*[n];

        if (!isCross && n != 0) {
            isCross = true;
        }
        if (isCross && n == 0) {
            isCross = false;
        }
        if (!isCross && n == 0 && k*EPSILON > MaxLToTetr) {
            break;
        }

        //n = 0;

        /*for (i = 0; i < 6; i++) {
            if (points[i] != nullptr) {
                resPoints[n] = points[i];
                n++;
            }
        }
        if (n != 0) {
            for (i = n; i < 6; i++) {
                resPoints[i] = nullptr;
            }
        }*/

        if (n != 0 && k < AllS) {
            allPointsVect.push_back(resPointsVect);
            //allPoints[k] = resPoints;
        }
        //f()

        if (resPointsVect.size() == 3) {
            resV += this->EPSILON*this->calcS3(resPointsVect);
        }
        if (resPointsVect.size() == 4) {
            resV += this->EPSILON*this->calcS4(resPointsVect);
        }
        d += this->EPSILON;
        plane->setD(d);
        k++;
    }
    return resV;
}

/*
double Tetraider::calcS3(Point **points) {
    Point *v1 = new Point(points[1]->x - points[0]->x, points[1]->y - points[0]->y, points[1]->z - points[0]->z);
    Point *v2 = new Point(points[2]->x - points[0]->x, points[2]->y - points[0]->y, points[2]->z - points[0]->z);
    double res = v1->vect_mult(v2)->mod()/2;
    delete v1;
    delete v2;
    return res;
}

double Tetraider::calcS4(Point **points) {
    Point **points3 = new Point*[3];
    for (int i = 0; i < 3; i++) {
        points3[i] = points[i];
    }
    double res = calcS3(points3);

    for (int i = 0; i < 3; i++) {
        points3[i] = points[i+1];
    }
    res += calcS3(points3);
    return res;
}
*/

double Tetraider::calcS3(QVector<Point *> points) {
    Point *v1 = new Point(points.at(1)->x - points.at(0)->x, points.at(1)->y - points.at(0)->y, points.at(1)->z - points.at(0)->z);
    Point *v2 = new Point(points.at(2)->x - points.at(0)->x, points.at(2)->y - points.at(0)->y, points.at(2)->z - points.at(0)->z);
    double res = v1->vect_mult(v2)->mod()/2;
    delete v1;
    delete v2;
    return res;
}

double Tetraider::calcS4(QVector<Point *> points) {
    QVector<Point *> points3;
    for (int i = 0; i < 3; i++) {
        points3.push_back(points.at(i));
    }
    double res = calcS3(points3);

    points3.clear();

    for (int i = 0; i < 3; i++) {
        points3.push_back(points.at(i + 1));
    }
    res += calcS3(points3);
    return res;
}

/*Point*** Tetraider::getAllPoints() {
    return allPoints;
}*/

QVector<QVector<Point *>> Tetraider::getAllPointsVect() const
{
    return allPointsVect;
}

void Tetraider::setAllPointsVect(const QVector<QVector<Point *> > &value)
{
    allPointsVect = value;
}
