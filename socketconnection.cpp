#include "socketconnection.h"

socketConnection::socketConnection()
{
    socket = new QLocalSocket();
    socket->setServerName("/home/seniordesign/eye-track/EyeTrack/servsock");
    socket->connectToServer(QIODevice::ReadOnly);
    QDataStream socketStream(socket);
    socketStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    socketStream.setByteOrder(QDataStream::LittleEndian);
}

QVector<float> socketConnection::receiveData()
{
    QVector<float> coordinates;
    socketStream.startTransaction();
    if(socket->waitForConnected(-1))
    {
        if(socket->waitForReadyRead())
        {
            if(socketStream.commitTransaction())
            {

                socketStream >> x >> y >> z;
                std::cout << x << " " << y << std::endl;

            }
        }
    }
    socketStream.abortTransaction();
    coordinates.push_back(x);
    coordinates.push_back(y);
    if(coordinates.empty())
    {
        std::cout << "No coordinates received" << std::endl;
        return coordinates;
    }


    return coordinates;

}
