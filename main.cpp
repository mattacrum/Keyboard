#include "keyboard.h"
#include "calibration.h"
#include "textedit.h"
#include "socketconnection.h"
#include "global.h"
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



    KB.show();

    socketConn.doConnect();

    return app.exec();

}
