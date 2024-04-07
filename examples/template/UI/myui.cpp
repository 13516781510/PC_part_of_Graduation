#include "myui.hpp"


myui::myui(QWidget *parent)
		: QWidget(parent)
		, ui(new Ui::helloworld)
{
	ui->setupUi(this);

}

myui::~myui()
{
	delete ui;
}
