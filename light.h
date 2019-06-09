#ifndef LIGHT_H
#define LIGHT_H

#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>

#include <transformational.h>

class Light : public Transformational
{
public:
    Light();

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions = 0);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const double &s);
    void setGlobalTransform(const QMatrix4x4 &g);


    QVector3D getCoord() const;
    void setCoord(const QVector3D &value);

private:
    QQuaternion m_rotate;
    QVector3D m_translate;
    double m_scale;
    double m_sens;
    QVector3D coord;
    QMatrix4x4 m_globalTransform;   //трансформацию всей системы локальных координат в пределах глобальной для родительской и для нее

    // QQuaternion m_rotation;     //содержит вектор поворота и угол поворота

};

#endif // LIGHT_H
