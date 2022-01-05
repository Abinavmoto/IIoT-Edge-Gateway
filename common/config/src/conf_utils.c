/*config.c*/
/*
To compile : gcc -o config config.c -lconfig
To run     : ./config
*/

#include "../inc/conf_utils.h"


int Confinit(core_context* data, mqtt_context* context, log_context* logger)
{
    config_t cfg;               /*Returns all parameters in this structure */
    config_setting_t* MQTTsetting;
    config_setting_t* Payloadsetting;
    config_setting_t* logsetting;
    const char* str1, * str2,* str3 ;
    int debug;
    /*Initialization */
    config_init(&cfg);
    printf("\ninit configuration file.");

    /* Read the file. If there is an error, report it and exit. */
    if (!config_read_file(&cfg, "common/config/conf.cfg"))
    {
        printf("\n%s:%d - %s", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return -1;
    }
    
    /* Get the  Basic configuration for MQTT */
    if (config_lookup_string(&cfg, "Serverip", &str1) && (config_lookup_string(&cfg, "Publishtopic", &str2)) && (config_lookup_string(&cfg, "Clientid", &str3))) {
        strcpy(context->Serverip, str1);
        strcpy(context->topic, str2);
        strcpy(context->Clientid, str3);
        printf("\nBasic configuration for MQTT: %s %s %s", context->Serverip, context->topic, context->Clientid);
        //printf("\nFile Type: %s", str1);
    }
        
    else
        printf("\nNo  setting in configuration file.");


    /*Read the parameter group*/
    MQTTsetting = config_lookup(&cfg, "MQTTparams");
    if (MQTTsetting != NULL)
    {
        /*Read the integer*/
        if (config_setting_lookup_int(MQTTsetting, "QOS", &context->QOS) && config_setting_lookup_int(MQTTsetting, "Timeout", &context->Timeout) && config_setting_lookup_int(MQTTsetting, "KeepAliveinterval", &context->KeepAliveinterval)
            && config_setting_lookup_int(MQTTsetting, "cleansession", &context->cleansession) && config_setting_lookup_int(MQTTsetting, "persistance", &context->persistance)&& config_setting_lookup_int(MQTTsetting, "retained", &context->retained))
        {
            printf("\nMQTTParams: QOS: %d Timeout: %d KeepAlive: %d Cleansession:%d Persistance: %d Retain: %d", context->QOS, context->Timeout, context->KeepAliveinterval, context->cleansession, context->persistance, context->retained);
        }
        else
            printf("\nNo 'nMQTTParam' setting in configuration file. and err");
    }
    /*Read the parameter group*/
    Payloadsetting = config_lookup(&cfg, "PayloadParams");
    if (Payloadsetting != NULL)
    {
        /*Read the integer*/
        if (config_setting_lookup_int(Payloadsetting, "PayloadInterval", &data->payload_Interval))
        {
        printf("\nPayloadParams: PayloadInterval: %d ", data->payload_Interval);
        }
        else
            printf("\nNo 'nPayloadParams' setting in configuration file. and err");
    }
    ///*Read the parameter group*/
    logsetting = config_lookup(&cfg, "LogParams");

    if (logsetting != NULL)
    {

        /*Read the integer*/
        if (config_setting_lookup_int(logsetting, "LOGLEVEL", &logger->debuglevel))
        {
        printf("\nLogParams: Debuglevel: %d ",logger->debuglevel);
        }
        else
            printf("\nNo 'LogParams' setting in configuration file. and err");
    }
    config_destroy(&cfg);
    return 1;
}