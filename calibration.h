#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QDialog>
#include <QtConcurrent>
#include "global.h"
#include "mousecontrol.h"


class Calibration : public QDialog
{
    Q_OBJECT

public:
    Calibration(QWidget *parent = nullptr);
    mouseControl* mouse;
    float a;
    float b;

private slots:
    void startTimerTimeout();
    void focusPointTimerTimeout();

private:
    void paintEvent(QPaintEvent *event);
    void calibrate();
    void returnToKeyboard(QKeyEvent *event);
    QTextEdit *display;
   // int center[2];  // <--- Crashes if I comment this out?
    void drawFocusPoints(QRectF fp1[], QRectF fp2[], QRectF fp3[], QRectF fp4[], QRectF fp5[], QRectF fp6[]);
    QTimer *timer;
    QTimer *startTimer;
    int timerCount;
    int startTimerCount;
    QCursor *cursor;
    QGridLayout *mainLayout;

    float a1;
    float b1;
    float a2;
    float b2;
    float x1;
    float x2;
    float y1;
    float y2;


};

#endif // CALIBRATION_H
