#include <QApplication> 
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWidget main_widget;
    main_widget.show();

    return app.exec();
}