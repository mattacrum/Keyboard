#include "button.h"
#include "keyboard.h"
#include "textedit.h"
//#include "calibration.h"
#include <QtWidgets>
#include <QWidget>
#include <string>
#include <cmath>

const int MAX_LENGTH = 200;

Keyboard::Keyboard(QWidget *parent)
    : QWidget(parent)//, completer(0)
{

/*  Create text display  */
    calibrationFlag = 0;
    //display = new TextEdit;
    display = new QTextEdit("");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignLeft);
    display->setMinimumHeight(100);
    display->setMaximumWidth(830);
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
/*
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(modelFromFile(":/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setWrapAround(false);
    display->setCompleter(completer);
*/

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

    for (int i = 0; i < 26; ++i)
    {
        QString text = characterButtons[i]->text();
        characterButtons[i]->setText(text.toLower());
    }

    Button *spacebar = createButton(tr(" "), SLOT(characterClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    backspaceButton->setMinimumWidth(120);

    Button *pauseButton = createButton(tr("Pause"), SLOT(characterClicked()));
    pauseButton->setMinimumWidth(120);

    Button *speakButton = createButton(tr("Speak"), SLOT(speakButtonClicked()));

    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAllButtonClicked()));
    clearAllButton->setMinimumWidth(120);
   // clearAllButton->setMaximumHeight(60);

    Button *shiftButton = createButton(tr("Shift"), SLOT(shiftButtonClicked()));

    Button *newLineButton = createButton(tr("<-------"), SLOT(newLineButtonClicked()));
    Button *calibrationButton = createButton(tr("Calibrate"), SLOT(calibrationButtonClicked()));
/*
 *
 * Add Widgets to Layout
 *
 *
*/

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 15);
    mainLayout->addWidget(backspaceButton, 1, 13,1,2);
    mainLayout->addWidget(spacebar,5,3,1,5);
    mainLayout->addWidget(shiftButton, 5, 1, 1,2);
    mainLayout->addWidget(pauseButton, 2, 11,1,2);
    mainLayout->addWidget(speakButton, 3, 11,1,2);
    mainLayout->addWidget(newLineButton, 4, 11,1,2);
    mainLayout->addWidget(clearAllButton, 0, 12);
    mainLayout->addWidget(calibrationButton, 5, 8);

    for( int i = 0; i < NumNumberRowButtons; ++i)
    {
        mainLayout->addWidget(numberRowButtons[i], 1, i);
    }

    for( int i = 0; i < NumCharButtons; ++i)
    {
        int row = (i / 10)+2;
        int column = ((i) % 10);
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
        for (int i = 0; i < 26; ++i)
        {
            QString text = characterButtons[i]->text();
            characterButtons[i]->setText(text.toLower());
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
        for (int i = 0; i < 26; ++i)
        {
            QString text = characterButtons[i]->text();
            characterButtons[i]->setText(text.toLower());
            shiftFlag = 1;
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

/*  Function to create button  */

Button *Keyboard::createButton(const QString &text, const char *member)
{

    Button *button = new Button(text);
    button->setMinimumSize(60,60);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


/*  Switch to Calibration screen  */

void Keyboard::calibrationButtonClicked()
{
    calibrationFlag = 1;
   // hide();
    Calibration cal;
    timerCount = 6;
    cal.setStyleSheet("background-color:black;");
    cal.setGeometry(200,200,800,600);

    //cal.showFullScreen();
    cal.setModal(true);
    cal.exec();

   // while(1)
   // {
      //  if (event->key() == Qt::Key_Escape)
      //      cal.hide();

   // }




}



/*  Auto Complete Function  */
/*
void Keyboard::autoComplete()
{

}

*/
