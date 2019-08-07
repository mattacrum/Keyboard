#include "mousecontrol.h"
#include "socketconnection.h"
#include "calibration.h"
#include <string>
#include <QtDebug>

mouseControl::mouseControl()
{

}

void mouseControl::calculateMove(float a1, float a2, float b1, float b2, float x1, float x2, float y1, float y2)
{
    while(1)
    {
        a = a1 + (socketConn.x - x1) / (x2 - x1) * (a2 - a1);
        b = b1 + (socketConn.y - y1) / (y2 - y1) * (b2 - b1);

        a = checkA(a);
        b = checkB(b);

        std::string str = "xdotool mousemove " + std::to_string(a) + " " +  std::to_string(b);

        const char *command = str.c_str();
        qDebug() << a << " " << b;
       // system(command);

    }
}

int mouseControl::checkA(int a)
{
    if(a < 0)
    {
        a = 0;
    }
    else if(a > 1920)
    {
        a = 1920;
    }

    return a;
}

int mouseControl::checkB(int b)
{
    if(b < 0)
    {
        b = 0;
    }
    else if(b > 1080)
    {
        b = 1080;
    }

    return b;
}
