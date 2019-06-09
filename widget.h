#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QWheelEvent>

#include <mainwindow.h>

class Object3D;
class Transformational;
class Group3D;
class Camera3D;

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    QVector<Object3D *> objects() const;

    MainWindow *getFather() const;
    void setFather(MainWindow *value);

    bool isDraw;


    void initFigures(double* nums, Tetraider *tetraider, Group3D *grupa);
    //void initFiguresFromLW(double** nums, Group3D *grupa, int size);

    double getDelta() const;
    void setDelta(double value);

    double getEpsilon() const;
    void setEpsilon(double value);

    void initTetraider(Tetraider *tetraider);

    void setStartSection(bool isStartSection );

    void setAllPointsVect(const QVector<QVector<Point *>> &value);
    void deleteAllPointsVect();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    //void mouseDoubleClickEvent(QMouseEvent *);
    //void keyReleaseEvent(QKeyEvent *event);

    void initShaders();

    void initCylinder(double a, double b, double height);
    //void initConus(double radius, double height);
    void initParaboloid1(double a, double b, double height);
    void initParaboloid2(double a, double b, double height);
    void initMainLines();
    void initSphera(double r);
    void initEllipsoid(double a, double b, double c);
    void initConus(double a, double b, double c);
    //int initCrossPoints(QVector<VertexData> *vert);


    double f(double* nums, double x, double z);
//    double* f(double* nums, double x, double y);
    double v(double* nums);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector3D m_mousePosition;

    QVector<Object3D *> m_objects;
    QVector<Group3D *> m_groups;
    QVector<Transformational *> m_transformObjects;

    Camera3D *m_camera;

    MainWindow *father;

    //QVector<VertexData> *vert;
    //QVector3D *points;

    double delta = 0.001; // шаг сечения
    double epsilon = 0.01; // размер кубика

    bool isStartSection = false;
    QVector<QVector<Point *>> allPointsVect;
    void drawSection();
};

#endif // WIDGET_H
