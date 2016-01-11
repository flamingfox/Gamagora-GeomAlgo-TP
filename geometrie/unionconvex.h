#ifndef UNIONCONVEX_H
#define UNIONCONVEX_H

#include <vector>
#include "convexe2d.h"

class UnionConvex
{
public:
    UnionConvex();
    void add(const Convexe2D& c);

    //friend Convexe2D;
    friend UnionConvex Morph(const UnionConvex& c1, const UnionConvex& c2, float t);

protected:
    std::vector<Convexe2D> convexs;
};

#endif // UNIONCONVEX_H
