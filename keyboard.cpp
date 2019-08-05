#include "button.h"
#include "keyboard.h"
#include "textedit.h"
//#include "calibration.h"
#include "socketconnection.h"
#include <QtWidgets>
#include <QWidget>
#include <string>
#include <cmath>
#include <QSound>

const int MAX_LENGTH = 200;

Keyboard::Keyboard(QWidget *parent)
    : QWidget(parent)//, completer(0)
{

/*  Create text display  */


    calibrationFlag = 0;
    gestureTimerCount = 4;
    xError = 0;//this->width();
    yError = 0;//this->height();
    //pauseFlag = 0;
    shiftFlag = 1;
    //display = new TextEdit;
    display = new QTextEdit("");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignLeft);
    display->setStyleSheet("background-color:white;"
                           "color:black;");
    screenSize = QApplication::desktop()->availableGeometry();
   // screenSize = QGuiApplication::screens()
    display->setMinimumHeight(screenSize.height()*0.3);
    display->setMaximumHeight(screenSize.height()*0.3);
    display->setMinimumWidth(screenSize.width()*.75);
   // display->setMaximumWidth(screenSize.width()*.75);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    setMouseTracking(true);

    gestureTimer = new QTimer(this);
    gestureTimer->setInterval(3000);
    connect(gestureTimer, SIGNAL(timeout()), this, SLOT(gestureTimerTimeout()));



/*
 *
 * Create Buttons
 *
 *
*/
    numberRowButtons[0] = createButton(tr("1"), SLOT(characterClicked()));
    numberRowButtons[1] = createButton(tr("2"), SLOT(characterClicked()));
    numberRowButtons[2] = createButton(tr("3"), SLOT(characterClicked()));
    numberRowButtons[3] = createButton(tr("4"), SLOT(characterClicked()));
    numberRowButtons[4] = createButton(tr("5"), SLOT(characterClicked()));
    numberRowButtons[5] = createButton(tr("6"), SLOT(characterClicked()));
    numberRowButtons[6] = createButton(tr("7"), SLOT(characterClicked()));
    numberRowButtons[7] = createButton(tr("8"), SLOT(characterClicked()));
    numberRowButtons[8] = createButton(tr("9"), SLOT(characterClicked()));
    numberRowButtons[9] = createButton(tr("0"), SLOT(characterClicked()));
    numberRowButtons[10] = createButton(tr("-"), SLOT(characterClicked()));
    numberRowButtons[11] = createButton(tr("+"), SLOT(characterClicked()));
    numberRowButtons[12] = createButton(tr("="), SLOT(characterClicked()));

/*  QWERTY Keyboard
    characterButtons[0] = createButton(tr("Q"), SLOT(characterClicked()));
    characterButtons[1] = createButton(tr("W"), SLOT(characterClicked()));
    characterButtons[2] = createButton(tr("E"), SLOT(characterClicked()));
    characterButtons[3] = createButton(tr("R"), SLOT(characterClicked()));
    characterButtons[4] = createButton(tr("T"), SLOT(characterClicked()));
    characterButtons[5] = createButton(tr("Y"), SLOT(characterClicked()));
    characterButtons[6] = createButton(tr("U"), SLOT(characterClicked()));
    characterButtons[7] = createButton(tr("I"), SLOT(characterClicked()));
    characterButtons[8] = createButton(tr("O"), SLOT(characterClicked()));
    characterButtons[9] = createButton(tr("P"), SLOT(characterClicked()));
    characterButtons[10] = createButton(tr("A"), SLOT(characterClicked()));
    characterButtons[11] = createButton(tr("S"), SLOT(characterClicked()));
    characterButtons[12] = createButton(tr("D"), SLOT(characterClicked()));
    characterButtons[13] = createButton(tr("F"), SLOT(characterClicked()));
    characterButtons[14] = createButton(tr("G"), SLOT(characterClicked()));
    characterButtons[15] = createButton(tr("H"), SLOT(characterClicked()));
    characterButtons[16] = createButton(tr("J"), SLOT(characterClicked()));
    characterButtons[17] = createButton(tr("K"), SLOT(characterClicked()));
    characterButtons[18] = createButton(tr("L"), SLOT(characterClicked()));
    characterButtons[19] = createButton(tr("Z"), SLOT(characterClicked()));
    characterButtons[20] = createButton(tr("X"), SLOT(characterClicked()));
    characterButtons[21] = createButton(tr("C"), SLOT(characterClicked()));
    characterButtons[22] = createButton(tr("V"), SLOT(characterClicked()));
    characterButtons[23] = createButton(tr("B"), SLOT(characterClicked()));
    characterButtons[24] = createButton(tr("N"), SLOT(characterClicked()));
    characterButtons[25] = createButton(tr("M"), SLOT(characterClicked()));
    characterButtons[26] = createButton(tr(","), SLOT(characterClicked()));
    characterButtons[27] = createButton(tr("."), SLOT(characterClicked()));
    characterButtons[28] = createButton(tr("/"), SLOT(characterClicked()));
*/

/*  ABC Keyboard  */
    characterButtons[0] = createButton(tr("A"), SLOT(characterClicked()));
    characterButtons[1] = createButton(tr("B"), SLOT(characterClicked()));
    characterButtons[2] = createButton(tr("C"), SLOT(characterClicked()));
    characterButtons[3] = createButton(tr("D"), SLOT(characterClicked()));
    characterButtons[4] = createButton(tr("E"), SLOT(characterClicked()));
    characterButtons[5] = createButton(tr("F"), SLOT(characterClicked()));
    characterButtons[6] = createButton(tr("G"), SLOT(characterClicked()));
    characterButtons[7] = createButton(tr("H"), SLOT(characterClicked()));
    characterButtons[8] = createButton(tr("I"), SLOT(characterClicked()));
    characterButtons[9] = createButton(tr("J"), SLOT(characterClicked()));
    characterButtons[10] = createButton(tr("K"), SLOT(characterClicked()));
    characterButtons[11] = createButton(tr("L"), SLOT(characterClicked()));
    characterButtons[12] = createButton(tr("M"), SLOT(characterClicked()));
    characterButtons[13] = createButton(tr("N"), SLOT(characterClicked()));
    characterButtons[14] = createButton(tr("O"), SLOT(characterClicked()));
    characterButtons[15] = createButton(tr("P"), SLOT(characterClicked()));
    characterButtons[16] = createButton(tr("Q"), SLOT(characterClicked()));
    characterButtons[17] = createButton(tr("R"), SLOT(characterClicked()));
    characterButtons[18] = createButton(tr("S"), SLOT(characterClicked()));
    characterButtons[19] = createButton(tr("T"), SLOT(characterClicked()));
    characterButtons[20] = createButton(tr("U"), SLOT(characterClicked()));
    characterButtons[21] = createButton(tr("V"), SLOT(characterClicked()));
    characterButtons[22] = createButton(tr("W"), SLOT(characterClicked()));
    characterButtons[23] = createButton(tr("X"), SLOT(characterClicked()));
    characterButtons[24] = createButton(tr("Y"), SLOT(characterClicked()));
    characterButtons[25] = createButton(tr("Z"), SLOT(characterClicked()));
    characterButtons[26] = createButton(tr(","), SLOT(characterClicked()));
    characterButtons[27] = createButton(tr("."), SLOT(characterClicked()));
    characterButtons[28] = createButton(tr("/"), SLOT(characterClicked()));
    characterButtons[29] = createButton(tr("!"), SLOT(characterClicked()));
    characterButtons[30] = createButton(tr("?"), SLOT(characterClicked()));
    characterButtons[31] = createButton(tr("@"), SLOT(characterClicked()));


    spacebar = createButton(tr(" "), SLOT(characterClicked()));

    backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    backspaceButton->setMinimumWidth(110);

    pauseButton = createButton(tr("Pause"), SLOT(pauseButtonClicked()));

    speakButton = createButton(tr("Speak"), SLOT(speakButtonClicked()));

    clearAllButton = createButton(tr("Clear All"), SLOT(clearAllButtonClicked()));
    clearAllButton->setMinimumHeight(60);

    shiftButton = createButton(tr("Shift"), SLOT(shiftButtonClicked()));

    newLineButton = createButton(tr("Return"), SLOT(newLineButtonClicked()));
   /* QCommonStyle style;
    newLineButton->setIcon(style.standardIcon(QStyle::SP_ArrowBack));
    newLineButton->setIconSize({80,40});
    */
    calibrationButton = createButton(tr("Calibrate"), SLOT(calibrationButtonClicked()));

    optionButton = createButton(tr("Options"), SLOT(optionButtonClicked()));

    deleteWordButton = createButton(tr("Delete Word"), SLOT(deleteWordButtonClicked()));

    symbolButton = createButton(tr("Symbols"), SLOT(symbolButtonClicked()));

    numbersButton = createButton(tr("123"), SLOT(numbersButtonClicked()));

    yesButton = createButton(tr("Yes"), SLOT(yesButtonClicked()));
    noButton = createButton(tr("No"), SLOT(noButtonClicked()));

    textPrediction = new QTextEdit("");
    textPrediction->setReadOnly(true);
    textPrediction->setAlignment(Qt::AlignLeft);
    textPrediction->setStyleSheet("background-color:white;"
                           "color:black;");
    textPrediction->setMinimumWidth(230);

/*
 *
 * Add Widgets to Layout
 *
 *
*/
    QGridLayout *mainLayout = new QGridLayout;
  //  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
 //   mainLayout->setSpacing(1);
  //  mainLayout->setVerticalSpacing(1);
    mainLayout->addWidget(display, 0, 0, 1, 10);
    mainLayout->addWidget(textPrediction, 1, 0, 5, 2);
    mainLayout->addWidget(backspaceButton, 1, 11);
    mainLayout->addWidget(pauseButton, 2, 11);
    mainLayout->addWidget(speakButton, 3, 10, 1, 2);
    mainLayout->addWidget(newLineButton, 4, 11);
    mainLayout->addWidget(calibrationButton, 5, 11);
    mainLayout->addWidget(spacebar, 5, 3, 1, 5);
    mainLayout->addWidget(shiftButton, 5, 2, 1,1);
    mainLayout->addWidget(symbolButton, 5, 8);
    mainLayout->addWidget(numbersButton,5,9);
    mainLayout->addWidget(clearAllButton, 0, 10, 1, 2);
    mainLayout->setAlignment(clearAllButton,Qt::AlignBottom);
    mainLayout->addWidget(deleteWordButton, 1, 10);
    mainLayout->addWidget(optionButton,2, 10);

    mainLayout->addWidget(yesButton, 4, 10);
    mainLayout->addWidget(noButton, 5, 10);


/*
    for( int i = 0; i < NumNumberRowButtons; ++i)
    {
        mainLayout->addWidget(numberRowButtons[i], 1, i);
    }
*/
    for( int i = 0; i < NumCharButtons; ++i)
    {
        int row = (i / 8) + 1;
        int column = ((i) % 8) + 2;
        mainLayout->addWidget(characterButtons[i], row, column);
    }

    setLayout(mainLayout);
    setWindowTitle(tr("Keyboard"));


}

/*
 *
 * Callbacks/Slots
 *
 *
*/

void Keyboard::characterClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    std::string characterValue = clickedButton->text().toStdString();

    if (display->toPlainText().length() >= MAX_LENGTH)
        return;

    display->setText(display->toPlainText() + QString::fromStdString(characterValue));

    if (shiftFlag == 1)
    {
        for (int i = 0; i < 26; ++i)
        {
            QString text = characterButtons[i]->text();
            characterButtons[i]->setText(text.toLower());
        }
        shiftFlag = 0;
    }
}

void Keyboard::backspaceClicked()
{
    QString text = display->toPlainText();
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
    }
    display->setText(text);
}

void Keyboard::clearAllButtonClicked()
{
    display->setText("");
}

void Keyboard::speakButtonClicked()
{
    m_speech = new QTextToSpeech(this);
    QString text = display->toPlainText();
    m_speech->say(text);
}

void Keyboard::shiftButtonClicked()
{
    if (shiftFlag == 1)
    {
        for (int i = 0; i < 26; ++i)
        {
            QString text = characterButtons[i]->text();
            characterButtons[i]->setText(text.toLower());
        }
        shiftFlag = 0;
    }
    else
    {
        shiftFlag = 1;

        for (int i = 0; i < 26; ++i)
        {
            QString text = characterButtons[i]->text();
            characterButtons[i]->setText(text.toUpper());
        }
    }
}

void Keyboard::newLineButtonClicked()
{
    if (display->toPlainText().length() >= MAX_LENGTH)
        return;

    display->setText(display->toPlainText() + "\n");
}

void Keyboard::pauseButtonClicked()
{
    if (pauseButton->text() == "Resume")
    {
        pauseButton->setText(("Pause"));
        pauseButton->setStyleSheet("background-color: orange;"
                              "color: white;");
        for(int i = 0; i < NumCharButtons; ++i)
        {
            characterButtons[i]->pauseFlag = 0;
        }

        for(int i = 0; i < NumNumberRowButtons; ++i)
        {
            numberRowButtons[i]->pauseFlag = 0;
        }

        spacebar->pauseFlag = 0;
        backspaceButton->pauseFlag = 0;
        speakButton->pauseFlag = 0;
        clearAllButton->pauseFlag = 0;
        shiftButton->pauseFlag = 0;
        newLineButton->pauseFlag = 0;
        calibrationButton->pauseFlag = 0;
        optionButton->pauseFlag = 0;
        deleteWordButton->pauseFlag = 0;
    }
    else if(this->pauseButton->text() == "Pause")
    {
        pauseButton->setText("Resume");
        pauseButton->setStyleSheet("background-color: cyan;"
                              "color: white;");
        for(int i = 0; i < NumCharButtons; ++i)
        {
            characterButtons[i]->pauseFlag = 1;
        }

        for(int i = 0; i < NumNumberRowButtons; ++i)
        {
            numberRowButtons[i]->pauseFlag = 1;
        }

        spacebar->pauseFlag = 1;
        backspaceButton->pauseFlag = 1;
        speakButton->pauseFlag = 1;
        clearAllButton->pauseFlag = 1;
        shiftButton->pauseFlag = 1;
        newLineButton->pauseFlag = 1;
        calibrationButton->pauseFlag = 1;
        optionButton->pauseFlag = 1;
        deleteWordButton->pauseFlag = 1;

    }
}

void Keyboard::symbolButtonClicked()
{
    if(symbolButton->text() == "Symbols")
    {
        numbersButton->hide();
        characterButtons[0]->setText("[");
        characterButtons[1]->setText("]");
        characterButtons[2]->setText("{");
        characterButtons[3]->setText("}");
        characterButtons[4]->setText("#");
        characterButtons[5]->setText("%");
        characterButtons[6]->setText("^");
        characterButtons[7]->setText("*");
        characterButtons[8]->setText("_");
        characterButtons[9]->setText("\\");
        characterButtons[10]->setText("~");
        characterButtons[11]->setText("<");
        characterButtons[12]->setText(">");
        characterButtons[13]->setText(":");
        characterButtons[14]->setText(";");
        characterButtons[15]->setText("(");
        characterButtons[16]->setText(")");
        characterButtons[17]->setText("|");
        characterButtons[18]->setText("?");
        characterButtons[19]->setText("!");
        characterButtons[20]->setText("'");
        characterButtons[21]->setText("\"");
        characterButtons[22]->setText("");
        characterButtons[23]->setText("");
        characterButtons[24]->setText("$");
        characterButtons[25]->setText("@");
        characterButtons[26]->setText(",");
        characterButtons[27]->setText(".");
        characterButtons[28]->setText("/");

        symbolButton->setText("ABC");
    }
    else
    {
        numbersButton->show();
        characterButtons[0]->setText("A");
        characterButtons[1]->setText("B");
        characterButtons[2]->setText("C");
        characterButtons[3]->setText("D");
        characterButtons[4]->setText("E");
        characterButtons[5]->setText("F");
        characterButtons[6]->setText("G");
        characterButtons[7]->setText("H");
        characterButtons[8]->setText("I");
        characterButtons[9]->setText("J");
        characterButtons[10]->setText("K");
        characterButtons[11]->setText("L");
        characterButtons[12]->setText("M");
        characterButtons[13]->setText("N");
        characterButtons[14]->setText("O");
        characterButtons[15]->setText("P");
        characterButtons[16]->setText("Q");
        characterButtons[17]->setText("R");
        characterButtons[18]->setText("S");
        characterButtons[19]->setText("T");
        characterButtons[20]->setText("U");
        characterButtons[21]->setText("V");
        characterButtons[22]->setText("W");
        characterButtons[23]->setText("X");
        characterButtons[24]->setText("Y");
        characterButtons[25]->setText("Z");
        characterButtons[26]->setText(",");
        characterButtons[27]->setText(".");
        characterButtons[28]->setText("/");

        if (shiftFlag == 0)
        {
            shiftFlag = 1;
            this->shiftButtonClicked();
        }

        symbolButton->setText("Symbols");
    }
}

void Keyboard::numbersButtonClicked()
{
    if(numbersButton->text() == "123")
    {
        symbolButton->hide();
        characterButtons[0]->setText("1");
        characterButtons[1]->setText("2");
        characterButtons[2]->setText("3");
        characterButtons[3]->setText("4");
        characterButtons[4]->setText("5");
        characterButtons[5]->setText("6");
        characterButtons[6]->setText("7");
        characterButtons[7]->setText("8");
        characterButtons[8]->setText("9");
        characterButtons[9]->setText("0");
        characterButtons[10]->setText("-");
        characterButtons[11]->setText("+");
        characterButtons[12]->setText("=");
        characterButtons[13]->setText(":");
        characterButtons[14]->setText(";");
        characterButtons[15]->setText("(");
        characterButtons[16]->setText(")");
        characterButtons[17]->setText("|");
        characterButtons[18]->setText("?");
        characterButtons[19]->setText("!");
        characterButtons[20]->setText("~");
        characterButtons[21]->setText("<");
        characterButtons[22]->setText(">");
        characterButtons[23]->setText("\"");
        characterButtons[24]->setText("$");
        characterButtons[25]->setText("@");
        characterButtons[26]->setText(",");
        characterButtons[27]->setText(".");
        characterButtons[28]->setText("/");

        numbersButton->setText("ABC");
    }
    else
    {
        symbolButton->show();
        characterButtons[0]->setText("A");
        characterButtons[1]->setText("B");
        characterButtons[2]->setText("C");
        characterButtons[3]->setText("D");
        characterButtons[4]->setText("E");
        characterButtons[5]->setText("F");
        characterButtons[6]->setText("G");
        characterButtons[7]->setText("H");
        characterButtons[8]->setText("I");
        characterButtons[9]->setText("J");
        characterButtons[10]->setText("K");
        characterButtons[11]->setText("L");
        characterButtons[12]->setText("M");
        characterButtons[13]->setText("N");
        characterButtons[14]->setText("O");
        characterButtons[15]->setText("P");
        characterButtons[16]->setText("Q");
        characterButtons[17]->setText("R");
        characterButtons[18]->setText("S");
        characterButtons[19]->setText("T");
        characterButtons[20]->setText("U");
        characterButtons[21]->setText("V");
        characterButtons[22]->setText("W");
        characterButtons[23]->setText("X");
        characterButtons[24]->setText("Y");
        characterButtons[25]->setText("Z");
        characterButtons[26]->setText(",");
        characterButtons[27]->setText(".");
        characterButtons[28]->setText("/");

        if (shiftFlag == 0)
        {
            shiftFlag = 1;
            this->shiftButtonClicked();
        }

        numbersButton->setText("123");
    }


}

void Keyboard::yesButtonClicked()
{
    m_speech = new QTextToSpeech(this);
    m_speech->say("Yes");
}

void Keyboard::noButtonClicked()
{
    m_speech = new QTextToSpeech(this);
    m_speech->say("No");
}

/*  Function to create button  */

Button *Keyboard::createButton(const QString &text, const char *member)
{

    Button *button = new Button(text);
    QFont font = button->font();
    font.setPointSize(18);
    button->setFont(font);
   // button->setMinimumSize(screenSize.width() *.065, screenSize.height()*.09);
   // button->setMaximumSize(screenSize.width() *.065, screenSize.height()*.09);
    button->setMinimumWidth(110);
   // button->setMinimumHeight(40);
   // button->setMaximumHeight(40);
    button->setStyleSheet("background-color: blue;"
                          "color: white;"
        //                  "border-style: outset;"
      //                    "border-width: 1px;"
        );//                  "border-color: grey;");
    button->pauseFlag = 0;
    if (button->text() == "Speak")
        button->setStyleSheet("background-color: green;"
                              "color: white;"
                       //       "border-style: outset;"
                        //      "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Clear All")
        button->setStyleSheet("background-color: red;"
                              "color: white;"
                        //      "border-style: outset;"
                        //      "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Backspace")
        button->setStyleSheet("background-color: red;"
                              "color: white;"
                          //    "border-style: outset;"
                          //    "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Delete Word")
        button->setStyleSheet("background-color: red;"
                              "color: white;"
                            //  "border-style: outset;"
                            //  "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Pause")
        button->setStyleSheet("background-color: orange;"
                              "color: white;"
                          //    "border-style: outset;"
                          //    "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Return")
        button->setStyleSheet("background-color: green;"
                              "color: white;"
                           //   "border-style: outset;"
                           //   "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Options")
        button->setStyleSheet("background-color: orange;"
                              "color: white;"
                           //   "border-style: outset;"
                           //   "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Calibrate")
        button->setStyleSheet("background-color: green;"
                              "color: white;"
                           //   "border-style: outset;"
                           //   "border-width: 1px;"
                              );//"border-color: grey;");*/
    if (button->text() == "Symbols")
        button->setStyleSheet("background-color: orange;"
                              "color: white;"
                       //       "border-style: outset;"
                        //      "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "123")
        button->setStyleSheet("background-color: orange;"
                              "color: white;"
                       //       "border-style: outset;"
                        //      "border-width: 1px;"
                              );//"border-color: grey;");
    if (button->text() == "Yes")
        button->setStyleSheet("background-color: purple;"
                              "color: white;"
                           //   "border-style: outset;"
                           //   "border-width: 1px;"
                              );//"border-color: grey;");*/
    if (button->text() == "No")
        button->setStyleSheet("background-color: purple;"
                              "color: white;"
                       //       "border-style: outset;"
                        //      "border-width: 1px;"
                              );//"border-color: grey;");
    connect(button, SIGNAL(clicked()), this, member);

    return button;
}

void Keyboard::optionButtonClicked()
{


}

void Keyboard::deleteWordButtonClicked()
{
    QString text = display->toPlainText();
    int spaceCount = 0;
    int charCount = 0;

    for(int i = 0; i < text.length(); ++i)
    {
        if (text[i] == " ")
            ++spaceCount;
    }
    if (spaceCount == 0)
        text.chop(text.length());
    else {
    for(int j = 0; j < text.length(); ++j)
    {
        if (spaceCount == 0)
            ++charCount;
        if (text[j] == " ")
            --spaceCount;

    }
    }

    text.chop(charCount+1);
    if (text.isEmpty()) {
        text = "";
    }

    display->setText(text);
}


/*  Switch to Calibration screen  */

void Keyboard::calibrationButtonClicked()
{
    calibrationFlag = 1;
    calibrationButton->pauseFlag = 1;

    hide();

    delayTimer = new QTimer(this);
    connect(delayTimer, SIGNAL(timeout()), this, SLOT(delayTimerTimeout()));
    if(!delayTimer->isActive())
        delayTimer->start(1000);
}

void Keyboard::delayTimerTimeout()
{
    delayTimer->stop();
    Calibration cal;
    cal.setStyleSheet("background-color:black;");
    cal.setGeometry(0,0,1400,1050);

    cal.showFullScreen();

    cal.setModal(true);
    cal.exec();

    display->setText("( " + QString::number(cal.x) + " , " + QString::number(cal.y) + " )");
    int px = mapFromGlobal(QCursor::pos()).x();
    int py = mapFromGlobal(QCursor::pos()).y();
    xError = cal.x;
    yError = cal.y;

    showFullScreen();
    calibrationButton->pauseFlag = 0;
   // show();

   // cursor->setPos(cal.x + px, cal.y + py);

}

void Keyboard::gestureTimerTimeout()
{
    --gestureTimerCount;
    if(gestureTimerCount == 3)
    {
        spacebar->setText("Bottom");
        if(cursor->pos().x() < this->width())
        {
            gestureTimerCount = 4;
            spacebar->setText("");
            gestureTimer->stop();
        }

    }

    if(gestureTimerCount == 2)
    {
        spacebar->setText("Left");
        if(cursor->pos().y() != this->height())
        {
            spacebar->setText("");
            gestureTimerCount = 4;
            gestureTimer->stop();
        }
    }

    if(gestureTimerCount == 1)
    {
        spacebar->setText("Calibrating...");
        if(cursor->pos().x() != 0)
        {
            spacebar->setText("");
            gestureTimerCount = 4;
            gestureTimer->stop();
        }
    }

    if(gestureTimerCount == 0)
    {
        calibrationFlag = 1;

        hide();
        gestureTimer->stop();
        gestureTimerCount = 4;
        spacebar->setText("");

        Calibration cal;
        cal.setStyleSheet("background-color:black;");
        cal.setGeometry(0,0,1400,1050);

        cal.showFullScreen();

        cal.setModal(true);
        cal.exec();

        display->setText("( " + QString::number(cal.x) + " , " + QString::number(cal.y) + " )");
        int px = mapFromGlobal(QCursor::pos()).x();
        int py = mapFromGlobal(QCursor::pos()).y();
        xError = cal.x;
        yError = cal.y;

        showFullScreen();
    }
}
void Keyboard::mouseMoveEvent(QMouseEvent *event)
{
   // display->setText("(" + QString::number(cursor->pos().x()) + ", " + QString::number(cursor->pos().y()) + ")");
   // display->setText("(" + QString::number(xError) + ", " + QString::number(yError) + ")");
    int px = mapFromGlobal(cursor->pos()).x();
    int py = mapFromGlobal(cursor->pos()).y();
   // display->setText("(" + QString::number(px) + ", " + QString::number(py) + ")");
  //  QPointF x;
   // x.setX(px + xError);
   // x.setY(py + yError);
//event->setLocalPos(x);
    if (cursor->pos().y() <= 0)
    {
        spacebar->setText("Look to the Right");
        if(!gestureTimer->isActive())
            gestureTimer->start();
    }
    // Set cursor position to corrdinates + error

 //   setMouseTracking(true);
    //QVector<float> coordinates = SC->receiveData();
    /*if(coordinates.size() == 2)
    {
        display->setText(QString::number(coordinates[0]) + " " + QString::number(coordinates[1]));
    }*/


}

QPoint Keyboard::getMousePosition()
{
    return cursor->pos();
}




/*  Auto Complete Function  */
/*
void Keyboard::autoComplete()
{

}

*/
