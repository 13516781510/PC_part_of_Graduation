//
// Created by 29451 on 2024/4/2.
//
#ifndef CLION_QT1_MYCLIENT_HPP
#define CLION_QT1_MYCLIENT_HPP

#include "MQTTAsync.h"
#include <windows.h>
#include "iostream"
#include "json.hpp"

class Myclient {

public:

	MQTTAsync pubclient;
	MQTTAsync_responseOptions pubopts;
	MQTTAsync_message pubmsg;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;

	void Createclient();

	int num_yuantong;
	int num_shunfeng;
	int num_yunda;
	bool state_robotic;
	char username[65] = "app1&k0eudLzkYR8";
	char password[65] = "0ea5530e7102db70088e68774060f592de3083b9e242d2de6d596840a77d6528";

	void do_send(nlohmann::json &json);

	bool is_marryed_so_changed;
	double pipeline_speed;
};


#endif //CLION_QT1_MYCLIENT_HPP
