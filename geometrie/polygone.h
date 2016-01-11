#ifndef POLYGONE_H
#define POLYGONE_H

#include <QVector>
#include "vector2d.h"


class Polygone
{
public:
    Polygone();
    Polygone(QVector<Vector2D> points): _points(points) {}
    inline bool isLinked(){return _linked;}
    inline void setLinked(bool linked){_linked = linked;}
    inline QVector<Vector2D> getPoints(){return _points;}



protected:
    QVector<Vector2D> _points;

private:
    bool _linked;
};

#endif // POLYGONE_H
