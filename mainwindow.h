#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <addformula.h>
#include <object3d.h>
#include <group3d.h>
#include <sectionwindow.h>
#include <tetraider.h>

//#include "shape.h"
//#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showFigures(QString formula);

    Group3D *getAllObj() const;
    //void setAllObj(QVector<Object3D *> *value);

    int getNumOfWinds() const;
    void setNumOfWinds(int value);

    //double *getNums() const;
    //void setNums(double *value);

    double **getAll_nums() const;

    void setTetraider(Tetraider *tetraider);
    Tetraider* getTetraider();
    int getD() const;

    void addSection();

    void changePlaneSec(int choose);

    int getChoosePlaneSec() const;
    void setChoosePlaneSec(int value);

private:
    Ui::MainWindow *ui;

    void init();
    double* fromFormula(QString formula);
    int findDel(int ind, QString formula);
    void labelShow();
    void setLabels();
    void setMAllNums(double *nums);

    void delTetraider();

    QLineEdit *numForDelObj;

    QLineEdit *deltaNum;
    QLineEdit *epsNum;
    QLabel *currEpsLabel;
    QLabel *currDeltaLabel;

    int numOfWinds;

    Tetraider *tetraider;
    bool isTetraider;

    Group3D *allObj;

    //QVector<Object3D *> m_objects;
    //double* m_nums;

    double** m_all_nums;

    int d;
    QSlider *slider;

    int choosePlaneSec;


private slots:
    void addFormulaWindow();
    void delOneObj();
    void delLastObj();
    void delAllObj();
    void setDeltaEps();

    void sliderClicked(int a);

    void secPlaneChoose();
    void xyPlaneChoose();
    void yzPlaneChoose();
    void xzPlaneChoose();

};

#endif // MAINWINDOW_H
