
#ifndef MQTT_UTILS_H_
#define MQTT_UTILS_H_



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "MQTTAsync.h"
#include "../../log/inc/log_utils.h"

#define MAX_LEN 255
#define MAX_PAYLOAD_LEN 65525

typedef struct {
	char Serverip[MAX_LEN];
	char topic[MAX_LEN];
	char Clientid[MAX_LEN];
	int QOS;
	int Timeout;
	int KeepAliveinterval;
	int cleansession ;
	int persistance;
	int retained;
}mqtt_context;

typedef struct {
	unsigned long long cur_time; /* milliseconds */
	unsigned long long prev_time ; /* milliseconds */
	char timestamp[MAX_LEN];
	char payload[MAX_PAYLOAD_LEN];
	int payload_Interval;/* milliseconds */
}core_context;

typedef struct {
	int debuglevel;
}log_context;


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