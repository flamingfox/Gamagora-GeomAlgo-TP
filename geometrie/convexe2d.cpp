#include "convexe2d.h"

Convexe2D::Convexe2D(QVector<Vector2D> points)
{
    Convexe2D tmp = Convexe2D(points[0], points[1], points[2]);

    for(int i=3; i< points.length(); i++){
        tmp = Convexe2D(tmp, points[i]);
    }

    _points = tmp._points;
    setLinked(true);
}

Convexe2D::Convexe2D(const Convexe2D& convexe, const Vector2D& point)
{
    bool debutCoupe = 0;

    for(int i=0; i<convexe._points.length(); i++){
        if(inHalfSpaceDroit(convexe._points[i],convexe._points[(i+1)%convexe._points.length()], point)){
            if(debutCoupe){
                _points.push_back(convexe._points[i]);
                _points.push_back(point);
            }
        }
        else{
            _points.push_back(convexe._points[i]);
            debutCoupe = 1;
        }
    }

    if(_points.empty()){
        _points = convexe._points;
    }
    setLinked(true);
}

Convexe2D::Convexe2D(const Vector2D& point0, const Vector2D& point1, const Vector2D& point2)
{    
    if(inHalfSpaceDroit(point0, point1, point2)){
        addPoint(point0);
        addPoint(point2);
        addPoint(point1);
    }
    else{
        addPoint(point0);
        addPoint(point1);
        addPoint(point2);
    }
    setLinked(true);
}

/*
Convexe2D::operator +(Convexe2D convexe)
{
    QVector<Vector2D> listInit;
    for(int i=0; i<_points.length(); i++){
        listInit.push_back(_points[i]+convexe._points[0]);
    }

    Convexe2D tmp = Convexe2D(listInit);

    for(int i=0; i<_points.length(); i++){
        for(int j=1; j<convexe._points.length(); j++){
            tmp = Convexe2D(tmp, _points[i]+convexe._points[j]);
        }
    }
}

Convexe2D::operator *(float scale)
{
    for(int i=0; i<_points.length(); i++){
        _points[i]*= scale;
    }
}*/

bool Convexe2D::inHalfSpaceDroit(const Vector2D& extrem0, const Vector2D& extrem1, const Vector2D& p)
{
    Vector2D orthoDir = (extrem1 - extrem0).crossProduct();

    if( (p-extrem0).dotProduct(orthoDir) <= 0 )
        return true;

    return false;
}



Convexe2D Convexe2D::operator+(const Convexe2D& convexe) const
{
    QVector<Vector2D> pointsAdd;
    for(const Vector2D& p1 : this->_points)
        for(const Vector2D& p2 : convexe._points)
            pointsAdd.push_back(p1+p2);


    return Convexe2D(pointsAdd);
}

Convexe2D Convexe2D::operator*(float scale) const
{
    Convexe2D res(*this);
    for(Vector2D& p : res._points)
        p*=scale;
    return res;
}
