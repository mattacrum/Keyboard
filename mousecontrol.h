#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

#include <QObject>
#include <QWidget>

class mouseControl
{
public:
    mouseControl();
    void calculateMove(float a1, float a2, float b1, float b2, float x1, float x2, float y1, float y2);

private:
    int a;
    int b;
    int checkA(int a);
    int checkB(int b);
};

#endif // MOUSECONTROL_H
