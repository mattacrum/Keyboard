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
    QVector<float> receiveData();
    float x, y, z;

    void doConnect();

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QLocalSocket* socket;
    QDataStream socketStream;

};

#endif // SOCKETCONNECTION_H
