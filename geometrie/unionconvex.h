#ifndef UNIONCONVEX_H
#define UNIONCONVEX_H

#include <vector>
#include "convexe2d.h"

class UnionConvex
{
public:
    UnionConvex();
    void add(const Convexe2D& c);

    std::vector<Convexe2D> getConvexes() const {    return convexs; }

    void translate(const Vector2D& trans);
    void scale(float s);

    //friend Convexe2D;
    friend UnionConvex Morph(const UnionConvex& c1, const UnionConvex& c2, float t);



protected:
    std::vector<Convexe2D> convexs;
};


UnionConvex Morph(const UnionConvex& conv1, const UnionConvex& conv2, float t);

#endif // UNIONCONVEX_H
