#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app_master(argc, argv);

    Widget mainwnd; // add path to db
    mainwnd.show();


    return app_master.exec();
}
