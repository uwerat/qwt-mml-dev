#include "mainwindow.h"

#include <qapplication.h>

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.resize( 600, 400 );
    w.show();

    return a.exec();
}
