#ifndef CAMERA3D_H
#define CAMERA3D_H

#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include <transformational.h>

class Camera3D : public Transformational
{
public:
    Camera3D();

    //virtual ~Camera3D();

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions = 0);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const double &s);
    void setGlobalTransform(const QMatrix4x4 &g);


    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

private:
    QQuaternion m_rotate;
    QVector3D m_translate;
    double m_scale;
    QMatrix4x4 m_globalTransform;   //трансформацию всей системы локальных координат в пределах глобальной для родительской и для нее
    double x,y,z;
    // QQuaternion m_rotation;     //содержит вектор поворота и угол поворота

};

#endif // CAMERA3D_H
