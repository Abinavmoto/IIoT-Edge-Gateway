#include "../inc/iiot_gateway.h"

core_context core_ctx;
mqtt_context mqtt_ctx;

int core_Init()
{
	int ret = 0;
	//Read CONF file
	//	ret = Confinit(); 
	//Added for Prototyping purpose will be removed later
	mqtt_ctx.cleansession = 1;
	strcpy(mqtt_ctx.Clientid, "DemoClient30");
	mqtt_ctx.KeepAliveinterval = 60;
	mqtt_ctx.persistance = MQTTCLIENT_PERSISTENCE_NONE;
	mqtt_ctx.QOS = 1;
	strcpy(mqtt_ctx.Serverip, "tcp://localhost:1883");
	mqtt_ctx.Timeout = 10000L;
	strcpy(mqtt_ctx.topic , "PUB1");
	mqtt_ctx.retained = 0;

	//initialise the MQTT Client

	ret = MQTTinit(&mqtt_ctx);
	if (ret != 0) {
		return 1;
	}
	return 0;
}

int core_routine() {
	int ret = 0;
	//previous time  - current time mills >= timeout
	//logic to be implemented later
	strcpy(core_ctx.payload,"Hello World");
	ret = MQTTPub(&core_ctx,&mqtt_ctx);
	return ret;
}



int main()
{
	//is config file present check needs to be added
	int ret = 0; 
	// Init all the Neccesary Preconditions
	ret = core_Init();
	//Main routine for the Application to run upon

	ret = core_routine();

	//Destroy or Kill the MQTT Client instance 
	MQTTClose();
	return ret;
}
