#ifndef SECTIONWDGET_H
#define SECTIONWDGET_H

//#include <windows.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLFramebufferObjectFormat>

#include <point.h>
#include <sectionwindow.h>

namespace Ui {
    class SectionWindow;
}

class SectionWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit SectionWidget(QWidget *parent = 0);

    MainWindow *getFather() const;
    void setFather(MainWindow *value);

    void setIsComplate(bool value);

    QVector<QVector<Point *>> getAllPointsVect() const;
    void setAllPointsVect(const QVector<QVector<Point *>> &value);
    void deleteAllPointsVect();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    MainWindow *father;

    bool isComplate;

    QVector<QVector<Point *>> allPointsVect;

    void initMainLines();
};

#endif // SECTIONWDGET_H
