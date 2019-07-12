#include "keyboard.h"
#include "calibration.h"
#include "textedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   // Q_INIT_RESOURCE(customcompleter);
    QApplication app(argc, argv);
    Keyboard KB;
//    Calibration CAL;

   // KB.setFixedSize(800,600);

   // while(1)
   // {
    //   int c = KB.calibrationFlag;
    //   if (c == 0)
            KB.show();
     //   else if (c == 1)
        //    CAL.showFullScreen();


    return app.exec();
   // }
}
