#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QDialog>

class Calibration : public QDialog
{
    Q_OBJECT

public:
    Calibration(QWidget *parent = nullptr);
    QPoint *mousePosError;
    int x;
    int y;
private slots:
    void startTimerTimeout();
    void focusPointTimerTimeout();

private:
    void paintEvent(QPaintEvent *event);
    void calibrate();
    void returnToKeyboard(QKeyEvent *event);
    QTextEdit *display;
    int center[2];  // <--- Crashes if I comment this out?
    void drawFocusPoints(QRectF fp1[], QRectF fp2[], QRectF fp3[], QRectF fp4[], QRectF fp5[], QRectF fp6[]);
    QTimer *timer;
    QTimer *startTimer;
    int timerCount;
    int startTimerCount;
    QCursor *cursor;
    QGridLayout *mainLayout;

    int coordinateError1[2];
    int coordinateError2[2];
    int coordinateError3[2];
    int coordinateError4[2];
    int coordinateError5[2];
    int coordinateError6[2];
};

#endif // CALIBRATION_H
