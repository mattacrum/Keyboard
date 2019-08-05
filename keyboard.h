#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QtWidgets>
#include <QTextToSpeech>
#include "textedit.h"
#include "calibration.h"

class QTextEdit;

class Button;

class Keyboard : public QWidget
{
    Q_OBJECT

public:
   Keyboard(QWidget *parent = nullptr);
   int calibrationFlag;
   //QCursor *cursor;


private slots:
    void characterClicked();
    void backspaceClicked();
    void speakButtonClicked();
    void clearAllButtonClicked();
    void shiftButtonClicked();
    void newLineButtonClicked();
    void calibrationButtonClicked();
    void pauseButtonClicked();
    void optionButtonClicked();
    void deleteWordButtonClicked();
    void delayTimerTimeout();
    void gestureTimerTimeout();
    void symbolButtonClicked();
    void numbersButtonClicked();
    void yesButtonClicked();
    void noButtonClicked();
  //  void autoComplete();

private:
    Button *createButton(const QString &text, const char * member);

    QTextToSpeech *m_speech;
    void mouseMoveEvent(QMouseEvent* event);
    QPoint getMousePosition();

   // QAbstractItemModel *modelFromFile(const QString& wordlist);

   // QCompleter *completer;

    QTextEdit *display;
    QTextEdit *textPrediction;
    QTimer *delayTimer;
    QTimer *gestureTimer;

    Calibration *Cal;
    QCursor *cursor;

    int timerCount;
    int gestureTimerCount;

    enum { NumCharButtons = 32 };
    Button *characterButtons[NumCharButtons];

    enum { NumNumberRowButtons =  13};
    Button *numberRowButtons[NumNumberRowButtons];

    Button *spacebar;
    Button *backspaceButton;
    Button *pauseButton;
    Button *speakButton;
    Button *clearAllButton;
    Button *shiftButton;
    Button *newLineButton;
    Button *calibrationButton;
    Button *optionButton;
    Button *deleteWordButton;
    Button *symbolButton;
    Button *numbersButton;
    Button *yesButton;
    Button *noButton;

    QRect screenSize;
    int shiftFlag;

    int xError;
    int yError;


};

#endif // KEYBOARD_H
