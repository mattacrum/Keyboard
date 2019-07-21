#ifndef BUTTON_H
#define BUTTON_H
#include "keyboard.h"
#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = nullptr);
    int pauseFlag;
    QSize sizeHint() const override;

private:
    QTimer *dwellTimer;
   // QTimer *openDelayTimer;
   // int pauseFlag;

private slots:
    void dwellTimerTimeout();
   // void openDelayTimerTimeout();

protected:
void hoverEnter(QHoverEvent *event);
void hoverLeave(QHoverEvent *event);
void hoverMove(QHoverEvent *event);
bool event(QEvent *event);
};

#endif
