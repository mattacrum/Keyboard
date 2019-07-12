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

private:
    void paintEvent(QPaintEvent *event);
    QGridLayout *mainLayout;
};

#endif // CALIBRATION_H
