#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <QObject>
#include <QWidget>
#include <QDataStream>
#include <QLocalSocket>
#include <iostream>
#include <QVector>

class socketConnection
{
public:
    socketConnection();
    QVector<float> receiveData();
    float x, y, z;

private:
    QLocalSocket* socket;
    QDataStream socketStream;
};

#endif // SOCKETCONNECTION_H
