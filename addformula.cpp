#include "addformula.h"
#include "ui_addformula.h"

#include "mainwindow.h"
#include <tetraider.h>

AddFormula::AddFormula(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFormula)
{
    ui->setupUi(this);

    setWindowTitle("Ввод формулы");

    init();
}

AddFormula::~AddFormula()
{
    delete ui;
}

void AddFormula::init(){
    formula_part1 = new QLineEdit(this);
    formula_part1->setGeometry(80, 90, 120, 30);
    formula_part1->setText("x^2+y^2+z^2");

    symbol = new QComboBox(this);
    symbol->setGeometry(210, 90, 42, 30);
    symbol->insertItem(0, "<");
    symbol->insertItem(1, "<=");
    symbol->insertItem(2, "=");
    symbol->insertItem(3, ">=");
    symbol->insertItem(4, ">");

    formula_part2 = new QLineEdit(this);
    formula_part2->setGeometry(262, 90, 50, 30);
    formula_part2->setText("2");

    rb_formula = new QRadioButton(this);
    rb_formula->setGeometry(40, 55, 250, 20);
    rb_formula->setText("Ввод уравнения/неравенства");
    rb_formula->setChecked(true);
    connect(rb_formula, SIGNAL(clicked(bool)), this, SLOT(rb_formulaClicked()));

    rb_points = new QRadioButton(this);
    rb_points->setGeometry(40, 140, 250, 20);
    rb_points->setText("Ввод тетраэдра по точкам");
    connect(rb_points, SIGNAL(clicked(bool)), this, SLOT(rb_pointsClicked()));


    QLabel *A_label = new QLabel(this);
    A_label->setGeometry(80, 170, 20, 20);
    A_label->setText("A:");

    QLabel *A_x_label = new QLabel(this);
    A_x_label->setGeometry(120, 170, 20, 20);
    A_x_label->setText("x");

    A_x = new QLineEdit(this);
    A_x->setGeometry(140, 170, 30, 30);
    A_x->setText("2");

    QLabel *A_y_label = new QLabel(this);
    A_y_label->setGeometry(240, 170, 20, 20);
    A_y_label->setText("y");

    A_y = new QLineEdit(this);
    A_y->setGeometry(260, 170, 30, 30);
    A_y->setText("1");

    QLabel *A_z_label = new QLabel(this);
    A_z_label->setGeometry(360, 170, 20, 20);
    A_z_label->setText("z");

    A_z = new QLineEdit(this);
    A_z->setGeometry(380, 170, 30, 30);
    A_z->setText("-1");


    QLabel *B_label = new QLabel(this);
    B_label->setGeometry(80, 210, 20, 20);
    B_label->setText("B:");

    QLabel *B_x_label = new QLabel(this);
    B_x_label->setGeometry(120, 210, 20, 20);
    B_x_label->setText("x");

    B_x = new QLineEdit(this);
    B_x->setGeometry(140, 210, 30, 30);
    B_x->setText("3");

    QLabel *B_y_label = new QLabel(this);
    B_y_label->setGeometry(240, 210, 20, 20);
    B_y_label->setText("y");

    B_y = new QLineEdit(this);
    B_y->setGeometry(260, 210, 30, 30);
    B_y->setText("2");

    QLabel *B_z_label = new QLabel(this);
    B_z_label->setGeometry(360, 210, 20, 20);
    B_z_label->setText("z");

    B_z = new QLineEdit(this);
    B_z->setGeometry(380, 210, 30, 30);
    B_z->setText("-1");


    QLabel *C_label = new QLabel(this);
    C_label->setGeometry(80, 250, 20, 20);
    C_label->setText("C:");

    QLabel *C_x_label = new QLabel(this);
    C_x_label->setGeometry(120, 250, 20, 20);
    C_x_label->setText("x");

    C_x = new QLineEdit(this);
    C_x->setGeometry(140, 250, 30, 30);
    C_x->setText("5");

    QLabel *C_y_label = new QLabel(this);
    C_y_label->setGeometry(240, 250, 20, 20);
    C_y_label->setText("y");

    C_y = new QLineEdit(this);
    C_y->setGeometry(260, 250, 30, 30);
    C_y->setText("-1");

    QLabel *C_z_label = new QLabel(this);
    C_z_label->setGeometry(360, 250, 20, 20);
    C_z_label->setText("z");

    C_z = new QLineEdit(this);
    C_z->setGeometry(380, 250, 30, 30);
    C_z->setText("-1");


    QLabel *D_label = new QLabel(this);
    D_label->setGeometry(80, 290, 20, 20);
    D_label->setText("D:");

    QLabel *D_x_label = new QLabel(this);
    D_x_label->setGeometry(120, 290, 20, 20);
    D_x_label->setText("x");

    D_x = new QLineEdit(this);
    D_x->setGeometry(140, 290, 30, 30);
    D_x->setText("1");

    QLabel *D_y_label = new QLabel(this);
    D_y_label->setGeometry(240, 290, 20, 20);
    D_y_label->setText("y");

    D_y = new QLineEdit(this);
    D_y->setGeometry(260, 290, 30, 30);
    D_y->setText("-2");

    QLabel *D_z_label = new QLabel(this);
    D_z_label->setGeometry(360, 290, 20, 20);
    D_z_label->setText("z");

    D_z = new QLineEdit(this);
    D_z->setGeometry(380, 290, 30, 30);
    D_z->setText("3");


    if(rb_formula->isChecked()){
        rb_formulaClicked();
    }

    okButton = new QPushButton(this);
    okButton->setText("OK");
    okButton->setGeometry(width() - 50, height() - 50, 40, 40);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(okButtonClicked()));

}

void AddFormula::okButtonClicked(){
    if(rb_formula->isChecked()){
        formula = formula_part1->text() + symbol->currentText() + formula_part2->text();
        father->showFigures(formula);
    }
    if(rb_points->isChecked()){
        father->setTetraider(initTetraider());
        father->addSection();
    }
    close();
}

Tetraider* AddFormula::initTetraider() {
    //Tetraider* tetraider = new Tetraider(new Point(2, 1, -1), new Point(3, 2, -1), new Point(5, -1, -1), new Point(1, -2, 3));
    Tetraider* tetraider = new Tetraider(new Point(A_x->text().toDouble(), A_y->text().toDouble(), A_z->text().toDouble()),
                                         new Point(B_x->text().toDouble(), B_y->text().toDouble(), B_z->text().toDouble()),
                                         new Point(C_x->text().toDouble(), C_y->text().toDouble(), C_z->text().toDouble()),
                                         new Point(D_x->text().toDouble(), D_y->text().toDouble(), D_z->text().toDouble()));
    tetraider->calcLines();
    return tetraider;
}

void AddFormula::rb_formulaClicked(){
    A_x->setReadOnly(true);
    A_y->setReadOnly(true);
    A_z->setReadOnly(true);
    B_x->setReadOnly(true);
    B_y->setReadOnly(true);
    B_z->setReadOnly(true);
    C_x->setReadOnly(true);
    C_y->setReadOnly(true);
    C_z->setReadOnly(true);
    D_x->setReadOnly(true);
    D_y->setReadOnly(true);
    D_z->setReadOnly(true);

    formula_part1->setReadOnly(false);
    formula_part2->setReadOnly(false);
    symbol->setDisabled(false);
}

void AddFormula::rb_pointsClicked(){
    A_x->setReadOnly(false);
    A_y->setReadOnly(false);
    A_z->setReadOnly(false);
    B_x->setReadOnly(false);
    B_y->setReadOnly(false);
    B_z->setReadOnly(false);
    C_x->setReadOnly(false);
    C_y->setReadOnly(false);
    C_z->setReadOnly(false);
    D_x->setReadOnly(false);
    D_y->setReadOnly(false);
    D_z->setReadOnly(false);

    formula_part1->setReadOnly(true);
    formula_part2->setReadOnly(true);
    symbol->setDisabled(true);
}

MainWindow *AddFormula::getFather() const
{
    return father;
}

void AddFormula::setFather(MainWindow *value)
{
    father = value;
}

void AddFormula::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return){
            okButtonClicked();
    }
    if(event->key() == Qt::Key_Right){
        this->focusNextChild();
    }
    if(event->key() == Qt::Key_Left){
        this->focusPreviousChild();
    }
    if(event->key() == Qt::Key_Down && rb_formula->isChecked()){
        rb_points->setChecked(true);
        rb_pointsClicked();
    }
    if(event->key() == Qt::Key_Up && rb_points->isChecked()){
        rb_formula->setChecked(true);
        rb_formulaClicked();
    }
}
