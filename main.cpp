#include <iostream>

#include "OpenGL/mywindow.h"
#include "geometrie/jarvisconvex.h"

#include <QTime>
#include <QDebug>

#define PI 3.14159265359

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    myWindow glWin;

#define TEST 1

#if TEST == 0
    //enveloppe convexe normale
    Polygone poly1;

    int nb = 50000000;
    poly1.reservePoints(nb);
    for(int i=0; i < nb; i++){
        poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
    }
    poly1.translate(-0.5,-0.5);
    poly1.scale(3);

    poly1.name = QString("Non Convex");


    QTime timer;
    timer.start();

    //Polygone poly2 = Convexe2D(poly1.getPoints());
    Polygone poly2 = Convexe2D(poly1.getPoints());

    int time = timer.elapsed();
    std::cout << time << " ms" << std::endl;


    std::cout << "nombre de points du polygone : " << poly1.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe : " << poly2.getNbPoints() << std::endl;
    poly2.name = QString("Convex");

    glWin.addPoly(poly1);
    glWin.addPoly(poly2);

#elif TEST == 1
    QTime t;
    Polygone poly0;
    Polygone poly00;

    Polygone poly1;

    for(int i=0; i < 1000000; i++){
        poly0.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
    }

    for(int i=0; i < 100; i++){
        poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
    }

    poly1.name = QString("Non Convex");

    double sampletest = 10.0; //nombre de creations de convexe pour la comparaison entre les 2 algos

    t.start();
    for(double i=0; i<sampletest; i++){
        poly00 = Convexe2D(poly0.getPoints());
    }
    qDebug()<<t.elapsed()/sampletest << " secondes";

    t.start();
    for(double i=0; i<sampletest; i++){
        poly00 = JarvisConvex(poly0.getPoints());
    }
    qDebug()<<t.elapsed()/sampletest << " secondes";


    Polygone poly2 = Convexe2D(poly1.getPoints());
    std::cout << "nombre de points du polygone : " << poly1.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe : " << poly2.getNbPoints() << std::endl;
    poly2.name = QString("Convex");

    glWin.addPoly(poly1);
    glWin.addPoly(poly2);

    /////////////////////////////////// jarvis est plus efficace si nb points < 100 000


    Polygone poly3 = poly1;
    poly3.translate(0,-2);

    Polygone poly4 = JarvisConvex(poly3.getPoints());


    std::cout << "nombre de points du polygone : " << poly3.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe de Jarvis : " << poly4.getNbPoints() << std::endl;
    poly4.name = QString("Jarvis Convex");

    glWin.addPoly(poly3);
    glWin.addPoly(poly4);

    ///////////////////////////////////

    Polygone carre;
    Polygone triangle;
    Polygone cercle;

    carre.addPoint(Vector2D(0,0));
    carre.addPoint(Vector2D(1,0));
    carre.addPoint(Vector2D(1,1));
    carre.addPoint(Vector2D(0,1));

    triangle.addPoint(Vector2D(0,0));
    triangle.addPoint(Vector2D(0.4,0));
    triangle.addPoint(Vector2D(0.2,0.4));

    for(int i = 0; i< 360; i+=9){
        cercle.addPoint(Vector2D((std::cos((i*2*PI)/360)/1.5f)+0.5f,(std::sin((i*2*PI)/360)/1.5f)+0.5f));
    }

    Convexe2D carreConv(carre.getPoints());
    Convexe2D triangleConv(triangle.getPoints());
    Convexe2D cercleConv(cercle.getPoints());

    cercleConv.scale(0.8);
    cercleConv.name = QString("Cercle Convexe");
    triangleConv.name = QString("Triangle Convexe");
    carreConv.name = QString("Carre Convexe");

    Convexe2D carrePtriangle = carreConv + triangleConv;
    Convexe2D carrePcercle = carreConv + cercleConv;

    carrePtriangle.name = QString("Carre + Triangle");
    carrePcercle.name = QString("Carre + Cercle");


    UnionConvex uc1, uc2, uc3, uc4, uc5;
    uc1.add(carreConv);
    uc2.add(cercleConv);
    uc3.add(triangleConv);
    uc4.add(carrePtriangle);
    uc5.add(carrePcercle);

    uc1.name = carreConv.name;
    uc2.name = cercleConv.name;
    uc3.name = triangleConv.name;
    uc4.name = carrePtriangle.name;
    uc5.name = carrePcercle.name;

    glWin.addUnionConvexMorph(uc1);
    glWin.addUnionConvexMorph(uc2);
    glWin.addUnionConvexMorph(uc3);
    glWin.addUnionConvexMorph(uc4);
    glWin.addUnionConvexMorph(uc5);
    glWin.translateMorph(Vector2D(13,0));

    uc1.translate(2,0);
    uc2.translate(4,0);
    uc3.translate(6,0);
    uc4.translate(8,0);
    uc5.translate(10,0);

    glWin.addUnionConvex(uc1);
    glWin.addUnionConvex(uc2);
    glWin.addUnionConvex(uc3);
    glWin.addUnionConvex(uc4);
    glWin.addUnionConvex(uc5);




#elif TEST == 2
    //Morph
    Polygone carre;
    carre.addPoint(Vector2D(0,0));
    carre.addPoint(Vector2D(1,0));
    carre.addPoint(Vector2D(1,1));
    carre.addPoint(Vector2D(0,1));
    carre.translate(-0.5,-0.5);

    Polygone triangle;
    triangle.addPoint(Vector2D(0,0));
    triangle.addPoint(Vector2D(1,0));
    triangle.addPoint(Vector2D(0.5,1));
    triangle.translate(-0.5,-0.5);

    Polygone carre2;
    carre2.addPoint(Vector2D(0.5,0));
    carre2.addPoint(Vector2D(1,0.5));
    carre2.addPoint(Vector2D(0.5,1));
    carre2.addPoint(Vector2D(0,0.5));
    carre2.translate(-0.5,-0.5);

    Polygone octogone;
    octogone.addPoint(Vector2D(1.0,1.0));
    octogone.addPoint(Vector2D(0,1.5));
    octogone.addPoint(Vector2D(-1.0,1.0));
    octogone.addPoint(Vector2D(-1.5,0));
    octogone.addPoint(Vector2D(-1.0,-1.0));
    octogone.addPoint(Vector2D(0,-1.5));
    octogone.addPoint(Vector2D(1.0,-1.0));
    octogone.addPoint(Vector2D(1.5,0.0));
    octogone.scale(0.5);

    //glWin.addPoly(octogone);

    /*
    carre.translate(Vector2D(-0.5,-0.5));
    triangle.translate(Vector2D(-0.5,-0.5));
    carre2.translate(Vector2D(-0.5,-0.5));
    */

    Convexe2D carreConv(carre.getPoints());
    Convexe2D triangleConv(triangle.getPoints());
    Convexe2D carreConv2(carre2.getPoints());
    Convexe2D octoConv(octogone.getPoints());


    UnionConvex uc1, uc2, uc3, uc4;
    uc1.add(carreConv);
    uc2.add(triangleConv);
    uc3.add(carreConv2);
    uc4.add(octoConv);

    //UnionConvex test = Morph(uc2,uc1,0.00799918175);

    //glWin.addUnionConvex(test);
    glWin.addUnionConvexMorph(uc1);
    glWin.addUnionConvexMorph(uc2);
    glWin.addUnionConvexMorph(uc3);
    glWin.addUnionConvexMorph(uc4);

#elif TEST == 3
//marche de jarvis

    Polygone poly1;

    int nb = 50000000;
    poly1.reservePoints(nb);
    for(int i=0; i < nb; i++){
        poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
    }
    poly1.translate(-0.5,-0.5);
    poly1.scale(3);

    poly1.name = QString("Non Convex");


    QTime timer;
    timer.start();

    Polygone poly2 = JarvisConvex(poly1.getPoints());

    int time = timer.elapsed();
    std::cout<< time << " ms" << std::endl;


    std::cout << "nombre de points du polygone : " << poly1.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe : " << poly2.getNbPoints() << std::endl;
    //poly2.translate(Vector2D(1.5,0));

    poly2.name = QString("Jarvis");

    glWin.addPoly(poly1);
    glWin.addPoly(poly2);
#endif

    glWin.show();
    return app.exec();
}


