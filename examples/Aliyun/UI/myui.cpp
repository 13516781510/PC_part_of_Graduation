#include "myui.hpp"

void myui::do_connect() {
	printf("connect......\n");
	this->ui->state_pipeline1->setText("正在连接阿里云平台");
	this->myclient->Createclient();
	this->ui->state_pipeline1->setText("已连接阿里云平台");
	this->updatetimer->start(30);
}
void myui::do_send_pipeline_v() const {
	if(!(this->myclient->is_marryed_so_changed)){
		printf("do_send_pipeline_v......\n");
		nlohmann::json json;
		nlohmann::json params;
		params["pipeline_speed"] = (this->ui->set_pipeline_v->value());
		json["params"] = params;
		json["veision"] =  "1.0.0";
		this->myclient->do_send(json);
	}
	this->myclient->is_marryed_so_changed = FALSE;
}
void myui::do_send_open_close() {
	printf("do_send_open_close......\n");
	nlohmann::json json;
	nlohmann::json params;
	this->myclient->state_robotic = !(this->myclient->state_robotic);
	params["ctrl_robotic"] = (this->myclient->state_robotic);
	json["params"] = params;
	json["veision"] =  "1.0.0";
	this->myclient->do_send(json);
	if(this->myclient->state_robotic == 0){
	this->ui->state_robot->setText("已关闭");
	this->ui->open_or_close_robot->setText("开启");
	}
	else if (this->myclient->state_robotic == 1){
		this->ui->state_robot->setText("已开启");
		this->ui->open_or_close_robot->setText("关闭");
	}
}
void myui::selfupdate() {
	this->ui->num_yuantong->setText(QCoreApplication::translate("IOT", std::to_string(this->myclient->num_yuantong).c_str(), nullptr));
	this->ui->num_shunfeng->setText(QCoreApplication::translate("IOT", std::to_string(this->myclient->num_shunfeng).c_str(), nullptr));
	this->ui->num_yunda->setText(QCoreApplication::translate("IOT", std::to_string(this->myclient->num_yunda).c_str(), nullptr));

	if (this->myclient->num_yuantong>=6){
		this->ui->state_yuantong->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (2).png")));
	}
	else if (this->myclient->num_yuantong>=4){
		this->ui->state_yuantong->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242.png")));
	}
	else if(this->myclient->num_yuantong>=0){
		this->ui->state_yuantong->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (1).png")));
	}
	if (this->myclient->num_shunfeng>=6){
		this->ui->state_shunfeng->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (2).png")));
	}
	else if (this->myclient->num_shunfeng>=4){
		this->ui->state_shunfeng->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242.png")));
	}
	else if(this->myclient->num_shunfeng>=0){
		this->ui->state_shunfeng->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (1).png")));
	}
	if (this->myclient->num_yunda>=6){
		this->ui->state_yunda->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (2).png")));
	}
	else if (this->myclient->num_yunda>=4){
		this->ui->state_yunda->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242.png")));
	}
	else if(this->myclient->num_yunda>=0){
		this->ui->state_yunda->setPixmap(QPixmap(QString::fromUtf8(":/1/\345\234\206\350\247\222\347\237\251\345\275\242 (1).png")));
	}

}
QPixmap Mat2Image(cv::Mat src) {
	cv::Mat tmp;
	QImage img;
	if (src.channels() == 3) {
		cv::cvtColor(src, tmp, cv::COLOR_BGR2RGB);
		img = QImage((uchar *) tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
	} else {
		img = QImage((uchar *) src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8);
	}
	QPixmap qimg = QPixmap::fromImage(img);
	return qimg;
}

void myui::read_frame() {

		if(this->cap.read(this->cvimage)){
			QPixmap qpixmap = Mat2Image(this->cvimage);
			this->ui->video1->setPixmap(qpixmap);
	}
}

void myui::open_video() {
	printf("open_video......\n");
	this->cap.open(0);//用自己的摄像头代替
	//this->cap.open("rtsp://admin:123456@192.168.31.233:554/stream0/");//正常走rtsp推流的视频
	this->state_open_video = true;
	this->timer->start(30);
}
void myui::thread1(){
	printf("open_video......\n");
	this->cap.open(0);//用自己的摄像头代替
	while(1){
		if(this->cap.read(this->cvimage)){
			QPixmap qpixmap = Mat2Image(this->cvimage);
			this->ui->video1->setPixmap(qpixmap);
		}
	}
}
void myui::thread2(){
	printf("open_video......\n");
	this->cap.open(1);//用自己的摄像头代替
	while(1){
		if(this->cap.read(this->cvimage)){
			QPixmap qpixmap = Mat2Image(this->cvimage);
			this->ui->video2->setPixmap(qpixmap);
		}
	}

}
void myui::start_thread(){
	printf("open_video......\n");
	std::thread t1(&myui::thread1, this);
	t1.detach(); // 分离线程，让它在后台运行

	std::thread t2(&myui::thread2, this);
	t2.detach(); // 分离线程，让它在后台运行
}
void myui::close_video() {
	printf("close_video......\n");
	this->state_open_video = false;
	this->cap.release();
}

myui::myui(QWidget *parent)
		: QWidget(parent), ui(new Ui::IOT) {
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->ui->setupUi(this);
	myui::connect(ui->connected_button, SIGNAL(clicked()), this, SLOT(do_connect()));
	myui::connect(ui->open_video1, SIGNAL(clicked()), this, SLOT(open_video()));

	myui::connect(ui->close_video1, SIGNAL(clicked()), this, SLOT(close_video()));

	myui::connect(this->updatetimer, SIGNAL(timeout()), this, SLOT(selfupdate()));
	myui::connect(this->ui->open_or_close_robot, SIGNAL(clicked()), this, SLOT(do_send_open_close()));
	myui::connect(this->ui->set_pipeline_v, SIGNAL(valueChanged(double)), this, SLOT(do_send_pipeline_v()));


//	myui::connect(ui->open_video1, SIGNAL(clicked()), this, SLOT(start_thread()));
//	myui::connect(this->timer, SIGNAL(timeout()), this, SLOT(read_frame()));
}

myui::~myui() {
	delete ui;
	delete  timer;
	delete  myclient;
}
