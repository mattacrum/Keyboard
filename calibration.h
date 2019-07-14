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
private slots:
    void timerTimeout();
private:
    void paintEvent(QPaintEvent *event);

    void drawFocusPoints(QRectF fp1[], QRectF fp2[], QRectF fp3[], QRectF fp4[], QRectF fp5[], QRectF fp6[]);
    QTimer *timer;
    int timerCount;
    QGridLayout *mainLayout;
};

#endif // CALIBRATION_H
