#include "sectionwindow.h"
#include "ui_sectionwindow.h"

SectionWindow::SectionWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SectionWindow)
{
    ui->setupUi(this);

    setWindowTitle("Сечения");

    init();
}

void SectionWindow::init(){

//    ui->widget->setFather(this);

    slider = new QSlider(Qt::Vertical, this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    slider->setSingleStep(1);
    slider->setGeometry(50, 20, 20, 600);
    slider->setMinimum(0);
    slider->setMaximum(300);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderClicked(int)));

    d = 0;

    QLabel *sliderLabel = new QLabel(this);
    sliderLabel->setGeometry(50, 630, 10, 10);
    sliderLabel->setText("d");
    sliderLabel->show();
}

int SectionWindow::getD() const
{
    return d;
}

MainWindow *SectionWindow::getFather() const
{
    return father;
}

void SectionWindow::setFather(MainWindow *value)
{
    father = value;
}

void SectionWindow::sliderClicked(int a){
    d = a;
    ui->widget->update();
}

QSlider *SectionWindow::getSlider() const
{
    return slider;
}

void SectionWindow::setTetraider(Tetraider* tetraider) {
    this->tetraider = tetraider;
}

Tetraider* SectionWindow::getTetraider(){
    return this->tetraider;
}

SectionWindow::~SectionWindow()
{
    delete ui;
}

void SectionWindow::updateWidget(){
    tetraider = father->getTetraider();
    ui->widget->setAllPointsVect(tetraider->getAllPointsVect());
    ui->widget->setIsComplate(true);
}

