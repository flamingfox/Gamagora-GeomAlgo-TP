
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
    TerrainTab terrain = TerrainTab(img, 1000, 1000, 100);
    QImage res = img.scaled(1000,1000);
    QImage res2 = img.scaled(1000,1000);
    QImage res3 = img.scaled(1000,1000);

    QPainter paint(&res);


    bSkeleton bS;

    int nb = 50;
    for(int i=0; i < nb; i++){
        Vector2D pos((rand()%1001),(rand()%1001));
        Ville ville(Vector3D(XY(pos), terrain.getHauteur(XY(pos))));

        //Ville ville(Vector3D(XY(pos), 0 ));

        bS.addVille(ville);
    }

    bS.relierVille(1);

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
    res.save("resultat1.png");

    /*========================================================*/

    QPainter paint2(&res2);
    bS.relierVille(2);

    paint2.setPen(pen);
    //paint.setBrush(QColor(255, 0, 0));

    for(const Route& r : bS.getRoutes())
    {
        const Ville& v1 = r._ville1;
        const Ville& v2 = r._ville2;
        paint2.drawLine(XY(v1.getPosition()), XY(v2.getPosition()));
    }

    paint2.setPen(pen2);
    //paint.setBrush(QColor(0, 255, 0));
    for(const Ville& v: bS.getVilles())
    {
        paint2.drawPoint(XY(v.getPosition()));
    }
    paint2.end();
    res2.save("resultat2.png");

    /*========================================================*/


    QPainter paint3(&res3);
    bS.relierVille(8);

    paint3.setPen(pen);
    //paint.setBrush(QColor(255, 0, 0));

    for(const Route& r : bS.getRoutes())
    {
        const Ville& v1 = r._ville1;
        const Ville& v2 = r._ville2;
        paint3.drawLine(XY(v1.getPosition()), XY(v2.getPosition()));
    }


    paint3.setPen(pen2);
    //paint.setBrush(QColor(0, 255, 0));
    for(const Ville& v: bS.getVilles())
    {
        paint3.drawPoint(XY(v.getPosition()));
    }
    paint3.end();
    res3.save("resultat8.png");

    return 0;
}

