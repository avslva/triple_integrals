#include "widget.h"
#include <QOpenGLContext>
#include <object3d.h>
#include <group3d.h>
#include <camera3d.h>
#include <transformational.h>

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_camera = new Camera3D;
    m_camera->translate(QVector3D(0.0f, 0.0f, -5.0f));
    isDraw = false;
    //points = new QVector3D();
}


Widget::~Widget()
{
    delete m_camera;
    for(int i = 0; i < m_objects.size(); i++){
        delete m_objects[i];
    }
    for(int i = 0; i < m_groups.size(); i++){
        delete m_groups[i];
    }
    for(int i = 0; i < m_transformObjects.size(); i++){
        delete m_transformObjects[i];
    }
}

/*void Widget::initFiguresFromLW(double** nums, Group3D *grupa, int size){
    for (int i = 0; i < 13; i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << " !!!!!!!!!! \n";
    //int e = grupa->numOfObj();
    if(grupa->numOfObj() == 0){
        initMainLines();
        grupa->addObj(m_objects[0]);
        m_groups.append(grupa);
    }
    for(int i = 0; i < size - 1; i++){
        //сфера
        if(nums[i][10] == 0 && nums[i][11] == 0 && nums[i][12] == 0){
            initSphera(nums[i][9]);
            m_objects[m_objects.size() - 1]->translate(QVector3D(nums[i][6], nums[i][7], nums[i][8]));
            grupa->addObject(m_objects[m_objects.size() - 1]);
            m_groups.append(grupa);
        }
    }
    m_transformObjects.append(m_groups[0]);
    update();
}*/
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

void Widget::initFigures(double* nums, Tetraider *tetraider, Group3D *grupa){
    if(grupa->numOfObj() == 0){
        initMainLines();
        grupa->addObj(m_objects[0]);
        m_groups.append(grupa);
        //vert = new QVector<VertexData>[10];
    }

    QString type;
    double res = 0;

    if(tetraider != nullptr){
        initTetraider(tetraider);
        type = "tetraider";
        res = tetraider->calcV();
    }else if(nums[10] == 0 && nums[11] == 0 && nums[12] == 0){
        initSphera(sqrt(nums[9]));
        type = "sphera";
    }else if(nums[10] != 0 && nums[11] != 0 && nums[2] == -1 && nums[12] == 0 && nums[9] == 0){
        //initParaboloid1(sqrt(nums[10]), sqrt(nums[11]), 3.0);
        initParaboloid2(sqrt(nums[10]), sqrt(nums[11]), 3.0);
        type = "paraboloid";
    }else if(nums[10] != 0 && nums[11] != 0 && nums[2] == 0 && nums[12] != 0 && nums[9] == 1){
        initEllipsoid(sqrt(nums[10]), sqrt(nums[11]), sqrt(nums[12]));
        type = "ellipsoid";
    }else if(nums[10] != 0 && nums[11] != 0 && nums[12] == 0 && nums[9] == 1){
        initCylinder(sqrt(nums[10]), sqrt(nums[11]), 3.0);
        type = "cylinder";
    }else if(nums[10] != 0 && nums[11] != 0 && nums[12] < 0 && nums[9] == 0){
        initConus(sqrt(nums[10]), sqrt(nums[11]), sqrt(-nums[12]));
        type = "conus";
    }

    if(tetraider == nullptr){
        m_objects[m_objects.size() - 1]->translate(QVector3D(nums[6], nums[7], nums[8]));
    }
    grupa->addObject(m_objects[m_objects.size() - 1]);
    m_transformObjects.append(m_groups[0]);

    grupa->objAt(grupa->numOfObj() - 1)->setType(type);
    grupa->objAt(grupa->numOfObj() - 1)->setRes(res);

    update();

    /*if(grupa->numOfObj() == 3){
        if(initCrossPoints(vert) != 0){
            type = "points";
            m_objects[m_objects.size() - 1]->translate(QVector3D(nums[6], nums[7], nums[8]));
            grupa->addObject(m_objects[m_objects.size() - 1]);
            m_transformObjects.append(m_groups[0]);
            grupa->objAt(grupa->numOfObj() - 1)->setType(type);
            update();
        }
    }*/
}

void Widget::initTetraider(Tetraider* tetraider){
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(tetraider->A->x, tetraider->A->y, tetraider->A->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->B->x, tetraider->B->y, tetraider->B->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->C->x, tetraider->C->y, tetraider->C->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->A->x, tetraider->A->y, tetraider->A->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->D->x, tetraider->D->y, tetraider->D->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->B->x, tetraider->B->y, tetraider->B->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->D->x, tetraider->D->y, tetraider->D->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(tetraider->C->x, tetraider->C->y, tetraider->C->z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        indexes.append(i);
    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

double Widget::f(double* nums, double x, double z) {
    // y = sqrt(R^2 - (y-y0)^2 - (x-x0)^2) + z0;
    double r = 0;
    double l = nums[9] - pow((z - nums[8]), 2) - pow((x - nums[6]), 2);
    if (!(l < 0 && l > -this->epsilon)) {
        r = sqrt(l);
    }
    return 2*r;
}

double Widget::v(double* nums) {
    double  xl, xr;
    double v=0, s0;
    // z [z0 - R; z0 + R]
    for (double z = nums[8] - sqrt(nums[9]); z <= nums[8] + sqrt(nums[9]); z += this->delta) {
        s0 = 0;
        xl = nums[6] - sqrt(nums[9] - pow(z-nums[8], 2));
        xr = nums[6] + sqrt(nums[9] - pow(z-nums[8], 2));
        for (double x = xl ; x <= xr; x += this->epsilon) {
            s0 += this->f(nums, x, z)  * this->epsilon;
        }
        v += s0 * this->delta;
    }
    return v;
}

double Widget::getEpsilon() const
{
    return epsilon;
}

void Widget::setEpsilon(double value)
{
    epsilon = value;
}

double Widget::getDelta() const
{
    return delta;
}

void Widget::setDelta(double value)
{
    delta = value;
}

/*int Widget::initCrossPoints(QVector<VertexData> *vert){
    QVector<VertexData> vertexes;
    for(int i = 0; i < vert[0].size(); i++){
        for(int j = 0; j < vert[1].size(); ++j){
            if(vert[0].at(i).position == vert[1].at(j).position){
               vertexes.append(vert[0].at(j));
               points->setX(vert[0].at(j).position.x());
               points->setY(vert[0].at(j).position.y());
               points->setZ(vert[0].at(j).position.z());
            }
        }
    }
    if(vertexes.size() != 0){
        QVector<GLuint> indexes;

        for(int i = 0; i < vertexes.size(); i++){
            indexes.append(i);
        }

        int isPaint = 5;

        m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));

        return 1;
    }else{
        return 0;
    }
}*/


void Widget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
}

void Widget::resizeGL(int w, int h)
{
    double aspect = w / (h ? (double)h : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 100.0f);    //0.01 и 100 - плоскости отсечения
}


void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 0.6f, 0.7f, 1.0f);

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);

    m_camera->draw(&m_program);

    /*glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 10.0f, 0.0f);
    glEnd();*/

    //int i = points->length();
    /*if(points->length() != 0){
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for(int i = 0; i < vert->length() || !points[i].isNull(); i++){
            if(points[i].x() > -100 && points[i].x() < 100 && points[i].y() > -100 && points[i].y() < 100 && points[i].z() > -100 && points[i].z() < 100){
                glVertex3f(points[i].x(), points[i].y(), points[i].z());
            }
        }
        glEnd();
    }*/

    for(int i = 0; i < m_transformObjects.size(); i++){
        m_transformObjects[i]->draw(&m_program, context()->functions());
    }

    if (this->isStartSection) {
        drawSection();
    }
}

void Widget::drawSection() {
    int d = father->getD();

    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.3, 0.0);

    for(int i = 0; i < allPointsVect.at(d).size(); i++){
        glVertex3f(allPointsVect.at(d).at(i)->x, allPointsVect.at(d).at(i)->y, allPointsVect.at(d).at(i)->z);
    }
    for(int i = allPointsVect.at(d).size() - 1; i >= 0; i--){
        glVertex3f(allPointsVect.at(d).at(i)->x, allPointsVect.at(d).at(i)->y, allPointsVect.at(d).at(i)->z);
    }

    glEnd();
}

void Widget::setStartSection(bool isStartSection ) {
    this->isStartSection = isStartSection;
}

void Widget::setAllPointsVect(const QVector<QVector<Point *>> &value) {
    allPointsVect = value;
}


void Widget::initShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "://vshader.vsh"))
        close();

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "://fshader.fsh"))
        close();

    if (!m_program.link())
        close();

   // if (!m_program.bind())
     //   close();
}


//void Widget::initCylinder(double radius, double height){
//    double height_div_2 = height / 2.0f;

//    QVector<VertexData> vertexes;
//    for (int i = 0; i <= 362 ; i++)
//    {
//        vertexes.append(VertexData(QVector3D(radius * cos((double)i / 360.0f*3.1415f*2.0f), -height_div_2, radius * sin((double)i / 360.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.0,  sin((double)i / 360.0f*3.1415f*2.0f))));
//        vertexes.append(VertexData(QVector3D(radius * cos((double)i / 360.0f*3.1415f*2.0f), height_div_2, radius * sin((double)i / 360.0f*3.1415f*2.0f)), QVector2D(0.0, 1.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.0,  sin((double)i / 360.0f*3.1415f*2.0f))));
//    }

//    QVector<GLuint> indexes;

//    for(int i = 0; i < vertexes.size() - 1; i++){
//        indexes.append(i);
//    }

//    int isPaint = 1;

//    m_objects.append(new Object3D(vertexes, indexes, QImage(":/cube.png"), isPaint));
//}

//void Widget::initCylinder(double a, double b, double height){
//    double height_div_2 = height / 2.0f;

//    QVector<VertexData> vertexes;
//    for (int i = 0; i <= 362 ; i++)
//    {
//        vertexes.append(VertexData(QVector3D(a * cos((double)i / 360.0f*3.1415f*2.0f), -height_div_2, b * sin((double)i / 360.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.0,  sin((double)i / 360.0f*3.1415f*2.0f))));
//        vertexes.append(VertexData(QVector3D(a * cos((double)i / 360.0f*3.1415f*2.0f), height_div_2, b * sin((double)i / 360.0f*3.1415f*2.0f)), QVector2D(0.0, 1.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.0,  sin((double)i / 360.0f*3.1415f*2.0f))));
//    }

//    QVector<GLuint> indexes;

//    for(int i = 0; i < vertexes.size() - 1; i++){
//        indexes.append(i);
//    }

//    int isPaint = 1;

//    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
//}


//void Widget::initConus(double radius, double height){
//    double height_div_2 = height / 2.0f;

//    QVector<VertexData> vertexes;
//    for (int i = 0; i <= 362 ; i++)
//    {
//        vertexes.append(VertexData(QVector3D(radius * cos((double)i / 360.0f*3.1415f*2.0f), -height_div_2, radius * sin((double)i / 360.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.0,  sin((double)i / 360.0f*3.1415f*2.0f))));
//        vertexes.append(VertexData(QVector3D(0.0, height_div_2, 0.0), QVector2D(0.0, 1.0), QVector3D(cos((double)i / 360.0f*3.1415f*2.0f), 0.9,  sin((double)i / 360.0f*3.1415f*2.0f))));
//    }

//    QVector<GLuint> indexes;

//    for(int i = 0; i < vertexes.size() - 1; i++){
//        indexes.append(i);
//    }

//    int isPaint = 1;

//    m_objects.append(new Object3D(vertexes, indexes, QImage(":/cube.png"), isPaint));
//}

QVector<Object3D *> Widget::objects() const
{
    return m_objects;
}

void Widget::initParaboloid1(double a, double b, double height){
    QVector<VertexData> vertexes;

    double _a, _b, _h;
    for(int j = 0; j <= height * 10; ++j) {
        /*if(j == height * 10){
            _a = a;
            _b = b;
            _h = height;
        }else{*/
            _a = a - a/(j + 1);
            _b = b - b/(j + 1);
            _h = j/10.0;
        //}
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _h, (_b * sin((double)i / 30.0f*3.1415f*2.0f))),
                                       QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,
                                                                      sin((double)i / 30.0f*3.1415f*2.0f))));
        }
        int f_down_ellipse = 5;
        if(j == 0){
            for(int l = 1; l < f_down_ellipse; ++l){
                _a = a - a/(j + 2) - ((a - a/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
                _b = b - b/(j + 2) - ((b - b/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
                _h = ( (j + 1) / (10.0 * f_down_ellipse))*l;
                for(int i = 0; i <= 30 ; i++)
                {
                    vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _h, (_b * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
                }
            }
        }
    }

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        indexes.append(i);
    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

//void Widget::initParaboloid2(double a, double b, double height){
//    QVector<VertexData> vertexes;
//    double _a, _b, _h;
//    for(int i = 0; i <= 30 ; i++){
//        for(int j = height * 10; j >= 0; --j)  //32 - кол-во линий по y
//        {
//            /*if(j == height * 10){
//                _a = a;
//                _b = b;
//                _h = height;
//            }else{*/
//                _a = a - a/(j + 1);
//                _b = b - b/(j + 1);
//                _h = j/10.0;
//            //}
//            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _h, _b * sin((double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//            //int f_down_ellipse = 5;
//            if(j == 1){
//               /* for(int l = 1; l < f_down_ellipse; ++l){
//                    _a = a - a/(j + 2) - ((a - a/(j + 2))/(f_down_ellipse))*(l) - 0.03;
//                    _b = b - b/(j + 2) - ((b - b/(j + 2))/(f_down_ellipse))*(l) - 0.03;
//                    _h = ( (j + 1) / (10.0 * f_down_ellipse))*l;
//                    //for(int i = 0; i <= 30 ; i++)
//                    //{
//                        vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _h, (_b * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//                    //}
//                }*/
//            }
//        }

//        //vertexes.append(VertexData(QVector3D(0.0f, 0.0f, 0.0f), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

//        for(int j = 0; j <= height * 10; ++j)
//        {
//            /*if(j == height * 10){
//                _a = a;
//                _b = b;
//                _h = height;
//            }else{*/
//                _a = a - a/(j + 1);
//                _b = b - b/(j + 1);
//                _h = j/10.0;
//            //}
//            vertexes.append(VertexData(QVector3D(_a * cos(180 + (double)i / 30.0f*3.1415f*2.0f), _h, _b * sin(180 + (double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));

//            int f_down_ellipse = 5;
//            if(j == 0){
//                for(int l = 1; l < f_down_ellipse; ++l){
//                    _a = a - a/(j + 2) - ((a - a/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
//                    _b = b - b/(j + 2) - ((b - b/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
//                    _h = ( (j + 1) / (10.0 * f_down_ellipse))*l;
//                    //for(int i = 0; i <= 30 ; i++)
//                    //{
//                        vertexes.append(VertexData(QVector3D(_a * cos(180 + (double)i / 30.0f*3.1415f*2.0f), _h, _b * sin(180 + (double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//                    //}
//                }
//            }
//        }
//    }

//    QVector<GLuint> indexes;

//    for(int i = 0; i < vertexes.size() - 1; i++){
//        indexes.append(i);
//    }

//    int isPaint = 3;

//    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
//}

void Widget::initParaboloid2(double a, double b, double height){
    QVector<VertexData> vertexes;

    double _a, _b, _h;

    for(int i = 0; i <= 60 ; i++){
        //if(i % 2 == 0){
            for(int j = height * 10; j > 0; --j){
                _a = a - a/(j + 1);
                _b = b - b/(j + 1);
                _h = j/10.0;
                vertexes.append(VertexData(QVector3D(_a * cos((double)i / 60.0f*3.1415f*2.0f), _h, _b * sin((double)i / 60.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
            }

            for(int j = 0; j <= height * 10; ++j){
                _a = a - a/(j + 1);
                _b = b - b/(j + 1);
                _h = j/10.0;
                vertexes.append(VertexData(QVector3D(_a * cos(3.1415f + (double)i / 60.0f*3.1415f*2.0f), _h, _b * sin(3.1415f + (double)i / 60.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
            }
    }

    //int tmp_size = vertexes.size();

    for(int i = 0; i <= 60 ; i++){
        _a = a - a/(height * 10 + 1);
        _b = b - b/(height * 10 + 1);
        //_h = j/10.0;
        vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), height, _b * sin((double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
    }



       // }/*else{
//            for(int j = height * 10; j >= 0; --j){
//                _a = a - a/(j + 1);
//                _b = b - b/(j + 1);
//                _h = j/10.0;
//                vertexes.append(VertexData(QVector3D(_a * cos(180 + (double)i / 30.0f*3.1415f*2.0f), _h, _b * sin(180 + (double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//            }

//            for(int j = 0; j <= height * 10; ++j){
//                _a = a - a/(j + 1);
//                _b = b - b/(j + 1);
//                _h = j/10.0;
//                vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _h, _b * sin((double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));

//                int f_down_ellipse = 5;
//                if(j == 0){
//                    for(int l = 1; l < f_down_ellipse; ++l){
//                        _a = a - a/(j + 2) - ((a - a/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
//                        _b = b - b/(j + 2) - ((b - b/(j + 2))/(f_down_ellipse))*(f_down_ellipse - l) + 0.03;
//                        _h = ( (j + 1) / (10.0 * f_down_ellipse))*l;
//                        vertexes.append(VertexData(QVector3D(_a * cos(180 + (double)i / 30.0f*3.1415f*2.0f), _h, _b * sin(180 + (double)i / 30.0f*3.1415f*2.0f)), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//                    }
//                }
//            }
//        }*/


    QVector<GLuint> indexes;

    int pointsInPar = 2 * height * 10;
    int lastInd = 1000000;


    for(int i = 0; i < (vertexes.size() - 60)/ 2*pointsInPar; i++){ //vertexes.size()/ (height * 40)
        for(int j = 0; j <= pointsInPar; j++){
            indexes.append(i*(2 * pointsInPar + 2) + j);
        }
        for(int j = pointsInPar*2 + 1; j > pointsInPar; j--){
            indexes.append(i*(2 * pointsInPar + 2) + j);
            if(lastInd < (i*(2 * pointsInPar + 2) + j)){
                lastInd = i*(2 * pointsInPar + 2) + j;
            }
        }

    }

    for(int i = lastInd + 1; i < vertexes.size(); i++){
        indexes.append(i);
    }


    /*for(int i = 0; i < vertexes.size() - 1; i++){
        indexes.append(i);
    }*/
//    int k1 = 0, k2 = height * 10 * 2;
//    for(int i = 0; i < 15; i++){
//        for(int j = k1; j < k2; ++j){     //  от 0 до h*10*2
//            indexes.append(j);
//            k1 = j;
//        }
//        k2 = height * 10 * pow(2, i+2);
//        for(int j = k2; j > k1 + 1; --j){   //  от h*10*2*2 до h*10*2+1
//            indexes.append(j);
//        }
//        k1 = k2 + 1;
//    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}


void Widget::initMainLines(){
    QVector<VertexData> vertexes;

    int max_num = 10.0;

    vertexes.append(VertexData(QVector3D(-max_num, 0.0, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num, 0.0, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, -max_num, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, max_num, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.0, -max_num), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.0, max_num), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    for(int i = -max_num + 1; i < max_num; i++){
        vertexes.append(VertexData(QVector3D(i, -0.1, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
        vertexes.append(VertexData(QVector3D(i, 0.1, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    }
    for(int i = -max_num + 1; i < max_num; i++){
        vertexes.append(VertexData(QVector3D(0.0, i, -0.1), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
        vertexes.append(VertexData(QVector3D(0.0, i, 0.1), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    }
    for(int i = -max_num + 1; i < max_num; i++){
        vertexes.append(VertexData(QVector3D(0.0, -0.1, i), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
        vertexes.append(VertexData(QVector3D(0.0, 0.1, i), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    }

    //x
    vertexes.append(VertexData(QVector3D(max_num + 0.2, 0.3, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num + 0.4, 0.5, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num + 0.2, 0.5, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num + 0.4, 0.3, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    //стрелка для x
    vertexes.append(VertexData(QVector3D(max_num, 0.0, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num - 0.1, 0.2, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num, 0.0, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(max_num - 0.1, -0.2, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    //y
    vertexes.append(VertexData(QVector3D(-0.5, max_num + 0.2, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.5, max_num + 0.3, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.5, max_num + 0.3, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.6, max_num + 0.4, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.5, max_num + 0.3, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.4, max_num + 0.4, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 1.0, 0.0)));

    //стрелка для y
    vertexes.append(VertexData(QVector3D(0.0, max_num, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-0.2, max_num - 0.1, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, max_num, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.2, max_num - 0.1, 0.0), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    //z
    vertexes.append(VertexData(QVector3D(0.0, 0.2, max_num + 0.2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.2, max_num + 0.3), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.2, max_num + 0.3), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.3, max_num + 0.2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.3, max_num + 0.2), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.3, max_num + 0.3), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.25, max_num + 0.27), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.25, max_num + 0.23), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 1.0)));

    //стрелка для z
    vertexes.append(VertexData(QVector3D(0.0, 0.0, max_num), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, -0.2, max_num - 0.1), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.0, max_num), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(0.0, 0.2, max_num - 0.1), QVector2D(1.0, 0.0), QVector3D(1.0, 0.0, 0.0)));

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        indexes.append(i);
    }

    int isPaint = 4;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

void Widget::initSphera(double r){
    const float PI = 3.141592f;
    GLfloat x, y, z, alpha, beta;
    GLfloat radius = r;
    int gradation = 20;

    QVector<VertexData> vertexes;

    for (alpha = 0.0; alpha < PI; alpha += PI/gradation)
    {
        for (beta = 0.0; beta < 2.01*PI; beta += PI/gradation)
        {
            x = radius*cos(beta)*sin(alpha);
            y = radius*sin(beta)*sin(alpha);
            z = radius*cos(alpha);
            vertexes.append(VertexData(QVector3D(x, y, z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0,  0.0)));

            x = radius*cos(beta)*sin(alpha + PI/gradation);
            y = radius*sin(beta)*sin(alpha + PI/gradation);
            z = radius*cos(alpha + PI/gradation);
            vertexes.append(VertexData(QVector3D(x, y, z), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0,  0.0)));
        }
    }

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        indexes.append(i);
    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

void Widget::initEllipsoid(double a, double b, double c){
    QVector<VertexData> vertexes;
    double _a, _b, _c;
    int num = b * 10;
    for(int j = num; j > 0; --j){
        if(j == num){
          //  _h = -r;
          //  _r = 0.0001;
        }else{
            //_h = -j/10.0;
            _a = a - a/(num - j);
            _b = -j/10.0;
            _c = c - c/(num - j);
        }

        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _b, (_c * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }

    for(int j = 0; j <= num; ++j){
        /*if(j == 0){
            _h = 0.0;
            _r = r - 0.1;   //должна быть просто r, но неправ отрисовывает
        }else{*/
            _a = a - a/(num - j);
            _b = j/10.0;
            _c = c - c/(num - j);
        //}
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _b, (_c * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        for(int j = 0; j < num/2; ++j){
            if( (31*j + i) < vertexes.size()){
                indexes.append(i + 31*j);
            }
        }
        for(int j = num/2; j > 0; --j){
            if( (31*j + i + 15) < vertexes.size()){
                indexes.append(i + 31*j);
            }
        }
    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

void Widget::initCylinder(double a, double b, double height){
    QVector<VertexData> vertexes;
    int num = height * 10;
    for(int j = num; j > 0; --j){
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(a * cos((double)i / 30.0f*3.1415f*2.0f), -height/2, (b * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }

    for(int j = 0; j <= num; ++j){
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(a * cos((double)i / 30.0f*3.1415f*2.0f), height/2, (b * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        for(int j = 0; j < num/2; ++j){
            if( (31*j + i) < vertexes.size()){
                indexes.append(i + 31*j);
            }
        }
        for(int j = num/2; j > 0; --j){
            if( (31*j + i + 15) < vertexes.size()){
                indexes.append(i + 31*j);
            }
        }
    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

void Widget::initConus(double a, double b, double c){
    QVector<VertexData> vertexes;

    double h = 2*c;
    double a_ = 2*sqrt(a);
    double b_ = 2*sqrt(b);

    vertexes.append(VertexData(QVector3D(0.0, 0.0, 0.0), QVector2D(1.0, 0.0), QVector3D(0.0, 0.0, 0.0)));

    for(int i = 0; i <= 30 ; i++)
    {
        vertexes.append(VertexData(QVector3D(a_ * cos((double)i / 30.0f*3.1415f*2.0f), (b_ * sin((double)i / 30.0f*3.1415f*2.0f)), h), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        vertexes.append(VertexData(QVector3D(a_ * cos((double)i / 30.0f*3.1415f*2.0f), (b_ * sin((double)i / 30.0f*3.1415f*2.0f)), -h), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
    }

    QVector<GLuint> indexes;

    for(int i = 1; i < vertexes.size(); i++){
        if(i % 2 == 0){
            indexes.append(0);
            indexes.append(i);
            indexes.append(i + 2);
        }
    }

    indexes.append(0);

    for(int i = 1; i < vertexes.size(); i++){
        if(i % 2 != 0){
            indexes.append(0);
            indexes.append(i);
            indexes.append(i + 2);
        }
    }

    /*double _a, _b, _c;
    int num = b * 10;
    for(int j = b * 10.0; j > 0; --j){
        _b = -j/10.0;
        _a = a - a/(j + 1);
        _c = c - c/(j + 1);
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _b, (_c * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }
    for(int j = 0; j <= b * 10; ++j){
        _b = j/10.0;
        _a = a - a/(j + 1);
        _c = c - c/(j + 1);
        for(int i = 0; i <= 30 ; i++)
        {
            vertexes.append(VertexData(QVector3D(_a * cos((double)i / 30.0f*3.1415f*2.0f), _b, (_c * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
        }
    }

    QVector<GLuint> indexes;

    for(int i = 0; i < vertexes.size(); i++){
        indexes.append(i);
    }*/

//    for(int i = 0; i < vertexes.size(); i++){
//        for(int j = 0; j < num/2; ++j){
//            if( (31*j + i) < vertexes.size()){
//                indexes.append(i + 31*j);
//            }
//        }
//        for(int j = num/2; j > 0; --j){
//            if( (31*j + i + 15) < vertexes.size()){
//                indexes.append(i + 31*j);
//            }
//        }
//    }

    int isPaint = 3;

    m_objects.append(new Object3D(vertexes, indexes, QImage("1"), isPaint));
}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        m_mousePosition = (QVector3D)event->localPos();
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() != Qt::LeftButton){
        return;
    }
    QVector3D diff = QVector3D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector3D(event->localPos());

    double angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_camera->rotate(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
}

void Widget::wheelEvent(QWheelEvent *event){
    if(event->delta() > 0){
         m_camera->translate(QVector3D(0.0f, 0.0f, 0.25f));
    }else if(event->delta() < 0){
         m_camera->translate(QVector3D(0.0f, 0.0f, -0.25f));
    }
    update();
}

/*void Widget::mouseDoubleClickEvent(QMouseEvent *){
    if(father->getNumOfWinds() == 0){
        largeWidget *largew = new largeWidget();
        largew->setFather(father);
        largew->show();
        father->setNumOfWinds(father->getNumOfWinds() + 1);
    }
}*/

MainWindow *Widget::getFather() const
{
    return father;
}

void Widget::setFather(MainWindow *value)
{
    father = value;
}

void Widget::deleteAllPointsVect(){
    allPointsVect.clear();
}

//что-то похожее на гиперболоид
//double _h, _r;
//for(int j = r * 10.0; j > 0; --j){
//    _h = -j/10.0;
//    _r = r - r/(j + 1);
//    for(int i = 0; i <= 30 ; i++)
//    {
//        vertexes.append(VertexData(QVector3D(_r * cos((double)i / 30.0f*3.1415f*2.0f), _h, (_r * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//    }
//}
//for(int j = 0; j <= r * 10; ++j){
//    _h = j/10.0;
//    _r = r - r/(j + 1);
//    for(int i = 0; i <= 30 ; i++)
//    {
//        vertexes.append(VertexData(QVector3D(_r * cos((double)i / 30.0f*3.1415f*2.0f), _h, (_r * sin((double)i / 30.0f*3.1415f*2.0f))), QVector2D(1.0, 0.0), QVector3D(cos((double)i / 30.0f*3.1415f*2.0f), 0.0,  sin((double)i / 30.0f*3.1415f*2.0f))));
//    }
//}

