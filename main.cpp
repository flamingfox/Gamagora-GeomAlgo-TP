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

        for(int i=0; i < 100000; i++){
            poly1.addPoint(Vector2D((rand()%1000)/1000.0f,(rand()%1000)/1000.0f));
        }

        /*poly1.addPoint(Vector2D(0,0));
        poly1.addPoint(Vector2D(1,0));
        poly1.addPoint(Vector2D(1,1));
        poly1.addPoint(Vector2D(0,1));

        poly1.addPoint(Vector2D(0.4,1.4));
        poly1.addPoint(Vector2D(-0.4,-0.4));
        poly1.addPoint(Vector2D(-0.4,1.4));
        poly1.addPoint(Vector2D(0.5,-0.5));
        poly1.addPoint(Vector2D(1.4,-0.4));
        poly1.addPoint(Vector2D(0.5,1.5));
        poly1.addPoint(Vector2D(1.5,0.5));
        poly1.addPoint(Vector2D(1.4,1.4));
        poly1.addPoint(Vector2D(-0.5,0.5));*/

        /*poly1.addPoint(Vector2D(0.2,0.2));

        poly1.addPoint(Vector2D(0.5,1.5));
        poly1.addPoint(Vector2D(-0.3,0.5));*/



        poly1.translate(Vector2D(-0.5,-0.5));
        poly1.scale(3.5);
        poly1.name = QString("Non Convex");

        Polygone poly2 = Convexe2D(poly1.getPoints());
        //poly2.translate(Vector2D(1.5,0));

        poly2.name = QString("Convex");

        glWin.addPoly(poly1);
        glWin.addPoly(poly2);




        //Polygone poly4 = Convexe2D(poly3.getPoints());
        //glWin.addPoly(poly3);





    glWin.show();
    return app.exec();
}


