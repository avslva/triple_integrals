#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <transformational.h>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector2D>
#include <QString>
#include <QList>
#include <QLabel>

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;

struct VertexData
{
    VertexData() {}
    VertexData(QVector3D p, QVector2D t, QVector3D n) : position(p), textCoord(t), normal(n) {}

    QVector3D position;
    QVector2D textCoord;
    QVector3D normal;
};

class Object3D : public Transformational
{
public:
    Object3D();
    Object3D(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture, int m_isPaint);
    Object3D(QString type, double x, double y, double z, double radius);

    ~Object3D();

    void init(QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture, int m_isPaint);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const double &s);
    void setGlobalTransform(const QMatrix4x4 &g);

    Object(QString type, double x, double y, double z, double radius);

    QString getType() const;
    void setType(const QString &value);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);

    double getZ() const;
    void setZ(double value);

    double getRadius() const;
    void setRadius(double value);

    double* getColor();
    void setColor(const double &value, int i);

    QLabel *getLabel() const;
    void setLabel(QLabel *value);

    QLabel *getColorLabel() const;
    void setColorLabel(QLabel *value);

    QString getColorStr();

    QLabel *getLabRes() const;
    void setLabRes(QLabel *value);

    double getRes() const;
    void setRes(double value);

private:
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLTexture *m_texture;

    QString type;
    double res;
    double x;
    double y;
    double z;
    double radius;
    double color[3];

    QLabel *label;
    QLabel *labRes;
    QLabel *colorLabel;

    int m_isPaint;

    QQuaternion m_rotate;
    QVector3D m_translate;
    double m_scale;
    QMatrix4x4 m_globalTransform;   //трансформацию всей системы локальных координат в пределах глобальной для родительской и для нее
};

#endif // OBJECT3D_H


