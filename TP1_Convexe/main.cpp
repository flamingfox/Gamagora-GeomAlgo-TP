#include <iostream>

#include "OpenGL/mywindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    myWindow glWin;
    glWin.show();
    return app.exec();
}

