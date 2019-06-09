#include "light.h"
#include <QOpenGLShaderProgram>

Light::Light()
{
    m_scale = 1.0f;
    m_globalTransform.setToIdentity();
    m_rotate.setX(0.0f);
    m_sens = 1.0f;
    coord = QVector3D(0.0, 0.0, 0.0);
}

void Light::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions){
    if(functions != 0)
        return;

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(m_translate);
    viewMatrix.rotate(m_rotate);
    viewMatrix.scale(m_scale);
    viewMatrix = viewMatrix * m_globalTransform.inverted();

    program->setUniformValue("u_viewMatrix", viewMatrix);
}

void Light::translate(const QVector3D &t){
    m_translate += t;
}

void Light::rotate(const QQuaternion &r){
    if(m_rotate.x() >= 0.0f){
        m_rotate = r * m_rotate;
    }else{
        m_rotate.setX(0.0f);
    }
}

void Light::scale(const double &s){
    m_scale *= s;
}

void Light::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;
}

QVector3D Light::getCoord() const
{
    return coord;
}

void Light::setCoord(const QVector3D &value)
{
    coord = value;
}

