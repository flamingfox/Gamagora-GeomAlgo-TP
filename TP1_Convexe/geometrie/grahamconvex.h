#ifndef GRAHAMCONVEX_H
#define GRAHAMCONVEX_H

#include "convexe2d.h"

class GrahamConvex : public Convexe2D
{
public:
    GrahamConvex(const QVector<Vector2D>& points);
};

#endif // GRAHAMCONVEX_H
