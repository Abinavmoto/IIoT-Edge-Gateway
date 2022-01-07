#ifndef CONF_UTILS_H_
#define CONF_UTILS_H_

#include "../../mqtt/inc/mqtt_utils.h"
#include "../../log/inc/log_utils.h"
#include <libconfig.h>

int Confinit(core_context* data, mqtt_context* context, log_context* logger , char* Confpath);
#endif 