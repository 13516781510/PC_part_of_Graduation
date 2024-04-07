#include <QApplication>
#include "../UI/myui.hpp"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	myui w;
	w.show();


	return a.exec();
}

