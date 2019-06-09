#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Поверхности второго порядка");

    init();
}

MainWindow::~MainWindow()
{    
    delete ui;
}

void MainWindow::init(){

    float h = this->height();

    this->setAttribute(Qt::WA_DeleteOnClose);

    QPushButton *addFormulaButton = new QPushButton(this);
    addFormulaButton->setGeometry(20, 20, 30, 30);
    addFormulaButton->setText("+");
    connect(addFormulaButton, SIGNAL(clicked()), this, SLOT(addFormulaWindow()));

    QPushButton *sectionButton = new QPushButton(this);
    sectionButton->setGeometry(60, 20, 80, 30);
    sectionButton->setText("Сечения");
    connect(sectionButton, SIGNAL(clicked()), this, SLOT(addSectionsWindow()));

    numForDelObj = new QLineEdit(this);
    numForDelObj->setGeometry(20, 60, 30, 30);

    QPushButton *delOneObjButton = new QPushButton(this);
    delOneObjButton->setGeometry(60, 60, 30, 30);
    delOneObjButton->setText("-");
    connect(delOneObjButton, SIGNAL(clicked()), this, SLOT(delOneObj()));

    QPushButton *delLastObjButton = new QPushButton(this);
    delLastObjButton->setGeometry(20, 100, 30, 30);
    delLastObjButton->setText("-last");
    connect(delLastObjButton, SIGNAL(clicked()), this, SLOT(delLastObj()));

    QPushButton *delAllObjButton = new QPushButton(this);
    delAllObjButton->setGeometry(20, 140, 30, 30);
    delAllObjButton->setText("-all");
    connect(delAllObjButton, SIGNAL(clicked()), this, SLOT(delAllObj()));

    QLabel *deltaEpsLabel = new QLabel(this);
    deltaEpsLabel->setText("Текущие значения eps и delta:");
    deltaEpsLabel->setGeometry(20, h - 160, 200, 30);
    deltaEpsLabel->show();

    QLabel *epsLabel = new QLabel(this);
    epsLabel->setText("eps:");
    epsLabel->setGeometry(20, h - 100, 50, 30);
    epsLabel->show();

    QLabel *deltaLabel = new QLabel(this);
    deltaLabel->setText("delta:");
    deltaLabel->setGeometry(110, h - 100, 50, 30);
    deltaLabel->show();

    deltaNum = new QLineEdit(this);
    deltaNum->setGeometry(150, h - 100, 50, 30);

    epsNum = new QLineEdit(this);
    epsNum->setGeometry(50, h - 100, 50, 30);

    QPushButton *deltaEpsButton = new QPushButton(this);
    deltaEpsButton->setGeometry(220, h - 100, 30, 30);
    deltaEpsButton->setText("OK");
    connect(deltaEpsButton, SIGNAL(clicked()), this, SLOT(setDeltaEps()));

    currDeltaLabel = new QLabel(this);
    QString currDeltaStr = QString::number(ui->widgeto->getDelta());
    currDeltaLabel->setText(currDeltaStr);
    currDeltaLabel->setGeometry(120, h - 140, 50, 30);
    currDeltaLabel->show();

    currEpsLabel = new QLabel(this);
    QString currEpsStr = QString::number(ui->widgeto->getEpsilon());
    currEpsLabel->setText(currEpsStr);
    currEpsLabel->setGeometry(30, h - 140, 50, 30);
    currEpsLabel->show();

    allObj = new Group3D();

    //m_objects = new QVector<Object3D *>();
    m_all_nums = new double*[100];

    numOfWinds = 0;

    choosePlaneSec = 0;

    ui->widget->setFather(this);
    ui->widgeto->setFather(this);

    slider = new QSlider(Qt::Vertical, this);
    slider->setFocusPolicy(Qt::StrongFocus);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    slider->setSingleStep(1);
    slider->setGeometry(250, 40, 20, 730);
    slider->setMinimum(0);
    slider->setMaximum(300);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderClicked(int)));

    isTetraider = false;

    d = 0;


    QPushButton *x_plane = new QPushButton(this);
    x_plane->setGeometry(1120, h - 900, 100, 30);
    x_plane->setText("XY");
    connect(x_plane, SIGNAL(clicked()), this, SLOT(xyPlaneChoose()));

    QPushButton *y_plane = new QPushButton(this);
    y_plane->setGeometry(1250, h - 900, 100, 30);
    y_plane->setText("YZ");
    connect(y_plane, SIGNAL(clicked()), this, SLOT(yzPlaneChoose()));

    QPushButton *z_plane = new QPushButton(this);
    z_plane->setGeometry(1380, h - 900, 100, 30);
    z_plane->setText("XZ");
    connect(z_plane, SIGNAL(clicked()), this, SLOT(xzPlaneChoose()));

    QPushButton *sec_plane = new QPushButton(this);
    sec_plane->setGeometry(1510, h - 900, 100, 30);
    sec_plane->setText("Section plane");
    connect(sec_plane, SIGNAL(clicked()), this, SLOT(secPlaneChoose()));
}


void MainWindow::sliderClicked(int a){
    d = a;
    ui->widget->update();
    ui->widgeto->update();
}

int MainWindow::getD() const
{
    return d;
}

void MainWindow::addFormulaWindow(){
    AddFormula *formulaWindow = new AddFormula();
    formulaWindow->setFather(this);
    formulaWindow->show();

    formulaWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(destroyed()), formulaWindow, SLOT(close()));
}

void MainWindow::addSection(){
    ui->widget->setAllPointsVect(tetraider->getAllPointsVect());
    ui->widget->setIsComplate(true);
    ui->widget->update();

    ui->widgeto->setAllPointsVect(tetraider->getAllPointsVect());
    ui->widgeto->setStartSection(true);
    ui->widgeto->update();
}

/*
 * x - 0
 * y - 1
 * z - 2
 * x^2 - 3
 * y^2 - 4
 * z^2 - 5
 * x0 - 6
 * y0 - 7
 * z0 - 8
 * r^2(св чл) - 9
 * a^2 - 10
 * b^2 - 11
 * c^2 - 12
*/
void MainWindow::showFigures(QString formula){
    for(int i = 0; i < formula.length(); i++){
        if(formula.at(i) == "\n" || formula.at(i) == " "){
            formula.remove(i, 1);
        }
    }

    double *nums = fromFormula(formula);

    setMAllNums(nums);

    ui->widgeto->initFigures(nums, nullptr, allObj);

    setLabels();
}

void MainWindow::setTetraider(Tetraider* tetraider) {
    double *nums = new double[13];
    for(int i = 0; i < 13; i++){
        nums[i] = 0;
    }

    setMAllNums(nums);

    this->tetraider = tetraider;

    isTetraider = true;

    ui->widgeto->initFigures(nums, tetraider, allObj);

    setLabels();
}

double* MainWindow::fromFormula(QString formula){
    double *nums = new double[13];
    QString num;
    QString lets[] = {"x", "y", "z"};
    int i = 1;
    int indX;

    nums[10] = 0;
    nums[11] = 0;
    nums[12] = 0;
    nums[6] = 0;
    nums[7] = 0;
    nums[8] = 0;

    for(int j = 0; j < 3; ++j){
        //для формулы (x+x0)^2...
        int ind = formula.indexOf(lets[j]);

        int isPow2 = 0;

        if( (ind + 1) < formula.length() || formula.at(ind + 1) != "/" || formula.at(ind + 1) != "*" ){
            if( formula.at(ind + 1) == ")" && formula.at(ind + 2) == "^"){
                // (a+x)^2/...
                if( formula.at(ind + 4) == "*" ){
                    // (a+x)^2*2... || (a+x)^2*(1/2)... || (a+x)^2*(23/24)...
                    double chislit = 1, znamenat = 1;
                    for(int i = 5; formula.at(ind + i).isNumber() || formula.at(ind + i) == "(" || formula.at(ind + i) == "." || formula.at(ind + i) == "," || formula.at(ind + i) == "/"; i++){
                        if( formula.at(ind + i) == "(" ){
                        }else if( formula.at(ind + i) == "/" ){
                            chislit = num.toDouble();
                            num = "";
                        }else{
                            num.push_back(formula.at(ind + i));
                        }
                    }
                    znamenat = num.toDouble();
                    nums[j + 10] = znamenat / chislit;
                }

                int isMinus = 0;
                if((ind + 1) < formula.length()){
                    if(formula.at((ind + 1)) == ")"){
                        for(i = 2; (formula.at(ind - i)).isNumber() || formula.at(ind - i) == "." || formula.at(ind - i) == ","; i++){
                            num.push_front(formula.at(ind - i));
                            isMinus = ind - i;
                        }
                        if(formula.at(isMinus - 1) == "("){
                            num.push_front("-");
                        }
                        nums[j+6] = num.toInt();
                        num = "";
                    }
                    if(formula.at((ind + 1)) == "^"){
                        nums[j+6] = 0;
                    }
                }
                if(formula.at(ind + 4) == "/"){
                    nums[j + 10] = findDel(ind + 1, formula);
                }
            }else if( formula.at(ind + 1) == "^" ){
                if( (ind - 1) >= 0 ){
                    if(formula.at(ind - 1) == "*"){
                        double chislit = 1, znamenat = 1;
                        for(int i = 2; (ind - i) >= 0 && (formula.at(ind - i).isNumber() || formula.at(ind - i) == ")" || formula.at(ind - i) == "." || formula.at(ind - i) == "," || formula.at(ind - i) == "/"); i++){
                            if( formula.at(ind - i) == ")" ){
                            }else if( formula.at(ind - i) == "/" ){
                                znamenat = num.toDouble();
                                num = "";
                            }else{
                                num.push_front(formula.at(ind - i));
                            }
                        }
                        chislit = num.toDouble();
                        num = "";
                        nums[j + 10] = znamenat / chislit;
                    }
                }

                if(formula.at(ind + 3) == "/" ){
                    // x^2/...
                    nums[j + 10] = findDel(ind, formula);
                }
                if(formula.at(ind + 3) == "*" ){
                    // x^2*...
                    double chislit = 1, znamenat = 1;
                    for(int i = 4; formula.at(ind + i).isNumber() || formula.at(ind + i) == "(" || formula.at(ind + i) == "." || formula.at(ind + i) == "," || formula.at(ind + i) == "/"; i++){
                        if( formula.at(ind + i) == "(" ){
                        }else if( formula.at(ind + i) == "/" ){
                            chislit = num.toDouble();
                            num = "";
                        }else{
                            num.push_back(formula.at(ind + i));
                        }
                    }
                    znamenat = num.toDouble();
                    num = "";
                    nums[j + 10] = znamenat / chislit;
                }
            }else if( formula.at(ind + 1) == "+" || formula.at(ind + 1) == "-" ){
                if( (ind - 1) >= 0 ){
                    if( formula.at(ind - 1) == "(" ){
                        // (x+a)^2...
                        if( ind - 2 > 0){
                            if( formula.at(ind - 2) == "*" ){
                                // 2*(x+a)^2... || (1/2)*(x+a)^2... || (23/24)*(x+a)^2...
                                double chislit = 1, znamenat = 1;
                                for(int i = 3; formula.at(ind - i).isNumber() || formula.at(ind - i) == ")" || formula.at(ind - i) == "." || formula.at(ind - i) == "," || formula.at(ind - i) == "/"; i++){
                                    if( formula.at(ind - i) == ")" ){
                                    }else if( formula.at(ind - i) == "/" ){
                                        znamenat = num.toDouble();
                                        num = "";
                                    }else{
                                        num.push_front(formula.at(ind - i));
                                    }
                                }
                                chislit = num.toDouble();
                                num = "";
                                nums[j + 10] = znamenat / chislit;
                            }
                        }else{
                            //scscsacacasccccccccccccccccccccccccsaaaaaaaaaaaaaaaaaa
                        }

                        if(formula.at(ind + 1) == "+"){
                            num.push_back("-");
                        }
                        int indSkobka;
                        for(i = 2; (formula.at(ind + i)).isNumber() || formula.at(ind + i) == "." || formula.at(ind + i) == ","; i++){
                            num.push_back(formula.at(ind + i));
                            indSkobka = i + 1 + ind;
                        }
                        nums[j+6] = num.toInt();
                        num = "";

                        // нашли a + сохранили indSkobka ")"
                        if( formula.at(indSkobka + 1)== "^" && formula.at(indSkobka + 3) == "/"){
                            nums[j + 10] = findDel(indSkobka, formula);
                        }
                    }else{
                        //значит x - не в квадрате
                        nums[j+6] = 0;
                        isPow2 = ind;
                    }
                }else{
                    //значит x - не в квадрате
                    nums[j+6] = 0;
                    isPow2 = ind;
                }
            }else{
                //значит x - не в квадрате
                nums[j+6] = 0;
                isPow2 = ind;
            }
        } else {
            //значит x - не в квадрате
            nums[j+6] = 0;
            isPow2 = ind;
        }

        if(formula.indexOf(lets[j]) != formula.lastIndexOf(lets[j]) || isPow2 != 0){
            int k = 1;
            if(formula.indexOf(lets[j]) != formula.lastIndexOf(lets[j])){
                ind = formula.lastIndexOf(lets[j]);
            }else{
                ind = isPow2;
            }
            if(ind != -1){
                if((ind - 1) >= 0){
                    if(formula.at(ind - 1).isNumber() || formula.at(ind - 1) == "*"){
                        if(formula.at(ind - 1) == "*"){
                            ++k;
                        }
                        for(k; (ind - k) >= 0; ++k){
                            if(formula.at(ind - k).isNumber() || formula.at(ind - k) == "-"){
                                num.push_front(formula.at(ind - k));
                                if(formula.at(ind - k) == "-"){
                                    break;
                                }
                            }else{
                                break;
                            }
                        }
                        nums[j] = num.toInt();
                    }else if(formula.at(ind + 1) == "*") {
                        ++k;
                        for(k; (ind + k) < formula.length(); ++k){
                            if(formula.at(ind + k).isNumber()){
                                num.push_back(formula.at(ind + k));
                            }else{
                                break;
                            }
                        }
                        nums[j] = num.toInt();
                    }else if(formula.at(ind - 1) == "-"){
                        nums[j] = -1;
                    }else{
                        nums[j] = 1;
                    }
                    k = 1;
                    num = "";
                }else{
                    nums[j] = 0;
                }
            }
        }else{
            nums[j] = 0;
        }
    }
    //свободный член
    indX = formula.length() - 1;
    for(i = 0; (indX - i) >= 0; i++){
        if(formula.at(indX - i).isNumber() || formula.at(indX - i) == "." || formula.at(indX - i) == ","){
            num.push_front(formula.at(indX - i));
        }else{
            break;
        }
    }
    nums[9] = num.toDouble();
    return nums;
}
/*
 * x - 0
 * y - 1
 * z - 2
 * x^2 - 3
 * y^2 - 4
 * z^2 - 5
 * x0 - 6
 * y0 - 7
 * z0 - 8
 * r^2(св чл) - 9
 * a^2 - 10
 * b^2 - 11
 * c^2 - 12
*/

int MainWindow::findDel(int ind, QString formula){
    QString num;
    double chislo;
    for(int i = 4; formula.at(ind + i).isNumber() || formula.at(ind + i) == "." || formula.at(ind + i) == ","; i++){
        num.push_back(formula.at(ind + i));
    }
    if(ind - 1 >= 0){
        if(formula.at(ind - 1) == "-"){
            num.push_front("-");
        }
    }
    /*if(ind - 2 >= 0){
        if(formula.at(ind - 2) == "-"){
            num.push_front("-");
        }
    }*/
    return chislo = num.toDouble();
}

//void MainWindow::setAllObj(Objects *value)
//{
//    allObj = value;
//}

void MainWindow::delOneObj(){
    if(!numForDelObj->text().isEmpty() && numForDelObj->text().toInt() < allObj->numOfObj()){
        if(allObj->objAt(numForDelObj->text().toInt())->getType() == "tetraider"){
            delTetraider();
        }
        allObj->delObj(numForDelObj->text().toInt());
        labelShow();
        ui->widgeto->update();
        ui->widget->update();
    }
}

void MainWindow::delLastObj(){
    if(allObj->objAt(allObj->numOfObj() - 1)->getType() == "tetraider"){
        delTetraider();
    }
    allObj->delLastObj();
    labelShow();
    ui->widgeto->update();
    ui->widget->update();
}

void MainWindow::delAllObj(){
    allObj->delAllObj();
    labelShow();
    if(isTetraider){
        delTetraider();
    }
    ui->widgeto->update();
    ui->widget->update();
}

void MainWindow::delTetraider(){
    delete tetraider;
    ui->widgeto->deleteAllPointsVect();
    ui->widget->deleteAllPointsVect();
    ui->widgeto->setStartSection(false);
    ui->widget->setIsComplate(false);
    isTetraider = false;
}

int MainWindow::getChoosePlaneSec() const
{
    return choosePlaneSec;
}

void MainWindow::setChoosePlaneSec(int value)
{
    choosePlaneSec = value;
}

void MainWindow::setMAllNums(double *nums){
    if(allObj->numOfObj() == 0){
        m_all_nums[allObj->numOfObj()] = new double[13];
    }else{
        m_all_nums[allObj->numOfObj() - 1] = new double[13];
    }

    for(int i = 0; i < 13; i++){
        if(allObj->numOfObj() == 0){
            m_all_nums[allObj->numOfObj()][i] = nums[i];
        }else{
            m_all_nums[allObj->numOfObj() - 1][i] = nums[i];
        }
    }
}

void MainWindow::setDeltaEps(){
    if(epsNum->text() != ""){
        ui->widgeto->setEpsilon(epsNum->text().toDouble());
    }
    if(deltaNum->text() != ""){
        ui->widgeto->setDelta(deltaNum->text().toDouble());
    }

    QString newEps = QString::number(ui->widgeto->getEpsilon());
    currEpsLabel->setText(newEps);
    QString newDelta = QString::number(ui->widgeto->getDelta());
    currDeltaLabel->setText(newDelta);
    ui->widgeto->update();
}

void MainWindow::setLabels(){
    if(allObj->objAt(allObj->numOfObj() - 1)->getType() != "points"){
        QLabel *lb = new QLabel(this);
        QString str = "obj - " + allObj->objAt(allObj->numOfObj() - 1)->getType();
        lb->setText(str);
        allObj->objAt(allObj->numOfObj() - 1)->setLabel(lb);

        QLabel *lb2 = new QLabel(this);
        double res = allObj->objAt(allObj->numOfObj() - 1)->getRes();
        QString resStr = QString::number(res);
        lb2->setText("result = " + resStr);
        allObj->objAt(allObj->numOfObj() - 1)->setLabRes(lb2);
        labelShow();
    }
}

void MainWindow::labelShow(){

    int h1 = 130, h2 = 160;
    for(int i = 1; i < allObj->numOfObj(); i++){

        allObj->objAt(i)->getLabel()->setGeometry(20, h1 + 80 * i, 100, 30);
        allObj->objAt(i)->getLabel()->adjustSize();
        allObj->objAt(i)->getLabel()->setGeometry(20, h1 + 80 * i, allObj->objAt(i)->getLabel()->width(), 30);
        allObj->objAt(i)->getLabel()->show();

        allObj->objAt(i)->getLabRes()->setGeometry(20, h2 + 80 * i, 100, 30);
        allObj->objAt(i)->getLabRes()->adjustSize();
        allObj->objAt(i)->getLabRes()->setGeometry(20, h2 + 80 * i, allObj->objAt(i)->getLabRes()->width(), 30);
        allObj->objAt(i)->getLabRes()->show();
        //allObj->objAt(i)->getColorLabel()->setStyleSheet("background-color: rgb(" + allObj->objAt(i)->getColorStr() + ")");
        //allObj->objAt(i)->getColorLabel()->setGeometry(40 + allObj->objAt(i)->getLabel()->width(), allObj->objAt(i)->getLabel()->y() + allObj->objAt(i)->getLabel()->height() - 20, 20, 20);
        //allObj->objAt(i)->getColorLabel()->show();
    }
}

double **MainWindow::getAll_nums() const
{
    return m_all_nums;
}

void MainWindow::setNumOfWinds(int value)
{
    numOfWinds = value;
}

int MainWindow::getNumOfWinds() const
{
    return numOfWinds;
}

Tetraider* MainWindow::getTetraider(){
    return this->tetraider;
}

Group3D *MainWindow::getAllObj() const
{
    return allObj;
}

void MainWindow::xyPlaneChoose(){
    choosePlaneSec = 0;
    ui->widget->update();
}

void MainWindow::yzPlaneChoose(){
    choosePlaneSec = 1;
    ui->widget->update();
}

void MainWindow::xzPlaneChoose(){
    choosePlaneSec = 2;
    ui->widget->update();
}

void MainWindow::secPlaneChoose(){
    choosePlaneSec = 3;
    ui->widget->update();
}

void MainWindow::changePlaneSec(int choose){

}
