#include "polygone.h"

Polygone::Polygone()
{

}

Polygone::Polygone(QVector<Vector2D> points): _points(points) {
    initMinMaxCentre();
}

void Polygone::initMinMaxCentre()
{
    if(!_points.empty())
    {
        _min = _points.first();
        _max = _points.last();
        for(const Vector2D& p:  _points)    {
            _min = min(_min,p);
            _max = max(_max,p);
        }
        _centre = (_min+_max)/2;
    }
}

void Polygone::translate(const Vector2D& trans)
{
    for(Vector2D& p: this->_points)
        p += trans;
    _centre += trans;
    _min += trans;
    _max += trans;
}
void Polygone::translate(float x, float y)
{
    translate(Vector2D(x,y));
}

void Polygone::scale(float s)
{
    for(Vector2D& p: this->_points)
        p *= s;
    _centre *= s;
    _min *= s;
    _max *= s;
}


