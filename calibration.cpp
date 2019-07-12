#include "calibration.h"
//#include "keyboard.h"
#include "button.h"
#include <QtWidgets>
#include <QTimer>
#include <QWidget>
#include <QGraphicsEllipseItem>

Calibration::Calibration(QWidget *parent)
    : QDialog(parent)
{

    QGridLayout *mainLayout = new QGridLayout;
    setLayout(mainLayout);
    setWindowTitle(tr("Calibration"));
}

void Calibration::paintEvent(QPaintEvent *)
{
    int w = this->width();
    int h = this->height();

    QRectF ir1(w-.75*w, h-.75*h, 25.0, 25.0);

    QRectF ir2(w-.50*w, h-.75*h, 25.0, 25.0);
    QRectF ir3(w-.25*w, h-.75*h, 25.0, 25.0);

    QRectF ir4(w-.75*w, h-.25*h, 25.0, 25.0);
    QRectF ir5(w-.50*w, h-.25*h, 25.0, 25.0);
    QRectF ir6(w-.25*w, h-.25*h, 25.0, 25.0);

    QRectF or1(ir1.x() - 37.5, ir1.y() - 37.5, 100.0, 100.0);
    QRectF or2(ir2.x() - 37.5, ir2.y() - 37.5, 100.0, 100.0);
    QRectF or3(ir3.x() - 37.5, ir3.y() - 37.5, 100.0, 100.0);

    QRectF or4(ir4.x() - 37.5, ir4.y() - 37.5, 100.0, 100.0);
    QRectF or5(ir5.x() - 37.5, ir5.y() - 37.5, 100.0, 100.0);
    QRectF or6(ir6.x() - 37.5, ir6.y() - 37.5, 100.0, 100.0);

    QPainter painter(this);

    //QTimer *timer = new QTimer(this);
   // connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));


    //timer->start(12000);
    //if (timer->remainingTime() == 6000)

    painter.setBrush(Qt::black);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawEllipse(or1);
    painter.drawEllipse(or2);
    painter.drawEllipse(or3);

    painter.drawEllipse(or4);
    painter.drawEllipse(or5);
    painter.drawEllipse(or6);

    painter.setBrush(Qt::white);
    painter.drawEllipse(ir1);
    painter.drawEllipse(ir2);
    painter.drawEllipse(ir3);

    painter.drawEllipse(ir4);
    painter.drawEllipse(ir5);
    painter.drawEllipse(ir6);


}
