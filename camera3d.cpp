#include "camera3d.h"

Camera3D::Camera3D()
{
    m_scale = 1.0f;
    m_globalTransform.setToIdentity();
    m_rotate.setX(0.0f);
}

void Camera3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions){
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

void Camera3D::translate(const QVector3D &t){
    m_translate += t;
}

void Camera3D::rotate(const QQuaternion &r){
    //if(m_rotate.x() >= 0.0f){
        m_rotate = r * m_rotate;
    /*}else{
        m_rotate.setX(0.0f);
    }*/
}

void Camera3D::scale(const double &s){
    m_scale *= s;
}

void Camera3D::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;
}

double Camera3D::getX() const
{
    return m_translate.x();
}

void Camera3D::setX(double value)
{
    x = value;
}

double Camera3D::getY() const
{
    return m_translate.y();
}

void Camera3D::setY(double value)
{
    y = value;
}

double Camera3D::getZ() const
{
    return m_translate.z();
}

void Camera3D::setZ(double value)
{
    z = value;
}

