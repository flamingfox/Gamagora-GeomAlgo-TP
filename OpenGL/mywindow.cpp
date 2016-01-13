#include "myWindow.h"
#include <QDebug>
#include "stdio.h"


myWindow::myWindow(QWidget *parent)
    : myGLWidget(60, parent, "Génération ville")
{
}

void myWindow::_draw_text(double x, double y, double z, QString txt)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0,1.0,1.0);
    renderText(x, y, z, txt, QFont("Arial", 12, QFont::Bold, false) );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}


void myWindow::initializeGL()
{

    _poly._points.append(Vector2D(0,0));
    _poly._points.append(Vector2D(0,1));
    _poly._points.append(Vector2D(0,0.5));
    _poly._points.append(Vector2D(0.2,0));
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
        case Qt::Key_Z:
            _zooming = false;
        break;
        case Qt::Key_P:
            if(_poly.isLinked())_poly.setLinked(false);
            else{_poly.setLinked(true);}
        break;
        case Qt::Key_S:
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
        case Qt::Key_Up:
            //_plonger = false;
        break;
        case Qt::Key_Down:
            //_deplonger = false;
        break;
            //hauteur camera
        case Qt::Key_E:
            _monter = false;
        break;
        case Qt::Key_A:
            _demonter = false;
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
        case Qt::Key_Z:
            _zooming = true;
        break;
        case Qt::Key_S:
            _dezooming = true;
        break;
            //zoom       
            //rotation
        case Qt::Key_Left:
            _turningright = true;
        break;
        case Qt::Key_Right:
            _turningleft = true;
        break;
            //angle
        case Qt::Key_Up:
            _plonger = true;
            //_angle -= 5.0;
        break;
        case Qt::Key_Down:
            _deplonger = true;
            //_angle += 5.0;
        break;
            //hauteur camera
        case Qt::Key_E:
            _monter = true;
        break;
        case Qt::Key_A:
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
    glRotated(_angle,1,0,0);
    glRotated(_fx,0,0,1);

    //***************************************//
    //************* Création Mesh ***********//
    //***************************************//

    if(!meshUpToDate){ 
        meshUpToDate = true;
    }

    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glPointSize(5.0f);

    if(_poly.isLinked()){
        glPointSize(3.0f);
        glBegin(GL_POINTS);
        for(int i=0; i<_poly.getPoints().size();i++){
            glVertex2f(_poly.getPoints().at(i).x,_poly.getPoints().at(i).y);
        }
        glEnd();
    }else{
        glLineWidth(3.0f);
        for(int i=0; i<_poly.getPoints().size()-1;i++){
            glBegin(GL_LINES);
            glVertex2f(_poly.getPoints().at(i).x,_poly.getPoints().at(i).y);
            glVertex2f(_poly.getPoints().at(i+1).x,_poly.getPoints().at(i+1).y);
            glEnd();
        }
    }




    //_draw_text(_par.hauteurEtageLePlusHaut.x,_par.hauteurEtageLePlusHaut.y,_par.hauteurEtageLePlusHaut.z,QString(QString::number(_par.etageLePlusHaut)));
}
