#include <QApplication>
#include <QFile>

#include "../qt_platform/qt_mainwindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	framework::MainWindow mainWindow;

	//QFile qss("../res/stylesheet.qss");
	//qss.open(QFile::ReadOnly);
	//application.setStyleSheet(qss.readAll());
	//qss.close();

	mainWindow.show();
	return (application.exec());
}
