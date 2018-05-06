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
#include <stdbool.h>
#include "max30003.h"

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

extern TEST_ER	test_errno;
extern bool		flag_timeout;
extern bool		int1_level_n;
extern bool		int2_level_n;

extern const int ERROR_STR_LEN;

test_result_t MAX30003_INIT_TEST();
test_result_t MAX30003_INIT_TEST_ROUND();
test_result_t MAX30003_INIT_SETUP();
test_result_t MAX30003_TEST_TRANS_RATE();
test_result_t MAX30003_TEST_GAIN();
test_result_t MAX30003_TEST_Fre();
test_result_t MAX30003_TEST_HELLO_WORLD();
test_result_t MAX30003_FLAG_TEST();
test_result_t MAX30003_FIFO_TEST();

char* error_no_to_string();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003TEST_H */
