#include "convexe2d.h"

Convexe2D::Convexe2D(QVector<Vector2D> points)
{

}

Convexe2D::Convexe2D(Vector2D point0, Vector2D point1, Vector2D point2)
{

}



Convexe2D Convexe2D::operator+(const Convexe2D& convexe) const
{
    return *this;
}

Convexe2D Convexe2D::operator*(float scale) const
{
    Convexe2D res(*this);
    for(Vector2D& p : res._points)
        p*=scale;
    return res;
}
