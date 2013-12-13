#include <QApplication>
#include "CaseVisualizer.h"
#include <QStyleFactory>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("fusion"));

    CaseVisualizer w;
    w.show();
    return a.exec();
}
