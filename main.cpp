#include <iostream>

#include "OpenGL/mywindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    myWindow glWin;

#define TEST 1

#if TEST == 1
    Polygone poly1;

    for(int i=0; i < 20; i++){
        poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
    }
/*
    poly1.addPoint(Vector2D(0,0));
    poly1.addPoint(Vector2D(1,0));
    poly1.addPoint(Vector2D(1,1));
    poly1.addPoint(Vector2D(0,1));
    poly1.addPoint(Vector2D(0.5,0.5));
    poly1.addPoint(Vector2D(0.2,0.2));
*/

    /*poly1.addPoint(Vector2D(0.4,1.4));
    poly1.addPoint(Vector2D(-0.4,-0.4));
    poly1.addPoint(Vector2D(-0.4,1.4));
    poly1.addPoint(Vector2D(0.5,-0.5));
    poly1.addPoint(Vector2D(1.4,-0.4));
    poly1.addPoint(Vector2D(0.5,1.5));
    poly1.addPoint(Vector2D(1.5,0.5));
    poly1.addPoint(Vector2D(1.4,1.4));
    poly1.addPoint(Vector2D(-0.5,0.5));*/

    poly1.name = QString("Non Convex");

    Polygone poly2 = Convexe2D(poly1.getPoints());
    std::cout << "nombre de points du polygone : " << poly1.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe : " << poly2.getNbPoints() << std::endl;
    poly2.name = QString("Convex");

    glWin.addPoly(poly1);
    glWin.addPoly(poly2);

#elif TEST == 1
    //Morph
    Polygone carre;
    carre.addPoint(Vector2D(0,0));
    carre.addPoint(Vector2D(1,0));
    carre.addPoint(Vector2D(1,1));
    carre.addPoint(Vector2D(0,1));

    Polygone triangle;
    triangle.addPoint(Vector2D(0,0));
    triangle.addPoint(Vector2D(1,0));
    triangle.addPoint(Vector2D(0.5,2));

    Polygone carre2;
    carre2.addPoint(Vector2D(0.5,0));
    carre2.addPoint(Vector2D(1,0.5));
    carre2.addPoint(Vector2D(0.5,1));
    carre2.addPoint(Vector2D(0.5,1));

    /*
    carre.translate(Vector2D(-0.5,-0.5));
    triangle.translate(Vector2D(-0.5,-0.5));
    carre2.translate(Vector2D(-0.5,-0.5));
    */

    Convexe2D carreConv(carre.getPoints());
    Convexe2D triangleConv(triangle.getPoints());
    Convexe2D carreConv2(carre2.getPoints());

    UnionConvex uc1, uc2, uc3;
    uc1.add(carreConv);
    uc2.add(triangleConv);
    uc3.add(carreConv2);

    //UnionConvex test = Morph(uc2,uc1,0.00799918175);

    //glWin.addUnionConvex(test);
    glWin.addUnionConvexMorph(uc1);
    glWin.addUnionConvexMorph(uc2);
    glWin.addUnionConvexMorph(uc3);
#elif TEST == 2

#endif

    glWin.show();
    return app.exec();
}


