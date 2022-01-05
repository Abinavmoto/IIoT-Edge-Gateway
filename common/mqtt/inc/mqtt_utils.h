
#ifndef MQTT_UTILS_H_
#define MQTT_UTILS_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTAsync.h"
#include "../../log/inc/log_utils.h"

#define MAX_PAYLOAD_LEN 255

typedef struct {
	char Serverip[MAX_PAYLOAD_LEN];
	char topic[MAX_PAYLOAD_LEN];
	char Clientid[MAX_PAYLOAD_LEN];
	int QOS;
	int Timeout;
	int KeepAliveinterval;
	int cleansession ;
	int persistance;
	int retained;
}mqtt_context;

typedef struct {
	int prev_time;
	int cur_time;
	int Interval;// in millisecods
	char payload[MAX_PAYLOAD_LEN];
}core_context;




int MQTTinit(mqtt_context* context);
int MQTTPub(core_context* data, mqtt_context* context);
void MQTTClose();
int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m);
void onConnect(void* context, MQTTAsync_successData* response);
void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onSend(void* context, MQTTAsync_successData* response);
void onSendFailure(void* context, MQTTAsync_failureData* response);
void onDisconnect(void* context, MQTTAsync_successData* response);
void onDisconnectFailure(void* context, MQTTAsync_failureData* response);
void connlost(void* context, char* cause);

#endif 