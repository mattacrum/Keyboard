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

  //  void autoComplete();

private:
    Button *createButton(const QString &text, const char * member);

    QTextToSpeech *m_speech;

   // QAbstractItemModel *modelFromFile(const QString& wordlist);

   // QCompleter *completer;

    QTextEdit *display;
    QTimer *delayTimer;
    Calibration *Cal;
   // QPoint *newCursorPos;
    //QCursor *cursor;
   // QKeyEvent *event;
    int timerCount;

    enum { NumCharButtons = 29 };
    Button *characterButtons[NumCharButtons];

    enum { NumNumberRowButtons =  13};
    Button *numberRowButtons[NumNumberRowButtons];

    int shiftFlag;


};

#endif // KEYBOARD_H
