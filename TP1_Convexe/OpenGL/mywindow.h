#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "geometrie/polygone.h"
#include "geometrie/convexe2d.h"
#include "geometrie/unionconvex.h"
#include <QImage>
#include <QVector>

class myWindow : public myGLWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );
    void keyReleaseEvent(QKeyEvent *keyEvent);
    void mousePressEvent( QMouseEvent *mouseEvent );
    void loadTexture(QString textureName);
    void _draw_text(double x, double y, double z, QString txt);

    void addPoly(const Polygone& poly);
    void addUnionConvex(const UnionConvex& convex);
    void addUnionConvexMorph(const UnionConvex& convex);
    void translateMorph(const Vector2D& trans);

private:
    float multiplicateurovertimezoom=1.0;
    float multiplicateurovertimerotation=1.0;
    float multiplicateurovertimeplonger=1.0;
    float multiplicateurovertimemonter=1.0;
    float _zoomspeed = 6;
    float _rotationspeed = 6;
    bool _zooming = false;
    bool _dezooming = false;
    bool _turningright = false;
    bool _turningleft = false;
    bool _plonger = false;
    bool _deplonger = false;
    bool _monter = false;
    bool _demonter = false;
    float _zoom = -5.0;
    bool _movingAlongXRight = false;
    bool _movingAlongXLeft = false;
    float _positionX = 0.0f;
    GLuint texture[1];
    float _fx;
    float _speed;
    float _angle;
    float _hauteurcam;
    bool meshUpToDate;
    QVector<Polygone> _polyList;
    QVector<UnionConvex> _unionConvexList;
    QVector<UnionConvex> _unionConvexMorphList;

};

#endif // MYWINDOW_H
