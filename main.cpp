#include "keyboard.h"
#include "calibration.h"
#include "textedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   // Q_INIT_RESOURCE(customcompleter);
    QApplication app(argc, argv);
    Keyboard KB;
    KB.setStyleSheet("background-color: black");
    QApplication::setStyle("fusion");
    KB.setGeometry(0, 0, 1400, 1050);

    KB.show();

    return app.exec();

}
