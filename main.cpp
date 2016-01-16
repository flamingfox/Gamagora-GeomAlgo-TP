#include <iostream>

#include "OpenGL/mywindow.h"
#define PI 3.14159265359

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

    poly1.name = QString("Non Convex");

    Polygone poly2 = Convexe2D(poly1.getPoints());
    std::cout << "nombre de points du polygone : " << poly1.getNbPoints() << std::endl;
    std::cout << "nombre de points de l'enveloppe convexe : " << poly2.getNbPoints() << std::endl;
    poly2.name = QString("Convex");

    glWin.addPoly(poly1);
    glWin.addPoly(poly2);

    Polygone carre;
    Polygone triangle;
    Polygone cercle;
    UnionConvex uc1, uc2, uc3, uc4, uc5;

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

    uc1.add(carreConv);
    uc2.add(cercleConv);
    uc3.add(triangleConv);
    uc4.add(carrePtriangle);
    uc5.add(carrePcercle);

    glWin.addUnionConvex(uc1);
    glWin.addUnionConvex(uc2);
    glWin.addUnionConvex(uc3);
    glWin.addUnionConvex(uc4);
    glWin.addUnionConvex(uc5);

    glWin.addUnionConvexMorph(uc1);
    glWin.addUnionConvexMorph(uc2);
    glWin.addUnionConvexMorph(uc3);
    glWin.addUnionConvexMorph(uc4);
    glWin.addUnionConvexMorph(uc5);



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


