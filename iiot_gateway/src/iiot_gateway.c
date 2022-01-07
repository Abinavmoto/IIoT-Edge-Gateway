#include "../inc/iiot_gateway.h"

core_context core_ctx;
mqtt_context mqtt_ctx;
log_context log_ctx;
int core_Init(char *Confpath)
{
	int ret = 0;
	//Read CONF file
	
	ret = Confinit(&core_ctx,&mqtt_ctx,&log_ctx,Confpath);
	if (ret == -1) {
		return(EXIT_FAILURE); 
	}
	//Initialize logger

	ret = LogInit(log_ctx.debuglevel);
	if (ret ==0) {
		return(EXIT_FAILURE);
	}
	//initialise the MQTT Client

	ret = MQTTinit(&mqtt_ctx);
	if (ret != 1) {
		return(EXIT_FAILURE);
	}
	return(EXIT_SUCCESS);
}

int core_routine() {
	int ret = 0;
	gettime(&core_ctx);
	if (core_ctx.cur_time - core_ctx.prev_time > core_ctx.payload_Interval)
	{
		LOG_INFO("Interval elapsed");
		
		printf("Interval elapssed");
		getPayload(&core_ctx, &mqtt_ctx);
		ret = MQTTPub(&core_ctx, &mqtt_ctx);
		core_ctx.prev_time = core_ctx.cur_time;
		return ret;
		
	}
	return ret;
}



int main(int argc, char* argv[]) {

	char confpath[MAX_LEN];
	if (argc == 1) {
		printf("\nPlease Specify conf.cfg location\n");
		return EXIT_FAILURE;
	}
	if (argc == 2)
		strcpy(confpath, argv[1]);
	
	//is config file present check needs to be added
	int ret = 0; 
	// Init all the Neccesary Preconditions
	ret = core_Init(confpath);
	//Main routine for the Application to run upon
	while (1) {
		core_routine();
	}
	//Destroy or Kill the MQTT Client instance 
	MQTTClose();
	return ret;
}
