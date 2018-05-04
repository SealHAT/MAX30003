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
//#include "driver_init.h"
//#include "max30003types.h"

//constant setup for default values in register
// const MAX30003_CNFG_GEN_VALS CNFGGEN_VALS_DEFAULT = {
// 	//.en_ulp_lon = ENULPLON_ENABLED,
// 	.en_ecg = ENECG_ENABLED
// };
extern const MAX30003_CNFG_GEN_VALS CNFGGEN_VALS_DEFAULT;
extern const MAX30003_CNFG_ECG_VALS CNFECG_VALS_DEFAULT;
extern const MAX30003_EN_INT_VALS EN_INT_VALS_DEFAULT;
extern const MAX30003_EN_INT_VALS EN_INT2_VALS_DEFAULT;
extern const MAX30003_MNGR_INT_VALS MNGR_INT_VALS_DEFAULT;

void MAX30003_INIT_TEST();
bool MAX30003_INIT_TEST_ROUND();
void MAX30003_INIT_SETUP();
void MAX30003_TEST_TRANS_RATE();
void MAX30003_TEST_GAIN();
void MAX30003_TEST_Fre();
void MAX30003_TEST_HELLO_WORLD();
void MAX30003_FLAG_TEST();
void MAX30003_FIFO_TEST();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003TEST_H */
