#include "../inc/log_utils.h"

int LogInit() {
    int ret = 0;

    ret = logger_initFileLogger("log.txt", 1024 * 1024, 5); //filename,maxFileSize,maxBackupFiles)
    logger_setLevel(LogLevel_DEBUG);
    //LOG_INFO("file logging");
    //LOG_DEBUG("format example: %d%c%s", 1, '2', "3");
    //LOG_TRACE("trace");
    //LOG_DEBUG("degug");
    //LOG_INFO("info");
    //LOG_WARN("warn");
    //LOG_ERROR("error");
    //LOG_FATAL("fatal");
    return ret;
}