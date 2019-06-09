#include "group3d.h"

Group3D::Group3D()
{
    m_scale = 1.0f;
}

void Group3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions){
    for(int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->draw(program, functions);
    }
}

void Group3D::translate(const QVector3D &t){
    m_translate += t;
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;

    for(int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::rotate(const QQuaternion &r){
    m_rotate = r * m_rotate;
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;

    for(int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::scale(const double &s){
    m_scale *= s;
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;

    for(int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);

    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;

    for(int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::addObject(Object3D *obj){
    m_objects.append(obj);
    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;
    m_objects[m_objects.size() - 1]->setGlobalTransform(localMatrix);
}

//void Group3D::setGroup3D(QVector<Object3D *> *value)
//{
//    m_objects. = value;
//}

void Group3D::addObj(Object3D *value){
    m_objects.append(value);
}

int Group3D::numOfObj(){
    return m_objects.size();
}

Object3D* Group3D::objAt(int value){
    return m_objects.at(value);
}

void Group3D::delObj(int value){
    if(value != 0){
        delete objAt(value)->getLabel();
        delete objAt(value)->getLabRes();
    }
    for(int i = value; i < numOfObj() - 1; i++){
        m_objects.replace(i, m_objects.at(i+1));
    }
    m_objects.removeLast();
}

void Group3D::delLastObj(){
    if(numOfObj() != 1){
        delete objAt(numOfObj() - 1)->getLabel();
        delete objAt(numOfObj() - 1)->getLabRes();
        //delete objAt(numOfObj() - 1)->getColorLabel();
        m_objects.removeLast();
    }
}

void Group3D::delAllObj(){
    for(int i = numOfObj() - 1; i > 0; i--){
        delObj(i);
    }
}

