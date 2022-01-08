#include <gtest/gtest.h>
#include <time.h>
#include <sys/time.h>
#include <ctime>

extern "C" {
	#include "../iiot_gateway/inc/iiot_gateway.h"
	#include "../common/utils/inc/utils.h"
	#include "../common/mqtt/inc/mqtt_utils.h"
	#include "../common/log/inc/log_utils.h"
#include "../common/config/inc/conf_utils.h"
}


//since this test is in millisec there may be failed seconds test
TEST(gettime, Check_Time) {
	time_t t;   // not a primitive datatype
	time(&t);
	core_context data_test;
	struct timeval now;
	unsigned long long Test_cur_time; /* milliseconds */
	char Test_timestamp[255];
	gettimeofday(&now, NULL);
	Test_cur_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	strcpy(Test_timestamp, ctime(&t));
	int ret = gettime(&data_test);
	ASSERT_EQ(data_test.cur_time, Test_cur_time);
}
TEST(gettime, Check_Timestamp) {
	time_t t;   // not a primitive datatype
	time(&t);
	core_context data_test;
	struct timeval now;
	unsigned long long Test_cur_time; /* milliseconds */
	char Test_timestamp[255];
	gettimeofday(&now, NULL);
	Test_cur_time = now.tv_sec * 1000 + now.tv_usec / 1000;
	strcpy(Test_timestamp, ctime(&t));
	int ret = gettime(&data_test);
	
	ASSERT_STREQ(data_test.timestamp, Test_timestamp);
}

TEST(Confinit, Check_configfile) {

	core_context data_test;
	mqtt_context context_test;
	log_context logger_test;
	char path[] = "../../test/conf.cfg";
	Confinit(&data_test,& context_test, &logger_test,path);
	ASSERT_STREQ(context_test.Clientid, "DEMOClient");
}
TEST(logger_initFileLogger,Check_LoggerinitFailed)
{
    int result;

    /* when: configure the empty filename */
    result = logger_initFileLogger("", 0, 0);

    /* then: failed */
    ASSERT_EQ(0, result);
}

TEST(logger_initFileLogger, Check_fileLogger)
{
    char test_filename[] = "file.log";
    const char message[] = "Test";
    int result;
    FILE* fp;
    char line[256];
    int count = 0;

    /* when: initialize file logger */
    result = logger_initFileLogger(test_filename, 0, 0);

    /* then: ok */
    ASSERT_EQ(1, result);

    /* when: output to the file */
    LOG_TRACE(message);
    LOG_DEBUG(message);
    LOG_INFO(message);
    logger_flush();

    /* then: write only one line */
    if ((fp = fopen(test_filename, "r")) == NULL) {
        FAIL();
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line) - 1] = '\0'; /* remove LF */
        ASSERT_EQ('I', line[0]);
        ASSERT_STREQ(message, &line[strlen(line) - strlen(message)]);
        count++;
    }
    ASSERT_EQ(1, count);

    /* cleanup: close resources */
    fclose(fp);
    remove(test_filename);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}