#ifndef ADDFORMULA_H
#define ADDFORMULA_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <QWheelEvent>

class MainWindow;
class Tetraider;

namespace Ui {
class AddFormula;
}

class AddFormula : public QWidget
{
    Q_OBJECT

public:
    explicit AddFormula(QWidget *parent = 0);
    ~AddFormula();

    MainWindow *getFather() const;
    void setFather(MainWindow *value);

private:
    Ui::AddFormula *ui;

    void init();
    MainWindow *father;

    QLineEdit *formula_part1;
    QLineEdit *formula_part2;
    QComboBox *symbol;
    QString formula;

    QRadioButton *rb_formula;
    QRadioButton *rb_points;

    QLineEdit *A_x;
    QLineEdit *A_y;
    QLineEdit *A_z;

    QLineEdit *B_x;
    QLineEdit *B_y;
    QLineEdit *B_z;

    QLineEdit *C_x;
    QLineEdit *C_y;
    QLineEdit *C_z;

    QLineEdit *D_x;
    QLineEdit *D_y;
    QLineEdit *D_z;

    QPushButton *okButton;

    Tetraider* initTetraider();

    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void okButtonClicked();
    void rb_formulaClicked();
    void rb_pointsClicked();
};

#endif // ADDFORMULA_H
