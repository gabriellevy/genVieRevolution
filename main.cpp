#include "genvierevolution.h"
#include <QApplication>
#include "urevfrance.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    URevFrance w;
    w.LancerHistoire(URevFrance::VIE_HUMAIN, nullptr, "", "", true );
    w.show();

    return a.exec();
}
