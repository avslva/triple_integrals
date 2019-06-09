#ifndef GROUP3D_H
#define GROUP3D_H

#include <transformational.h>
#include <object3d.h>

#include <QQuaternion>
#include <QVector3D>
#include <QMatrix4x4>
#include <QVector>

class Group3D : public Transformational
{
public:
    Group3D();

    //virtual ~Group3D();

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const double &s);
    void setGlobalTransform(const QMatrix4x4 &g);

    void addObject(Object3D *obj);

    //void setGroup3D(QVector<Object3D *> *value);
    void addObj(Object3D *value);
    int numOfObj();
    Object3D* objAt(int value);
    void delObj(int value);
    void delLastObj();
    void delAllObj();

private:
    QQuaternion m_rotate;
    QVector3D m_translate;
    double m_scale;
    QMatrix4x4 m_globalTransform;   //трансформацию всей системы локальных координат в пределах глобальной для родительской и для нее

    QVector<Object3D *> m_objects;
};

#endif // GROUP3D_H
