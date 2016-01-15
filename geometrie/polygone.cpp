#include "polygone.h"

Polygone::Polygone()
{

}

Polygone::Polygone(QVector<Vector2D> points): _points(points) {
    for(const Vector2D& p:  points)    {
        _centre += p;
        _min = min(_min,p);
        _max = max(_max,p);
    }
    _centre /= points.size();
}

void Polygone::translate(const Vector2D& trans)
{
    for(Vector2D& p: this->_points)
        p += trans;
    _centre += trans;
    _min += trans;
    _max += trans;
}
