
#ifndef UTILS_H_
#define UTILS_H_

#include <json-c/json.h>
#include "../../log/inc/log_utils.h"
#include "../../mqtt/inc/mqtt_utils.h"



int getPayload(core_context* data, mqtt_context* context);
int Randoms(int lower, int upper);
int gettime(core_context* data);
#endif 