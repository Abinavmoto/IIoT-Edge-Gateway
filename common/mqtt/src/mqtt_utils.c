#include "../inc/mqtt_utils.h"


//Variable declaration
volatile int finished = 0;
volatile int connected = 0;


MQTTAsync client;
MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;

void connlost(void *context, char *cause)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	LOG_DEBUG("\nConnection lost\n");
	printf("     cause: %s\n", cause);
	LOG_DEBUG("     cause: %s\n", cause);

	printf("Reconnecting\n");
	LOG_DEBUG("Reconnecting\n");
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		LOG_DEBUG("Failed to start connect, return code %d\n", rc);
 		finished = 1;
	}
}

void onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Disconnect failed\n");
	LOG_DEBUG("\n Disconnect failed \n");
	finished = 1;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful disconnection\n");
	LOG_INFO("\n MQTT Successful disconnection \n");
	finished = 1;
}

void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message send failed token %d error code %d\n", response->token, response->code);
	opts.onSuccess = onDisconnect;
	opts.onFailure = onDisconnectFailure;
	opts.context = client;
	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start disconnect, return code %d\n", rc);
		LOG_ERROR(" MQTT Failed to start disconnect, return code % d\n", rc);
		exit(EXIT_FAILURE);
	}
}

void onSend(void* context, MQTTAsync_successData* response)
{
	// This gets called when a message is acknowledged successfully.
}


void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
	LOG_ERROR("\nConnect failed, rc % d\n", response ? response->code : 0);
	finished = 1;
}


void onConnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful connection\n");
	LOG_INFO("\n MQTT Successful connection \n");
	connected = 1;
}

int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m)
{
	//ADD Subcriber logic
	/* not expecting any messages */
	return 1;
}


int MQTTPub(core_context *data, mqtt_context* context)
{
	int ret = 0;

	pubmsg.payload = data->payload;
	pubmsg.payloadlen = strlen(data->payload);
	pubmsg.qos = context->QOS;
	pubmsg.retained = context->retained;

	if ((ret = MQTTAsync_sendMessage(client, context->topic, &pubmsg, &pub_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", ret);
		return ret;
	}
	LOG_INFO("\n MQTT Data Published to %s !! \n", context->topic);
	return ret;

}

void MQTTClose() {
	MQTTAsync_destroy(&client);
}

int MQTTinit(mqtt_context* context) {

	int rc;
	LOG_INFO("\n MQTTinit Started \n");
	if ((rc = MQTTAsync_create(&client, context->Serverip, context->Clientid, context->persistance, NULL)) != MQTTASYNC_SUCCESS)
	{
		LOG_ERROR("Failed to create client object, return code %d\n", rc);
		printf("Failed to create client object, return code %d\n", rc);
		return rc;
	}

	if ((rc = MQTTAsync_setCallbacks(client, NULL, connlost, messageArrived, NULL)) != MQTTASYNC_SUCCESS)
	{
		LOG_ERROR("Failed to set callback, return code %d\n", rc);
		printf("Failed to set callback, return code %d\n", rc);
		return rc;
	}

	conn_opts.keepAliveInterval = context->KeepAliveinterval;
	conn_opts.cleansession = context->cleansession;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		LOG_ERROR("Failed to start connect, return code %d\n", rc);
		printf("Failed to start connect, return code %d\n", rc);
		return rc;
	}
	pub_opts.onSuccess = onSend;
	pub_opts.onFailure = onSendFailure;
	pub_opts.context = client;
	// need to add Timout logic
	while (!connected) {
		usleep(100000L);
	}

	return rc;
}

