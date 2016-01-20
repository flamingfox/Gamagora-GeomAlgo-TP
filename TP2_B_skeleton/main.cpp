
#include <QImage>
#include <QPainter>
#include <iostream>
#include "modele/urbanisation/ville.h"
#include "geometrie/vector2d.h"

#include "modele/terrain/terraintab.h"
#include "math/bskeleton.h"

#include <QTime>


void dessineBskeleton(QImage* res, const bSkeleton& bS, const Terrain& terrain, const QPen& penRoute, const QPen& penVille);


int main(int argc, char *argv[])
{
    (void) argc;    (void) argv;
    QImage img("map.png");
    //QImage img = QImage("map2.jpg");

    img = img.convertToFormat(QImage::Format_RGB888);
    int taille = 1000, tailleTerrain = 1000;
    img = img.scaled(taille, taille);
    TerrainTab terrain = TerrainTab(img, taille,taille, tailleTerrain,tailleTerrain, 500);

    bSkeleton bS;

    int nb = 200;
    bS.reserveVilles(nb);
    for(int i=0; i < nb; i++){
        Vector2D pos((rand()%(tailleTerrain+1)),(rand()%(tailleTerrain+1)));
        Ville ville(Vector3D(XY(pos), terrain.getHauteur(XY(pos))));

        bS.addVille(ville);
    }

    /*-------------------------------------------------------------------------*/
    QTime timer;
    int time;

    QPen penRoute(Qt::red);
    penRoute.setWidthF(1);

    QPen penVille(Qt::green);
    penVille.setWidthF(5);

    /*-------------------------------------------------------------------------*/

    QImage res = QImage(img);
    timer.start();
    bS.relierVille(1);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultat1.png");
    std::cout << "sauvegarde resultat1.png terminée" << std::endl;

    /*========================================================*/

    res = QImage(img);
    timer.start();
    bS.relierVille(2);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultat2.png");
    std::cout << "sauvegarde resultat2.png terminée" << std::endl;

    /*========================================================*/

    res = QImage(img);
    timer.start();
    bS.relierVille(8);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultat8.png");
    std::cout << "sauvegarde resultat8.png terminée" << std::endl;

    /*-------------------------------------------------------------------------*/

    res = QImage(img);
    timer.start();
    bS.relierVille(terrain, 1);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultatTerrain1.png");
    std::cout << "sauvegarde resultatTerrain1.png terminée" << std::endl;

    /*========================================================*/

    res = QImage(img);
    timer.start();
    bS.relierVille(terrain, 2);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultatTerrain2.png");
    std::cout << "sauvegarde resultatTerrain2.png terminée" << std::endl;

    /*========================================================*/

    res = QImage(img);
    timer.start();
    bS.relierVille(terrain, 8);
    dessineBskeleton(&res,bS,terrain, penRoute,penVille);
    time = timer.elapsed();
    std::cout << time/1000.f << " secondes" << std::endl;

    res.save("resultatTerrain8.png");
    std::cout << "sauvegarde resultatTerrain8.png terminée" << std::endl;

    return 0;
}

/***************************************************************************************************/

void dessineBskeleton(QImage* res, const bSkeleton& bS, const Terrain& terrain, const QPen& penRoute, const QPen& penVille)
{
    QPainter paint(res);
    const Vector3D redim(res->width()/terrain.largeur, res->height()/terrain.longueur,1);

    paint.setPen(penRoute);
    for(const Route& r : bS.getRoutes())
    {
        const Ville& v1 = r._ville1;
        const Ville& v2 = r._ville2;
        paint.drawLine(XY((v1.getPosition()*redim)), XY((v2.getPosition()*redim)));
    }


    paint.setPen(penVille);
    for(const Ville& v: bS.getVilles())
    {
        paint.drawPoint(XY((v.getPosition()*redim)));
    }
    paint.end();
}
