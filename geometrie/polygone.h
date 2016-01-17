#ifndef POLYGONE_H
#define POLYGONE_H

#include <QVector>
#include "vector2d.h"
#include <QString>

class Polygone
{
public:
    Polygone();
    Polygone(QVector<Vector2D> points);
    inline bool isLinked() const {return _linked;}
    inline void setLinked(bool linked){_linked = linked;}
    QVector<Vector2D> getPoints() const {return _points;}

    
    inline void addPoint(const Vector2D& point){_points.push_back(point);}

    void translate(const Vector2D& trans);
    virtual void scale(float s);

    QString name;

    Vector2D getCentre() const {return _centre;}
    Vector2D getMin() const {return _min;}
    Vector2D getMax() const {return _max;}

    int getNbPoints() const {return _points.size();}
    void reservePoints(int nb)  {_points.reserve(nb);}

protected:
    QVector<Vector2D> _points;
    Vector2D _centre;    //peut aussi servir à afficher le nom au bon endroit.
    Vector2D _min;
    Vector2D _max;
    bool _linked = false;

    void initMinMaxCentre();

private:
};

#endif // POLYGONE_H
