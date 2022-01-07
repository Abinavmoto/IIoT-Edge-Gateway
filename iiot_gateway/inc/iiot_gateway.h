#ifndef IIOT_GATEWAY_H_
#define IIOT_GATEWAY_H_


#include "../../common/mqtt/inc/mqtt_utils.h"
#include "../../common/config/inc/conf_utils.h"
#include "../../common/utils/inc/utils.h"

int core_Init(char* Confpath);
int core_routine();


#endif 