#include "sectionwidget.h"

SectionWidget::SectionWidget(QWidget *parent):QOpenGLWidget(parent){
    isComplate = false;
 }

void SectionWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void SectionWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, w, 0, h, -1.0, 1.0);
    glOrtho(-w/100, w/100, -h/100, h/100, -1.0, 1.0);
}

void SectionWidget::paintGL()
{
    glClearColor(0.4f, 0.6f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (isComplate) {
        initMainLines();

        int d = father->getD();

        glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 0.0, 0.0);

        int planeSec = father->getChoosePlaneSec();

        if(planeSec == 0){
            for(int i = 0; i < allPointsVect.at(d).size(); i++){
                glVertex2f(allPointsVect.at(d).at(i)->x, allPointsVect.at(d).at(i)->y);
            }
        }else if(planeSec == 1){
            for(int i = 0; i < allPointsVect.at(d).size(); i++){
                glVertex2f(allPointsVect.at(d).at(i)->y, allPointsVect.at(d).at(i)->z);
            }
        }else if(planeSec == 2){
            for(int i = 0; i < allPointsVect.at(d).size(); i++){
                glVertex2f(allPointsVect.at(d).at(i)->x, allPointsVect.at(d).at(i)->z);
            }
        }else {
            for(int i = 0; i < allPointsVect.at(d).size(); i++){
                glVertex2f(-1*allPointsVect.at(d).at(i)->z, allPointsVect.at(d).at(i)->y);
            }
        }

        glEnd();
    }
}

QVector<QVector<Point *>> SectionWidget::getAllPointsVect() const
{
    return allPointsVect;
}

void SectionWidget::setAllPointsVect(const QVector<QVector<Point *>> &value)
{
    allPointsVect = value;
}

void SectionWidget::setIsComplate(bool value)
{
    isComplate = value;
}

MainWindow *SectionWidget::getFather() const
{
    return father;
}

void SectionWidget::setFather(MainWindow *value)
{
    father = value;
}

void SectionWidget::initMainLines(){
    int max_num = 8.0;

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-max_num, 0.0);
    glVertex2f(max_num, 0.0);
    glVertex2f(0.0, -max_num);
    glVertex2f(0.0, max_num);

    for(int i = -max_num; i < max_num; i++){
        glVertex2f(i, -0.1);
        glVertex2f(i, 0.1);
    }
    for(int i = -max_num + 1; i < max_num; i++){
        glVertex2f(-0.1, i);
        glVertex2f(0.1, i);
    }

    //x
    glVertex2f(max_num + 0.2, 0.3);
    glVertex2f(max_num + 0.4, 0.5);
    glVertex2f(max_num + 0.2, 0.5);
    glVertex2f(max_num + 0.4, 0.3);

    //стрелка для x
    glVertex2f(max_num, 0.0);
    glVertex2f(max_num - 0.1, 0.2);
    glVertex2f(max_num, 0.0);
    glVertex2f(max_num - 0.1, -0.2);

    //y
    glVertex2f(-0.5, max_num + 0.2);
    glVertex2f(-0.5, max_num + 0.3);
    glVertex2f(-0.5, max_num + 0.3);
    glVertex2f(-0.6, max_num + 0.4);
    glVertex2f(-0.5, max_num + 0.3);
    glVertex2f(-0.4, max_num + 0.4);

    //стрелка для y
    glVertex2f(0.0, max_num);
    glVertex2f(-0.2, max_num - 0.1);
    glVertex2f(0.0, max_num);
    glVertex2f(0.2, max_num - 0.1);

    glEnd();
}

void SectionWidget::deleteAllPointsVect(){
    allPointsVect.clear();
}

