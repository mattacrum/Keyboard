#include "keyboard.h"
#include "calibration.h"
#include "textedit.h"
#include "socketconnection.h"
#include <QApplication>
#include <QDataStream>
#include <QLocalSocket>
#include <iostream>
#include <QVector>
#include <QtConcurrent>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Keyboard KB;
    QCursor *cursor;
    KB.setStyleSheet("background-color: black");
    QApplication::setStyle("fusion");

    socketConnection socket;


    KB.show();
    socket.doConnect();
    //socketConnection *SC = new socketConnection();


    return app.exec();

}
