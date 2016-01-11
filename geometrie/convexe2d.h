#ifndef CONVEXE2D_H
#define CONVEXE2D_H

#include <QVector>
#include "vector2d.h"

class Convexe2D
{
public:
    Convexe2D(QVector<Vector2D> points);
    Convexe2D(Convexe2D convexe, Vector2D point);
    Convexe2D(Vector2D point0, Vector2D point1, Vector2D point2);

    operator +(Convexe2D convexe);
    operator *(float scale);

private :
    bool inHalfSpace(Vector2D extrem0, Vector2D extrem1, Vector2D p);
};

#endif // CONVEXE2D_H
