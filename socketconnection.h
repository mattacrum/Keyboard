#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <QObject>
#include <QWidget>
#include <QDataStream>
#include <QLocalSocket>
#include <iostream>
#include <QVector>
#include <QDebug>

class socketConnection : public QObject
{
    Q_OBJECT
public:
    explicit socketConnection(QObject *parent = 0);
   // socketConnection();
    float x, y, z;
    QLocalSocket* socket;
    void doConnect();

public slots:
    bool connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:

    QDataStream socketStream;

};

#endif // SOCKETCONNECTION_H
