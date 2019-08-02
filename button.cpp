#include "button.h"

#include <QtWidgets>
#include <QTimer>
#include <QSound>

Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QFont font = this->font();
    font.setPointSize(18);
    setText(text);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

/* Click Sound for Buttons */
    buttonClick.setSource(QUrl::fromLocalFile("://clickSound.wav"));
    buttonClick.setVolume(0.55f);
    connect(this, &QPushButton::clicked, &buttonClick, &QSoundEffect::play);


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
        font.setPointSize(20);
/*
        if (this->text() == "Speak")
            this->setStyleSheet("background-color: green;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Clear All")
            this->setStyleSheet("background-color: red;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Backspace")
            this->setStyleSheet("background-color: red;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Delete Word")
            this->setStyleSheet("background-color: red;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Pause")
            this->setStyleSheet("background-color: orange;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Resume")
            this->setStyleSheet("background-color: orange;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Return")
            this->setStyleSheet("background-color: green;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Options")
            this->setStyleSheet("background-color: orange;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else if (this->text() == "Calibrate")
            this->setStyleSheet("background-color: green;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
        else
            this->setStyleSheet("background-color: blue;"
                                  "color: white;"
                                  "border-style: outset;"
                                  "border-width: 3px;"
                                  "border-color: grey;");
*/
        this->setFont(font);
        repaint();
        dwellTimer = new QTimer(this);

        if (pauseFlag == 0)
        {
        connect(dwellTimer, SIGNAL(timeout()), this, SLOT(dwellTimerTimeout()));

        if(!dwellTimer->isActive())
            dwellTimer->start(1200);
        }
}

void Button::dwellTimerTimeout()
{
    //if(dwellTimer->isActive())
   // {
        this->animateClick();
   // }
    dwellTimer->stop();
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
    font.setPointSize(18);
    font.setBold(false);
    this->setFont(font);
 /*   if (this->text() == "Speak")
        this->setStyleSheet("background-color: green;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Clear All")
        this->setStyleSheet("background-color: red;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Backspace")
        this->setStyleSheet("background-color: red;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Delete Word")
        this->setStyleSheet("background-color: red;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Pause")
        this->setStyleSheet("background-color: orange;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Resume")
        this->setStyleSheet("background-color: bright green;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Return")
        this->setStyleSheet("background-color: green;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Options")
        this->setStyleSheet("background-color: orange;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else if (this->text() == "Calibrate")
        this->setStyleSheet("background-color: green;"
                              "color: white;"
                              "border-style: outset;"
                              "border-width: 1px;"
                              "border-color: grey;");
    else
        this->setStyleSheet("background-color: blue;"
                              "color: white;"
                              "border-style: ridge;"
                              "border-width: 1px;"
                              "border-color: grey;");*/
    repaint();
}

void Button::hoverMove(QHoverEvent *)
{
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(20);
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
