#include "button.h"

#include <QtWidgets>
#include <QTimer>
Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
   // openDelayTimer = new QTimer(this);
  //  connect(openDelayTimer, SIGNAL(timeout()), this, SLOT(openDelayTimerTimeout()));
   // if(!openDelayTimer->isActive())
   //     openDelayTimer->start(1000);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QFont font = this->font();
    font.setPointSize(12);
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
   // if (pauseFlag == 0)
   // {
        QFont font = this->font();
        font.setBold(true);
        font.setPointSize(16);
        this->setFont(font);
        repaint();
        dwellTimer = new QTimer(this);
        connect(dwellTimer, SIGNAL(timeout()), this, SLOT(dwellTimerTimeout()));
 //       if (!openDelayTimer->isActive())
     //   {
            if(!dwellTimer->isActive())
                dwellTimer->start(1200);
     //   }

  //  }

}

void Button::dwellTimerTimeout()
{
      this->animateClick();
    // add sound to click
}
/*
void Button::openDelayTimerTimeout()
{
      openDelayTimer->stop();
   //   setMouseTracking(true);
   //   setAttribute(Qt::WA_Hover);
    // add sound to click
}
*/
void Button::hoverLeave(QHoverEvent *)
{
    dwellTimer->stop();
    QFont font = this->font();
    font.setPointSize(12);
    font.setBold(false);
    this->setFont(font);
    repaint();
}

void Button::hoverMove(QHoverEvent *)
{
  /*  if (this->text() == "Pause")
    {
        if (dwellTimer->remainingTime() == 0)
        {
            pauseFlag = 1;
        }
    }*/
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(16);
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
