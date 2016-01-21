#ifndef CONVEXE2D_H
#define CONVEXE2D_H

#include <QVector>
#include "vector2d.h"
#include "polygone.h"

class Convexe2D : public Polygone
{
public:
    Convexe2D() {}
    Convexe2D(const QVector<Vector2D>& points);
    Convexe2D(const Convexe2D &convexe, const Vector2D &point);
    Convexe2D(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2);

    Convexe2D operator+(const Convexe2D& convexe) const;
    Convexe2D operator*(float scale) const;

    void scale(float s);


    void ajoutPointConvex(const Vector2D& p);

protected :
    bool initNonAlignee(const QVector<Vector2D>& points, int& i0, int& i1, int& i2) const;
    void initTriangle(const Vector2D& point0, const Vector2D& point1, const Vector2D& point2);

    bool findIndicesCoupe(const Vector2D& p, int& deb, int& fin);

};

#define ALIGNEE 2
#define GAUCHE 0
#define DROIT 1
int inHalfSpaceDroit(const Vector2D &extrem0, const Vector2D &extrem1, const Vector2D &p);

int coteAlignement(const Vector2D& p, const Vector2D& extrem0, const Vector2D& extrem1);

#endif // CONVEXE2D_H
