#include "unionconvex.h"

UnionConvex::UnionConvex()
{
}



void UnionConvex::add(const Convexe2D& c)
{
    if(convexs.empty())
    {
        _min = c.getMin();
        _max = c.getMax();
    }
    else
    {
        _min = min(this->_min,c.getMin());
        _max = max(this->_max,c.getMax());
    }
    _centre = (_min+_max)/2;
    convexs.push_back(c);

    /*
    QVector<Vector2D> points;
    foreach(const Convexe2D& poly, convexs)
    {
        foreach(const Vector2D& p, poly.getPoints()){
            points.append(p);
        }
    }
    Convexe2D tmp(points);
    convexs.clear();
    convexs.push_back(tmp);*/
}


UnionConvex Morph(const UnionConvex& conv1, const UnionConvex& conv2, float t)
{
    UnionConvex res;
    if(conv1.convexs.size() != conv2.convexs.size())
        return res;


    for(unsigned int iconv = 0;  iconv < conv1.convexs.size();   iconv++)
    {
        const Convexe2D& c1 = conv1.convexs[iconv]*(1-t);
        const Convexe2D& c2 = conv2.convexs[iconv]*t;

        Convexe2D c = c1 + c2;
        if(iconv == 0)  {
            res._min = c.getMin();
            res._max = c.getMax();
        }
        else    {
            res._min = min(res._min, c.getMin());
            res._max = max(res._max, c.getMax());
        }

        res.convexs.push_back(c);
    }
    res._centre = (res._min+res._max)/2;
    return res;
}

void UnionConvex::translate(const Vector2D& trans)
{
    for(Convexe2D& conv:  this->convexs)
        conv.translate(trans);
    _min += trans;
    _max += trans;
    _centre += trans;
}

void UnionConvex::scale(float s)
{
    for(Convexe2D& conv:  this->convexs)
        conv.scale(s);
    _min *= s;
    _max *= s;
    _centre *= s;
}
