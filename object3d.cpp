#include "object3d.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

Object3D::Object3D():
    m_indexBuffer(QOpenGLBuffer::IndexBuffer), m_texture(0)
{
    m_scale = 1.0f;
    type = "";
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Object3D::Object3D(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture, int m_isPaint):
    m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    m_scale = 1.0f;
    init(vertData, indexes, texture, m_isPaint);
}

Object3D::~Object3D(){
    if(m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if(m_indexBuffer.isCreated())
        m_indexBuffer.destroy();
    if(m_texture != 0)
        if(m_texture->isCreated())
            m_texture->destroy();
}

void Object3D::init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture, int isPaint){
    if(m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if(m_indexBuffer.isCreated())
        m_indexBuffer.destroy();
    if(m_texture != 0){
        m_texture = 0;
    }

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(vertData.constData(), vertData.size() * sizeof(VertexData));  //выделяет видеопамять
    m_vertexBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));   //умножаем на sizeof, тк размер size в байтах
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(texture.mirrored());

    m_texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);

    m_isPaint = isPaint;
}

void Object3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions){
    if(!m_vertexBuffer.isCreated() || !m_indexBuffer.isCreated())
        return;

    m_texture->bind(0);
    program->setUniformValue("u_texture", 0);

    //преобразования с матрицей делаются в обратном порядке, снизу вверх
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(m_translate);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);
    modelMatrix = m_globalTransform * modelMatrix;

    program->setUniformValue("u_modelMatrix", modelMatrix);

    m_vertexBuffer.bind();

    int offset = 0;

    int vertLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertLoc);
    program->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int textLoc = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(textLoc);
    program->setAttributeBuffer(textLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normLoc = program->attributeLocation("a_normal");
    program->enableAttributeArray(normLoc);
    program->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_indexBuffer.bind();

    if(m_isPaint == 0){
        functions->glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }else if(m_isPaint == 1){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        functions->glDrawElements(GL_TRIANGLE_STRIP, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }else if(m_isPaint == 2){
        functions->glDrawElements(GL_POLYGON, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }else if(m_isPaint == 3){
        //glEnable(GL_LINE_SMOOTH);
        functions->glDrawElements(GL_LINE_STRIP, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }else if(m_isPaint == 4){
        functions->glDrawElements(GL_LINES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }else if(m_isPaint == 5){
        //glColor3f(1.0, 0.0, 0.0);
        double **triangleVertexArray = new double*[m_indexBuffer.size()];
        for(int i = 0; i < m_indexBuffer.size(); ++i){
            triangleVertexArray[i] = new double[2];
            triangleVertexArray[i][0] = 1.0;
            triangleVertexArray[i][1] = 0.0;
            triangleVertexArray[i][2] = 0.0;
        }
        glColorPointer(3, GL_FLOAT, 0, triangleVertexArray);
        functions->glDrawElements(GL_POINTS, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
    }

    m_vertexBuffer.release();
    m_indexBuffer.release();
    m_texture->release();
}

void Object3D::translate(const QVector3D &t){
    m_translate += t;
}

void Object3D::rotate(const QQuaternion &r){
    m_rotate = r * m_rotate;
}

void Object3D::scale(const double &s){
    m_scale *= s;
}

void Object3D::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;
}


Object3D::Object3D(QString type, double x, double y, double z, double radius){
    this->type = type;
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    for(int i = 0; i < 3; ++i){
        color[i] = (rand() % 100 + 1)/100.0f;
    }
}

QString Object3D::getType() const
{
    return type;
}

void Object3D::setType(const QString &value)
{
    type = value;
}

double Object3D::getX() const
{
    return x;
}

void Object3D::setX(double value)
{
    x = value;
}

double Object3D::getY() const
{
    return y;
}

void Object3D::setY(double value)
{
    y = value;
}

double Object3D::getZ() const
{
    return z;
}

void Object3D::setZ(double value)
{
    z = value;
}

double Object3D::getRadius() const
{
    return radius;
}

void Object3D::setRadius(double value)
{
    radius = value;
}

double* Object3D::getColor()
{
    return color;
}

void Object3D::setColor(const double &value, int i)
{
    color[i] = value;
}

QLabel *Object3D::getLabel() const
{
    return label;
}

void Object3D::setLabel(QLabel *value)
{
    label = value;
}

QLabel *Object3D::getColorLabel() const
{
    return colorLabel;
}

void Object3D::setColorLabel(QLabel *value)
{
    colorLabel = value;
}

QString Object3D::getColorStr(){
    QString c, str;
    c.setNum(int(color[0]*255));
    str.append(c);
    str.append(",");
    c.setNum(int(color[1]*255));
    str.append(c);
    str.append(",");
    c.setNum(int(color[2]*255));
    str.append(c);
    return str;
}

QLabel *Object3D::getLabRes() const
{
    return labRes;
}

void Object3D::setLabRes(QLabel *value)
{
    labRes = value;
}

double Object3D::getRes() const
{
    return res;
}

void Object3D::setRes(double value)
{
    res = value;
}
