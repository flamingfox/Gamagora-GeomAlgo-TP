#ifndef POLYGONE_H
#define POLYGONE_H

#include <QVector>
#include "vector2d.h"


class Polygone
{
public:
    Polygone();
    inline bool isLinked(){return _linked;}
    inline void setLinked(bool linked){_linked = linked;}
    inline QVector<Vector2D> getPoints(){return _points;}
    QVector<Vector2D> _points;


protected:


private:
    bool _linked;
};

#endif // POLYGONE_H
