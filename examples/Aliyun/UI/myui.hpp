#ifndef WIDGET_H
#define WIDGET_H

#include <QPainter>
#include <QWidget>
#include <QPixmap>
#include "ui_Iot.h"
#include <QTimer>
#include <opencv2/opencv.hpp>
#include "../src/MYClient.hpp"
#include "thread"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE



class myui : public QWidget {
Q_OBJECT

public:
	myui(QWidget *parent = nullptr);

	~myui();

private slots:

	void selfupdate();
	void do_connect();
	void open_video();
	void close_video();
	void do_send_open_close();
	void do_send_pipeline_v() const;

	void read_frame();
	void start_thread();
public:
	bool state_open_video;
	void thread1();
	Ui::IOT *ui;
	cv::VideoCapture cap;
	QImage qtimage;
	cv::Mat cvimage;
	QTimer *timer = new QTimer(this);
	QTimer *updatetimer = new QTimer(this);
	Myclient *myclient = new Myclient();


};

#endif // WIDGET_H
