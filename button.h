#ifndef BUTTON_H
#define BUTTON_H
#include "keyboard.h"
#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = nullptr);

    QSize sizeHint() const override;

private:
    QTimer *dwellTimer;
    int pauseFlag;

private slots:
    void dwellTimerTimeout();

protected:
void hoverEnter(QHoverEvent *event);
void hoverLeave(QHoverEvent *event);
void hoverMove(QHoverEvent *event);
bool event(QEvent *event);
};

#endif
