#ifndef JARVISCONVEX_H
#define JARVISCONVEX_H

#include "convexe2d.h"

class JarvisConvex : public Convexe2D
{
public:
    JarvisConvex(const QVector<Vector2D>& points);
};

#endif // JARVISCONVEX_H
