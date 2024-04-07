//
// Created by 29451 on 2024/4/2.
//

#include "MYClient.hpp"

#define ADDRESS     "tcp://iot-06z00jl8tcjx5tf.mqtt.iothub.aliyuncs.com:443"
#define postTOPIC       "/sys/k0eudLzkYR8/app1/thing/event/property/post"
#define subTOPIC        "/sys/k0eudLzkYR8/app1/thing/service/property/set"
#define QOS         1
#define CLIENTID "k0eudLzkYR8.app1|securemode=2,signmethod=hmacsha256,timestamp=1699097397678|"
char clientId[150] = "k0eudLzkYR8.app1|securemode=2,signmethod=hmacsha256,timestamp=1699097397678|";

int finished = 0;
int subscribed = 0;
void *PAYLOAD = (void *) "helloworld!";

void connlost(void *context, char *cause) {
	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);
	printf("reconnecting.....\n");
	Myclient *cl = (Myclient *) context;
	finished = 0;
	subscribed = 0;
	int rc = 0;
	if ((rc = MQTTAsync_connect(cl->pubclient, &cl->conn_opts)) != MQTTASYNC_SUCCESS) {
		printf("Failed to start connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
	printf("Waiting for publication of %s\n"
	       "on topic %s for client\n",
	       PAYLOAD, subTOPIC);

	while (!finished or !subscribed);
}


void onSendFailure(void *context, MQTTAsync_failureData *response) {
	printf("Message send failed token %d error code %d\n", response->token, response->code);
}

void onSend(void *context, MQTTAsync_successData *response) {
	printf("send success\n");
	finished = 1;
}


void onConnectFailure(void *context, MQTTAsync_failureData *response) {
	printf("Connect failed, rc %d\n", response ? response->code : 0);
//	finished = 1;
}

void onSubscribe(void *context, MQTTAsync_successData *response) {
	printf("Subscribe succeeded\n");
	subscribed = 1;
}

void onSubscribeFailure(void *context, MQTTAsync_failureData *response) {
	printf("Subscribe failed, rc %d\n", response->code);
	finished = 1;
}

void onConnect(void *context, MQTTAsync_successData *response) {

	Myclient *pubclient = (Myclient *) context;
	pubclient->pubopts = MQTTAsync_responseOptions_initializer;
	pubclient->pubmsg = MQTTAsync_message_initializer;
	int rc;

	pubclient->pubopts.onSuccess = onSend;
	pubclient->pubopts.onFailure = onSendFailure;
	pubclient->pubopts.context = pubclient;

	pubclient->pubmsg.payload = PAYLOAD;
	pubclient->pubmsg.payloadlen = (int) (strlen("helloworld!"));
	pubclient->pubmsg.qos = QOS;
	pubclient->pubmsg.retained = 0;

	if ((rc = MQTTAsync_sendMessage(pubclient->pubclient, postTOPIC, &pubclient->pubmsg, &pubclient->pubopts)) !=
	    MQTTASYNC_SUCCESS) {
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
	printf("Successful connection\n");

	Sleep(1000);
	printf("Subscribing to topic %s\nfor client %s using QoS%d\n", subTOPIC, CLIENTID, QOS);
	pubclient->opts.onSuccess = onSubscribe;
	pubclient->opts.onFailure = onSubscribeFailure;
	pubclient->opts.context = pubclient;
	if ((rc = MQTTAsync_subscribe(pubclient->pubclient, subTOPIC, QOS, &pubclient->opts)) != MQTTASYNC_SUCCESS) {
		printf("Failed to start subscribe, return code %d\n", rc);
		finished = 1;
	}
}

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
	/* not expecting any messages */
	Myclient *cl = (Myclient *) context;
	try {
		auto jsondata = nlohmann::json::parse((char *) message->payload,
		                                      (char *) message->payload + message->payloadlen);
		if (jsondata.contains("params")) {
			auto json_params = jsondata["params"];
			if (json_params.contains("num_yuantong")) {
				int j = json_params["num_yuantong"];
				cl->num_yuantong = j;
			}
		}
		if (jsondata.contains("params")) {
			auto json_params = jsondata["params"];
			if (json_params.contains("num_shunfeng")) {
				int j = json_params["num_shunfeng"];
				cl->num_shunfeng = j;
			}
		}
		if (jsondata.contains("params")) {
			auto json_params = jsondata["params"];
			if (json_params.contains("num_yunda")) {
				int j = json_params["num_yunda"];
				cl->num_yunda = j;


				if (json_params.contains("num_yunda")) {
					int j = json_params["num_yunda"];
					cl->num_yunda = j;

					if (json_params.contains("pipeline_speed")) {
						double j = json_params["pipeline_speed"];
						cl->pipeline_speed = j;
						cl->is_marryed_so_changed = TRUE;
					}
				}
			}
		}


	} catch (const std::exception &e) {
		std::cerr << "JSON 解析错误: " << e.what() << std::endl;
	}

	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);
	return 1;
}


/* invoke aiotMqttSign to generate mqtt connect parameters */
void Myclient::Createclient() {
	int rc = 0;

	if ((rc = MQTTAsync_create(&this->pubclient, ADDRESS, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL)) !=
	    MQTTASYNC_SUCCESS) {
		printf("Failed to create client object, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	if ((rc = MQTTAsync_setCallbacks(this->pubclient, this, connlost,
	                                 messageArrived, NULL)) != MQTTASYNC_SUCCESS) {
		printf("Failed to set callback, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	this->conn_opts.keepAliveInterval = 60;
	this->conn_opts.cleansession = 1;
	this->conn_opts.onSuccess = onConnect;
	this->conn_opts.onFailure = onConnectFailure;
	this->conn_opts.context = this;
	this->conn_opts.username = this->username;
	this->conn_opts.password = this->password;

	if ((rc = MQTTAsync_connect(this->pubclient, &this->conn_opts)) != MQTTASYNC_SUCCESS) {
		printf("Failed to start connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
	printf("Waiting for publication of %s\n"
	       "on topic %s for client\n",
	       PAYLOAD, subTOPIC);

	while (!finished or !subscribed);

	Sleep(100);
//	MQTTAsync_destroy(&pubclient);
}


void Myclient::do_send(nlohmann::json &json) {
	int rc;

	this->pubmsg.payload = (void *) (json.dump().c_str());
	this->pubmsg.payloadlen = (int) (strlen(json.dump().c_str()));

	if ((rc = MQTTAsync_sendMessage(this->pubclient, postTOPIC, &this->pubmsg, &this->pubopts)) !=
	    MQTTASYNC_SUCCESS) {
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
	printf("Successful connection\n");
}

