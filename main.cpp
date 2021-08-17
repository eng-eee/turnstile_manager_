#include "widget.h"
#include "turnstile_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.setWindowTitle("TURNSTILE_MANAGER");
    return a.exec();
}
