
#include "../inc/utils.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


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
    data->cur_time = now.tv_sec * 1000 + now.tv_usec / 1000;
    //getTimestamp(&now, data->timestamp, sizeof(data->timestamp));
    //printf("\nThis program has been writeen at (date and time): %s", ctime(&t));
    strcpy(data->timestamp, ctime(&t));
}

int getPayload(core_context* data, mqtt_context* context)
{
    json_object* root = json_object_new_object();
    LOG_DEBUG("Get Payload");
    printf("Get payload");
    if (!root)
        return EXIT_FAILURE;

    // basic data
    json_object_object_add(root, "Client_ID", json_object_new_string(context->Clientid));
    json_object_object_add(root, "Publish_Topic", json_object_new_string(context->topic));
    json_object_object_add(root, "Temperature_Sensor", json_object_new_int(Randoms(30,100)));
    // Timestamp json
    json_object* timeStamp = json_object_new_object();
    json_object_object_add(timeStamp, "Time_Stamp", json_object_new_string(data->timestamp));
    json_object_object_add(timeStamp, "Payload_Interval", json_object_new_int(data->payload_Interval));
    json_object_object_add(root, "TimeStamp", timeStamp);

    // Copy json payload
    printf("The json representation:\n\n%s\n\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    strcpy(data->payload, json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
    LOG_DEBUG("%s", data->payload);
    // cleanup and exit
    json_object_put(root);
    return EXIT_SUCCESS;
}