/*config.c*/
/*
To compile : gcc -o config config.c -lconfig
To run     : ./config
*/

#include "../inc/conf_utils.h"


int Confinit(mqtt_context* context)
{
    config_t cfg;               /*Returns all parameters in this structure */
    config_setting_t* setting;
    const char* str1, * str2,* str3 ;

    /*Initialization */
    config_init(&cfg);
    LOG_INFO("\ninit configuration file.");

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
        LOG_INFO("\nBasic configuration for MQTT: %s %s %s", context->Serverip, context->topic, context->Clientid);
        //printf("\nFile Type: %s", str1);
    }
        
    else
        LOG_ERROR("\nNo  setting in configuration file.");


    /*Read the parameter group*/
    setting = config_lookup(&cfg, "MQTTparams");
    if (setting != NULL)
    {
        /*Read the integer*/
        if (config_setting_lookup_int(setting, "QOS", &context->QOS) && config_setting_lookup_int(setting, "Timeout", &context->Timeout) && config_setting_lookup_int(setting, "KeepAliveinterval", &context->KeepAliveinterval)
            && config_setting_lookup_int(setting, "cleansession", &context->cleansession) && config_setting_lookup_int(setting, "persistance", &context->persistance)&& config_setting_lookup_int(setting, "retained", &context->retained))
        {
            LOG_INFO("\nMQTTParams: QOS: %d Timeout: %d KeepAlive: %d Cleansession:%d Persistance: %d Retain: %d", context->QOS, context->Timeout, context->KeepAliveinterval, context->cleansession, context->persistance, context->retained);
        }
        else
            LOG_ERROR("\nNo 'nMQTTParam' setting in configuration file. and err");
    }

    config_destroy(&cfg);
    return 1;
}