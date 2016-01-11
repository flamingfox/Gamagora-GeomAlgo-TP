#include "convexe2d.h"

Convexe2D::Convexe2D(const QVector<Vector2D>& points)
{
    //calcule de l'enveloppe convexe
}

Convexe2D::Convexe2D(Vector2D point0, Vector2D point1, Vector2D point2)
{

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
