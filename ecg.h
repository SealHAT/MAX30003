/* MIT License
 *
 * Copyright (c) 2018 SealHAT: Seal Heart and Activity Tracker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ECG_H
#define ECG_H

#include "max30003.h"
#include "ecg_types.h"
#define MOD_INT1 (MOD9)
#define MOD_INT2 (MOD2)

#define CNFGGEN_DEFAULT_MASK (CNFGGEN_EN_ECG)
#define CNFGECG_DEFAULT_MASK (CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE)
#define MNGRINT_DEFAULT_MASK (MNGRINT_EFIT)
#define ENINT1_DEFUALT_MASK  (ENINT_INTB_TYPE|ENINT_EN_EINT)
#define ENINT2_DEFUALT_MASK  (ENINT_INTB_TYPE|ENINT_EN_LONINT)

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Ekg Configuration enum
 *
 * Each represents the results indicating if the configuration applied or not.
 * Config_Failure would not result any extra influence on registers
 */
typedef enum config_status {
	CONFIG_SUCCESS = 0,
    SAME_CONFIG    = 1,
	CONFIG_FAILURE = 2
} config_status;

/**
 * Interrupt Pin Configuration enum
 *
 * In the function of setting interrupt pins, we have two choices, this enum
 * is a parameter of the interrupt pin setting func
 */

typedef enum int_pin {
	INT_PIN_1,
	INT_PIN_2
} int_pin;

/**
 * ecg_spi_init
 *  initialize the SPI device and buffers for the ECG
 *  @returns the success value
 */
int32_t ecg_spi_init();

/**
 * ecg_init
 *  initialize the ecg to the desired defaults for the elephant seal deployment
 *  @returns the initialization status
 */
config_status ecg_init();

void ecg_sleep();
void ecg_wake();

#ifdef __cplusplus
}
#endif
#endif
