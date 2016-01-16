#include "myWindow.h"
#include <QDebug>
#include "stdio.h"


myWindow::myWindow(QWidget *parent)
    : myGLWidget(60, parent, "Polygone Convexe")
{
}

void myWindow::_draw_text(double x, double y, double z, QString txt)
{
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0,1.0,1.0);
    int coeefzoom = std::abs(_zoom)/3;
    if(coeefzoom <= 1)coeefzoom = 1;
    renderText(x, y, z, txt, QFont("Arial", 12/coeefzoom, QFont::Bold, false) );
    glEnable(GL_DEPTH_TEST);
}


void myWindow::initializeGL()
{

    carre.addPoint(Vector2D(0,0));
    carre.addPoint(Vector2D(1,0));
    carre.addPoint(Vector2D(1,1));
    carre.addPoint(Vector2D(0,1));

    triangle.addPoint(Vector2D(0,0));
    triangle.addPoint(Vector2D(1,0));
    triangle.addPoint(Vector2D(0.5,2));

    Convexe2D carreConv(carre.getPoints());
    Convexe2D triangleConv(triangle.getPoints());

    uc1.add(carreConv);
    uc2.add(triangleConv);

    addUnionConvex(uc1);
    addUnionConvex(uc2);

    addUnionConvexMorph(uc1);
    addUnionConvexMorph(uc2);


    _zoom = -2.0f;
    _fx = 0.0;
    _speed =0.1;
    _angle = 0.0;
    _hauteurcam = 0.0;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glShadeModel(GL_SMOOTH);
    glClearColor(24.0f/255.0f, 94.0f/255.0f, 139.0f/255.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    meshUpToDate = false;

}

void myWindow::loadTexture(QString textureName){
    QImage qim_Texture;
    QImage qim_TempTexture;
    qim_TempTexture.load(textureName);
    qim_Texture = QGLWidget::convertToGLFormat( qim_TempTexture );
    glGenTextures( 1, &texture[0] );
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, 3, qim_Texture.width(), qim_Texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, qim_Texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void myWindow::keyReleaseEvent(QKeyEvent *keyEvent){
    switch(keyEvent->key())
    {
            //zoom
        case Qt::Key_Up:
            _zooming = false;
        break;
        case Qt::Key_Down:
            _dezooming = false;
        break;
            //rotation
        case Qt::Key_Left:
            _turningright = false;
        break;
        case Qt::Key_Right:
            _turningleft = false;
        break;
            //angle
            /*
        case Qt::Key_Up:
            //_plonger = false;
        break;
        case Qt::Key_Down:
            //_deplonger = false;
        break;*/
            //hauteur camera
        case Qt::Key_Z:
            _monter = false;
        break;
        case Qt::Key_S:
            _demonter = false;
        break;

        case Qt::Key_Q:
            _movingAlongXLeft = false;
        break;
        case Qt::Key_D:
            _movingAlongXRight = false;
        break;
    }
}

void myWindow::keyPressEvent(QKeyEvent *keyEvent)
{

    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Plus:
            _speed += 0.05;
        break;
        case Qt::Key_Minus:
            _speed -= 0.05;
        break;
            //zoom
        case Qt::Key_Up:
            _zooming = true;
        break;
        case Qt::Key_Down:
            _dezooming = true;
        break;
            //zoom

        case Qt::Key_Q:
            _movingAlongXLeft = true;
        break;
        case Qt::Key_D:
            _movingAlongXRight = true;
        break;


            //rotation
        case Qt::Key_Left:
            _turningright = true;
        break;
        case Qt::Key_Right:
            _turningleft = true;
        break;
            //angle
            /*
        case Qt::Key_Up:
            _plonger = true;
            //_angle -= 5.0;
        break;
        case Qt::Key_Down:
            _deplonger = true;
            //_angle += 5.0;
        break;*/
            //hauteur camera
        case Qt::Key_Z:
            _monter = true;
        break;
        case Qt::Key_S:
            _demonter = true;
        break;
    }
}


// Replaces gluPerspective. Sets the frustum to perspective mode.
// fovY     - Field of vision in degrees in the y direction
// aspect   - Aspect ratio of the viewport
// zNear    - The near clipping distance
// zFar     - The far clipping distance
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );

}


void myWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(90.0f, (GLfloat)width/(GLfloat)height, 0.1f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myWindow::paintGL()
{
    double deltaTime = t_Timer->interval()/1000.0;

    int LightPos[4] = {1,5,-1,0};
    int Light2Pos[4] = {-2,7,2,0};
    int Light3Pos[4] = {5,4,0,0};
    _fx += _speed;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPolygonMode( GL_FRONT, GL_FILL );

    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);
    glLightiv(GL_LIGHT1,GL_POSITION,Light2Pos);
    glLightiv(GL_LIGHT2,GL_POSITION,Light3Pos);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 10);

    //zoom
    if(_zooming){
        multiplicateurovertimezoom += 0.15;
        _zoom += _zoomspeed * multiplicateurovertimezoom * deltaTime;
    }else if(_dezooming){
        multiplicateurovertimezoom += 0.15;
        _zoom -= _zoomspeed * multiplicateurovertimezoom * deltaTime;
    }else{
        multiplicateurovertimezoom = 1.0;
    }
    //déplacmeent axe X
    if(_movingAlongXRight){
        _positionX -= _zoomspeed * deltaTime;
    }
    if(_movingAlongXLeft){
        _positionX += _zoomspeed * deltaTime;
    }

    //rotation
    if(_turningleft){
        multiplicateurovertimerotation += 0.15;
        _fx -= _rotationspeed * multiplicateurovertimerotation * deltaTime;
    }else if(_turningright){
        multiplicateurovertimerotation += 0.15;
        _fx += _rotationspeed * multiplicateurovertimerotation * deltaTime;
    }else{
        multiplicateurovertimerotation = 1.0;
    }

    /*
    //angle
    if(_plonger){
        multiplicateurovertimeplonger += 0.15;
        _angle += _rotationspeed* multiplicateurovertimeplonger *deltaTime;
    }else if(_deplonger){
        multiplicateurovertimeplonger += 0.15;
        _angle -= _rotationspeed* multiplicateurovertimeplonger *deltaTime;
    }else{
        multiplicateurovertimeplonger = 1.0;
    }*/


    //hauteur camera
    if(_monter){
        multiplicateurovertimemonter += 0.15;
        _hauteurcam -= 2 * multiplicateurovertimemonter *deltaTime;
    }else if(_demonter){
        multiplicateurovertimemonter += 0.15;
        _hauteurcam += 2 * multiplicateurovertimemonter *deltaTime;
    }else{
        multiplicateurovertimemonter = 1.0;
    }

    glTranslatef(0.f, _hauteurcam, _zoom);
    glTranslatef(_positionX, 0.0f, 0.0f);
    glRotated(_angle,1,0,0);
    //glRotated(_fx,0,0,1);

    //***************************************//
    //************* Création Mesh ***********//
    //***************************************//

    if(!meshUpToDate){ 
        meshUpToDate = true;
    }


    Convexe2D carreConv(carre.getPoints());
    Convexe2D triangleConv(triangle.getPoints());

    uc1.getConvexes().clear();
    uc2.getConvexes().clear();
    uc1.add(carreConv);
    uc2.add(triangleConv);






    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);


    glPointSize(5.0f);
    glLineWidth(5.0f);


    foreach(const Polygone& poly, _polyList){
        if(poly.isLinked()) {
            glBegin(GL_LINE_LOOP);
            glColor3f(0,1,0);
        }
        else{
            glBegin(GL_POINTS);
            glColor3f(1,0,0);
        }
        for(const Vector2D& p: poly.getPoints()){
            glVertex2f(p.x,p.y);
        }
        glEnd();
        _draw_text(0.0f,-0.5f,0.0f,QString(poly.name));
        glTranslatef(2.0f, 0.0f, 0.0f);
    }

    foreach(const UnionConvex& uC, _unionConvexList)
    {
        foreach(const Convexe2D& poly, uC.getConvexes())
        {
            glBegin(GL_LINE_LOOP);
            for(const Vector2D& p: poly.getPoints())
                glVertex2f(p.x,p.y);
            glEnd();
        }
        glTranslatef(2.0f, 0.0f, 0.0f);
    }

    //morph
    int nbMorph = _unionConvexMorphList.size();
    if(nbMorph == 1)    {
        foreach(const Convexe2D& poly, _unionConvexMorphList[0].getConvexes())
        {
            glBegin(GL_LINE_LOOP);
            for(const Vector2D& p: poly.getPoints())
                glVertex2f(XY(p));
            glEnd();
        }
    }
    else if(nbMorph > 1)    {
        static float temps = 0.f;
        temps += deltaTime;
        float t = fmodf(temps, nbMorph);
        int i = floor(t);
        t -= i;

        UnionConvex uCMorph = Morph(_unionConvexMorphList[i],_unionConvexMorphList[(i+1)%nbMorph],t);

        foreach(const Convexe2D& poly, uCMorph.getConvexes())
        {
            glBegin(GL_LINE_LOOP);
            for(const Vector2D& p: poly.getPoints())
                glVertex2f(XY(p));
            glEnd();
        }
    }
}


void myWindow::addPoly(const Polygone& poly){
    _polyList.append(poly);
    //_polyList.push_back(poly);
}

void myWindow::addUnionConvex(const UnionConvex& convex){
    _unionConvexList.append(convex);
    //_unionConvexList.push_back(convex);
}


void myWindow::addUnionConvexMorph(const UnionConvex& convex){
    _unionConvexMorphList.append(convex);
    //_unionConvexMorphList.push_back(convex);
}
