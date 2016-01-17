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
    void translate(float x, float y);
    void scale(float s);

    //friend Convexe2D;
    friend UnionConvex Morph(const UnionConvex& c1, const UnionConvex& c2, float t);


    Vector2D getCentre() const {return _centre;}
    Vector2D getMin() const {return _min;}
    Vector2D getMax() const {return _max;}

    QString name;

protected:
    std::vector<Convexe2D> convexs;

    Vector2D _centre;    //peut aussi servir à afficher le nom au bon endroit.
    Vector2D _min;
    Vector2D _max;
};


UnionConvex Morph(const UnionConvex& conv1, const UnionConvex& conv2, float t);

#endif // UNIONCONVEX_H
