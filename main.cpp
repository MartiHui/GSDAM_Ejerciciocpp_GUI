#include "gui.h"
#include "interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    QString mode = argv[1];

//    if (mode == "consola") {
//        Interface* interface = new Interface;
//            interface->mainMenu();

//            //delete interface; <- crashea el programa y no se porque
//    } else if (mode == "gui") {
//        QApplication a(argc, argv);
//        GUI w;
//        w.show();

//        return a.exec();
//    }

//    return 0;

    QApplication a(argc, argv);
    GUI w;
    w.show();

    return a.exec();
}
