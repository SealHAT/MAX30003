/*
 * max30003test.h
 *
 * Created: 5/2/2018 3:23:31 PM
 *  Author: dli40
 */

#ifndef MAX30003TEST_H
#define MAX30003TEST_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "max30003.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum test_result_t {
    TEST_FAILURE = 0,
    TEST_SUCCESS = 1,
} test_result_t;

typedef enum TEST_ER {
	TEST_NOERROR = 0,
	TEST_TIMEOUT = 1,
	TEST_CFGFAIL = 2,
	TEST_RUNFAIL = 3
} TEST_ER;

/*put here temporary, belong to ecg.h
typedef enum config_status {
	SAME_CONFIG = 0,
	CONFIG_SUCCESS = 1,
	CONFIG_FAILURE = 2
} config_status;*/

extern TEST_ER	test_errno;
extern bool		flag_timeout;
extern bool		int1_level_n;
extern bool		int2_level_n;

extern const int ERROR_STR_LEN;
void ecg_test_welcome();
void ecg_test_run(const char MSG[], uint8_t test_num, test_result_t(*test_function)(void));
void ecg_test_interactive_switch(uint8_t test_num, uint8_t *rval, uint8_t *gval, uint8_t *lval);
void ecg_test_goodbye();

test_result_t MAX30003_INIT_TEST();
test_result_t MAX30003_INIT_TEST_ROUND();
test_result_t MAX30003_INIT_SETUP();
test_result_t MAX30003_TEST_TRANS_RATE();
test_result_t MAX30003_TEST_GAIN();
test_result_t MAX30003_TEST_Fre();
test_result_t MAX30003_TEST_HELLO_WORLD();
test_result_t MAX30003_FLAG_TEST();
test_result_t MAX30003_FIFO_TEST();
test_result_t MAX30003_CONFIG_TEST(const uint8_t SPS, const uint8_t GAIN, const uint8_t LOWPASS);
//temporary here, belong to ecg.h
//config_status ecg_change_datarate(CNFGECG_RATE_VAL vals);

char* error_no_to_string();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003TEST_H */
