#ifndef SECTIONWINDOW_H
#define SECTIONWINDOW_H

#include "tetraider.h"
#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <mainwindow.h>

namespace Ui {
class SectionWindow;
}

class SectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SectionWindow(QWidget *parent = 0);
    ~SectionWindow();

    void setTetraider(Tetraider* tetraider);
    Tetraider* getTetraider();
    void updateWidget();
//    void showEvent(QShowEvent *event);

    QSlider *getSlider() const;

    MainWindow *getFather() const;
    void setFather(MainWindow *value);

    int getD() const;

private:
    Ui::SectionWindow *ui;

    Tetraider *tetraider;

    QSlider *slider;

    void init();

    MainWindow *father;

    int d;

private slots:
    void sliderClicked(int a);
};

#endif // SECTIONWINDOW_H
