#include "calibration.h"
#include "keyboard.h"
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
    cursor = new QCursor();

    display = new QTextEdit("");
    display->setReadOnly(true);
    display->setStyleSheet("background-color:white;"
                           "color:black;");
    display->setGeometry(500, 0, 120, 60);
    display->setMaximumSize(120,60);

    mainLayout->addWidget(display);

    startTimer = new QTimer(this);
    startTimer->setInterval(1000);
    display->setText("Starting Calibration...");
    connect(startTimer, SIGNAL(timeout()), this, SLOT(startTimerTimeout()));

    startTimerCount = 3;
    if(!startTimer->isActive())
        startTimer->start();
}

void Calibration::paintEvent(QPaintEvent *)
{
    int w = this->width();
    int h = this->height();

    QRectF ir1(w-.80*w, h-.75*h, 25.0, 25.0);
    QRectF ir2(w-.50*w, h-.75*h, 25.0, 25.0);
    QRectF ir3(w-.20*w, h-.75*h, 25.0, 25.0);

    QRectF ir4(w-.80*w, h-.25*h, 25.0, 25.0);
    QRectF ir5(w-.50*w, h-.25*h, 25.0, 25.0);
    QRectF ir6(w-.20*w, h-.25*h, 25.0, 25.0);


    QRectF or1(ir1.x() - 62.5, ir1.y() - 62.5, 150.0, 150.0);
    QRectF or2(ir2.x() - 62.5, ir2.y() - 62.5, 150.0, 150.0);
    QRectF or3(ir3.x() - 62.5, ir3.y() - 62.5, 150.0, 150.0);

    QRectF or4(ir4.x() - 62.5, ir4.y() - 62.5, 150.0, 150.0);
    QRectF or5(ir5.x() - 62.5, ir5.y() - 62.5, 150.0, 150.0);
    QRectF or6(ir6.x() - 62.5, ir6.y() - 62.5, 150.0, 150.0);

    QRectF fp1[2] = {ir1,or1};
    QRectF fp2[2] = {ir2,or2};
    QRectF fp3[2] = {ir3,or3};
    QRectF fp4[2] = {ir4,or4};
    QRectF fp5[2] = {ir5,or5};
    QRectF fp6[2] = {ir6,or6};

    drawFocusPoints(fp1,fp2,fp3,fp4,fp5,fp6);


}

void Calibration::startTimerTimeout()
{
    --startTimerCount;
    if (startTimerCount <= -1)
    {
        startTimer->stop();
        timer = new QTimer(this);
        timer->setInterval(2000);
        timerCount = 6;
        connect(timer, SIGNAL(timeout()), this, SLOT(focusPointTimerTimeout()));
        timer->start();

       // hide();
    }
    else if (startTimerCount == 2)
        display->setText("3");
    else if (startTimerCount == 1)
        display->setText("2");
    else if (startTimerCount == 0)
        display->setText("1");

}

void Calibration::focusPointTimerTimeout()
{
    --timerCount;
    if (timerCount <= -1)
    {
        timer->stop();
        calibrate();
        hide();
    }
}

void Calibration::drawFocusPoints(QRectF fp1[], QRectF fp2[], QRectF fp3[], QRectF fp4[], QRectF fp5[], QRectF fp6[])
{
    QPainter painter(this);


    if (timerCount == 5)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp1[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp1[0]);

           coordinateError1[0] = (int)fp1[1].center().x() - QCursor::pos().x();
           coordinateError1[1] = (int)fp1[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp1[1].center().x()) + ", " +
                            QString::number((int)fp1[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");

    }

    if (timerCount == 4)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp2[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp2[0]);

           coordinateError2[0] = (int)fp2[1].center().x() - QCursor::pos().x();
           coordinateError2[1] = (int)fp2[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp2[1].center().x()) + ", " +
                            QString::number((int)fp2[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");
    }

    if (timerCount == 3)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp3[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp3[0]);

           coordinateError3[0] = (int)fp3[1].center().x() - QCursor::pos().x();
           coordinateError3[1] = (int)fp3[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp3[1].center().x()) + ", " +
                            QString::number((int)fp3[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");
    }

    if (timerCount == 2)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp4[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp4[0]);

           coordinateError4[0] = (int)fp4[1].center().x() - QCursor::pos().x();
           coordinateError4[1] = (int)fp4[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp4[1].center().x()) + ", " +
                            QString::number((int)fp4[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");
    }

    if (timerCount == 1)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp5[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp5[0]);

           coordinateError5[0] = (int)fp5[1].center().x() - QCursor::pos().x();
           coordinateError5[1] = (int)fp5[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp5[1].center().x()) + ", " +
                            QString::number((int)fp5[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");
    }

    if (timerCount == 0)
    {
           painter.setBrush(Qt::black);
           painter.setPen(QPen(Qt::white, 2));
           painter.drawEllipse(fp6[1]);
           painter.setBrush(Qt::white);
           painter.drawEllipse(fp6[0]);

           coordinateError6[0] = (int)fp6[1].center().x() - QCursor::pos().x();
           coordinateError6[1] = (int)fp6[1].center().y() - QCursor::pos().y();


           display->setText("(" + QString::number((int)fp6[1].center().x()) + ", " +
                            QString::number((int)fp6[1].center().y()) + ")" +
                            "    - " + "(" + QString::number(QCursor::pos().x()) + ", " +
                            QString::number(QCursor::pos().y()) + ")");
    }

    this->update();

}


void Calibration::calibrate()
{
    x = ((coordinateError1[0] + coordinateError2[0] + coordinateError3[0]
           + coordinateError4[0] + coordinateError5[0] + coordinateError6[0]) / 6) ;

    y = ((coordinateError1[1] + coordinateError2[1] + coordinateError3[1]
             + coordinateError4[1] + coordinateError5[1] + coordinateError6[1]) / 6) ;


    QString coordx = QString::number(x + QCursor::pos().x());
    QString coordy = QString::number(y + QCursor::pos().y());

    display->setText("(" + coordx + ", " + coordy + ")");

   // mousePosError->setX(x);
   // mousePosError->setY(y);
    //int mpex = x + QCursor::pos().x()


}

void Calibration::returnToKeyboard(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        hide();
    }
}
