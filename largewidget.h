#ifndef LARGEWIDGET_H
#define LARGEWIDGET_H

#include <widget.h>
#include <mainwindow.h>

namespace Ui {
class largeWidget;
}

class largeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit largeWidget(QWidget *parent = 0);
    ~largeWidget();

    MainWindow *getFather() const;
    void setFather(MainWindow *value);

private:
    Ui::largeWidget *ui;

    MainWindow *father;

    Group3D *allObj;

    void closeEvent(QCloseEvent *event);
};

#endif // LARGEWIDGET_H
