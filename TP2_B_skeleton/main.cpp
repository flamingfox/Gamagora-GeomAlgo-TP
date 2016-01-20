
#include <QImage>
#include <QPainter>
#include <iostream>
#include "modele/urbanisation/ville.h"
#include "geometrie/vector2d.h"

#include "modele/terrain/terraintab.h"
#include "math/bskeleton.h"

int main(int argc, char *argv[])
{
    QImage img("map.png");
    TerrainTab terrain = TerrainTab(img, 1000, 1000);
    QImage res = img.scaled(1000,1000);

    QPainter paint(&res);

    bSkeleton bS;

    int nb = 100;
    for(int i=0; i < nb; i++){
        Vector2D pos((rand()%1001),(rand()%1001));
        Ville ville(Vector3D(XY(pos), terrain.getHauteur(XY(pos))));

        bS.addVille(ville);
    }

    bS.relierVille(2);


    QPen pen(Qt::red);
    pen.setWidthF(1);
    paint.setPen(pen);
    //paint.setBrush(QColor(255, 0, 0));

    for(const Route& r : bS.getRoutes())
    {
        const Ville& v1 = r._ville1;
        const Ville& v2 = r._ville2;
        paint.drawLine(XY(v1.getPosition()), XY(v2.getPosition()));
    }

    QPen pen2(Qt::green);
    pen2.setWidthF(2.5);
    paint.setPen(pen2);
    //paint.setBrush(QColor(0, 255, 0));
    for(const Ville& v: bS.getVilles())
    {
        paint.drawPoint(XY(v.getPosition()));
    }
    paint.end();
    res.save("resultat.png");

    return 0;
}

