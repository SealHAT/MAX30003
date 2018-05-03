/*
 * max30003test.h
 *
 * Created: 5/2/2018 3:23:31 PM
 *  Author: dli40
 */ 


#ifndef MAX30003TEST_H_
#define MAX30003TEST_H_





#endif /* MAX30003TEST_H_ */

#include "max30003.h"
#include "driver_init.h"

typedef struct MAX30003_INIT_SETUP_MASK{
	uint32_t ENIT_MASK = 0x803;
	uint32_t ENIT2_MASK = 0x800003;
	uint32_t MNGR_MASK = 0xB80000;
	uint32_t GEN_MASK = 0x80004;
	uint32_t CAL_MASK = 0x30800;
	uint32_t EMUX_MASK = 0xB0000;
	uint32_t ECG_MASK = 0x8500000;
	
}MAX30003_INIT_SETUP_MASK

typedef struct MAX30003_CONFG_SETUP_MASK{
	uint32_t DATA_TRANS_RATE_512sps_MASK = 0x0;
	uint32_t DATA_TRANS_RATE_256sps_MASK = 0x200000;
	uint32_t DATA_TRANS_RATE_128sps_MASK = 0x800000;
	uint32_t GAIN_20V_MASK = 0x0;
	uint32_t GAIN_40V_MASK = 0x10000;
	uint32_t GAIN_80V_MASK = 0x20000;
	uint32_t GAIN_160V_MASK = 0x30000;
	uint32_t BYPASS_MASK = 0x0;
	uint32_t 40HZ_MASK = 0x1000;
	uint32_t 100HZ_MASK = 0x2000;
	uint32_t 150HZ_MASK = 0x3000;
}MAX30003_CONFG_SETUP_MASK

void MAX30003_INIT_TEST();

	