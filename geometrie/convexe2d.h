#ifndef CONVEXE2D_H
#define CONVEXE2D_H

#include <QVector>
#include "polygone.h"

class Convexe2D : public Polygone
{
public:
    Convexe2D(const QVector<Vector2D>& points);
    Convexe2D(Convexe2D convexe, Vector2D point);
    Convexe2D(Vector2D point0, Vector2D point1, Vector2D point2);

    Convexe2D operator+(const Convexe2D& convexe) const;
    Convexe2D operator*(float scale) const;

private :
    bool inHalfSpace(Vector2D extrem0, Vector2D extrem1, Vector2D p);
};

#endif // CONVEXE2D_H
