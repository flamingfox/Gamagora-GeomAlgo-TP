#ifndef CONVEXE2D_H
#define CONVEXE2D_H

#include <QVector>
#include "vector2d.h"
#include "polygone.h"

class Convexe2D : public Polygone
{
public:
    Convexe2D(QVector<Vector2D> points);
    Convexe2D(const Convexe2D &convexe, const Vector2D &point);
    Convexe2D(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2);

    Convexe2D operator+(const Convexe2D& convexe) const;
    Convexe2D operator*(float scale) const;

private :
    bool inHalfSpaceDroit(const Vector2D &extrem0, const Vector2D &extrem1, const Vector2D &p);
};

#endif // CONVEXE2D_H
