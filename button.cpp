#include "button.h"

#include <QtWidgets>
#include <QTimer>
Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

void Button::hoverEnter(QHoverEvent *)
{
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(12);
    this->setFont(font);
    repaint();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));

    if(!timer->isActive())
        timer->start(1200);
}

void Button::timerTimeout()
{
    this->animateClick();
}

void Button::hoverLeave(QHoverEvent *)
{
    timer->stop();

    QFont font = this->font();
    font.setPointSize(10);
    font.setBold(false);
    this->setFont(font);
    repaint();
}

void Button::hoverMove(QHoverEvent *)
{
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(12);
    this->setFont(font);
    repaint();
}

bool Button::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
