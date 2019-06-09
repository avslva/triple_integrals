#include "largewidget.h"
#include "ui_largewidget.h"

largeWidget::largeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::largeWidget)
{
    ui->setupUi(this);

    setWindowState(Qt::WindowMaximized);
    ui->widgeti->resize(1900, 990);

    allObj = new Group3D();
}

largeWidget::~largeWidget()
{
    delete ui;
}

MainWindow *largeWidget::getFather() const
{
    return father;
}

void largeWidget::setFather(MainWindow *value)
{
    father = value;
    ui->widgeti->setFather(father);
    //allObj = father->getAllObj();
    //int t = father->getAllObj()->numOfObj();

    //ui->widgeti->initFiguresFromLW(getFather()->getAll_nums(), allObj, father->getAllObj()->numOfObj());

    //ui->widgeti->initFiguresFromLW(allObj);
}

void largeWidget::closeEvent(QCloseEvent *event){

    father->setNumOfWinds(father->getNumOfWinds() - 1);
    event->accept();
}
