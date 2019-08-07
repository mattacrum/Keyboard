#include "socketconnection.h"

socketConnection::socketConnection(QObject *parent)
    : QObject(parent)
{

}

void socketConnection::doConnect()
{
    socket = new QLocalSocket(this);
    QDataStream socketStream(socket);
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    socket->setServerName("/home/seniordesign/eye-track/EyeTrack/servsock");
    socket->connectToServer(QIODevice::ReadOnly);

    if(!socket->waitForConnected(5000))
        {
            qDebug() << "Error: " << socket->errorString();
        }
}

bool socketConnection::connected()
{
    qDebug() << "connected...";
    return true;
}

void socketConnection::disconnected()
{
    qDebug() << "disconnected...";
}

void socketConnection::bytesWritten(qint64 bytes)
{
 //   qDebug() << bytes << " bytes written...";
}

void socketConnection::readyRead()
{
    qDebug() << "reading...";

    qDebug() << socket->read(0);

    socketStream.setDevice(socket);
    socketStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    socketStream.setByteOrder(QDataStream::LittleEndian);
    socketStream.startTransaction();

    socketStream >> x >> y >> z;
  //  qDebug() << x << " " << y << " " << z;

    socketStream.abortTransaction();

}
