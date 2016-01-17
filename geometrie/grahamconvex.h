#ifndef JARVISCONVEX_H
#define JARVISCONVEX_H

#include "convexe2d.h"

class GrahamConvex : public Convexe2D
{
public:
    GrahamConvex(const QVector<Vector2D>& points);
};

#endif // JARVISCONVEX_H
