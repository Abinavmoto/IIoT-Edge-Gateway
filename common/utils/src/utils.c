
#include "../inc/utils.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MILLISECOND 1000

int Randoms(int lower, int upper)
{
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}

int gettime(core_context* data)
{
    time_t t;   // not a primitive datatype
    time(&t);
    struct timeval now;
    gettimeofday(&now, NULL);
    data->cur_time = now.tv_sec * MILLISECOND + now.tv_usec / MILLISECOND;
    //getTimestamp(&now, data->timestamp, sizeof(data->timestamp));
    //LOG_DEBUG("Get Payload");
    strcpy(data->timestamp, ctime(&t));
    //printf("%s", data->timestamp);
    return EXIT_SUCCESS;
}

int getPayload(core_context* data, mqtt_context* context)
{
    json_object* root = json_object_new_object();
    //printf("Get payload");
    if (!root)
        return 0;
    // terminating the EOF
    data->timestamp[strlen(data->timestamp) - 1] = '\0';

    // adding basic data to JSON Format
    json_object_object_add(root, "Client_ID", json_object_new_string(context->Clientid));
    json_object_object_add(root, "Publish_Topic", json_object_new_string(context->topic));
    json_object_object_add(root, "Time_Stamp", json_object_new_string(data->timestamp));
    // Adding Sensor data
    json_object* sensor_data = json_object_new_object();
    json_object_object_add(sensor_data, "Temperature_Sensor", json_object_new_int(Randoms(30, 100)));
    json_object_object_add(sensor_data, "Interval", json_object_new_int(data->payload_Interval));//in milliseconds
    json_object_object_add(root, "Sensor_data", sensor_data);

    // Copy json payload 
    printf("The json representation:\n\n %s \n\n ", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    strcpy(data->payload, json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    LOG_DEBUG("\n\n %s \n\n", data->payload);
    // cleanup and exit
    json_object_put(root);
    return 1;
}