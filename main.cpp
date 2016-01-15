#include <iostream>

#include "OpenGL/mywindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myWindow glWin;




    /*
        _poly._points.append(Vector2D(0,0));
        _poly._points.append(Vector2D(0,1));
        _poly._points.append(Vector2D(0,0.5));
        _poly._points.append(Vector2D(0.2,0));
    */

        Polygone poly1;
        /*
        poly1.addPoint(Vector2D(0,0));
        poly1.addPoint(Vector2D(1,0));
        poly1.addPoint(Vector2D(1,1));
        poly1.addPoint(Vector2D(0,1));
        poly1.addPoint(Vector2D(0.5,0.5));
        poly1.addPoint(Vector2D(0.2,0.2));
        */

        for(int i=0;i<20;i++){
            poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
        }

        poly1.name = QString("Non Convex");

        Polygone poly2 = Convexe2D(poly1.getPoints());
        poly2.translate(Vector2D(2,0));

        /*
        poly2.addPoint(Vector2D(0,0));
        poly2.addPoint(Vector2D(1,0));
        poly2.addPoint(Vector2D(1,1));
        poly2.addPoint(Vector2D(0,1));
        poly2.addPoint(Vector2D(0.5,0.5));
        poly2.addPoint(Vector2D(0.2,0.2));
        */

        poly2.name = QString("Convex");

        glWin.addPoly(poly1);
        glWin.addPoly(poly2);

        //Polygone poly3 = Convexe2D(poly2.getPoints());
        //glWin.addPoly(poly3);





    glWin.show();
    return app.exec();
}

