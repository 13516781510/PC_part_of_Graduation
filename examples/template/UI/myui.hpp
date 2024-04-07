#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ui.hpp"
QT_BEGIN_NAMESPACE
//namespace Ui {
//	class myui;
//}
QT_END_NAMESPACE

class myui : public QWidget
{
Q_OBJECT

public:
	myui(QWidget *parent = nullptr);
	~myui();

private:
	Ui::helloworld *ui;
};
#endif // WIDGET_H
