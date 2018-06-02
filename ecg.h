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

#ifdef __cplusplus
extern "C"
{
#endif

//libraries we used in ecg.h
#include "max30003.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


/**
 * Ekg Configuration enum
 *
 * Each represents the results indicating if the configuration applied or not. 
 * Config_Failure would not result any extra influence on registers 
 */
typedef enum config_status {
	SAME_CONFIG = 0,
	CONFIG_SUCCESS = 1,
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

//int32_t ECG_LOG;


/**
 * ecg_change_gain
 *
 * Change cnfg_ecg register D[17:16] value to achieve the goal of adjusting gain 
 * of ecg. This allow you to input any CNFGECG_GAIN_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFG_ECG_GAIN_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_gain(CNFGECG_GAIN_VAL vals);

/**
 * ecg_change_lowfre
 *
 * Change cnfg_ecg register D[13:12] value to achieve the goal of adjusting digital 
 * low-pass filter of ecg. This allow you to input any CNFGECG_DLPF_VAL, and the func 
 * checks for should any changes need to be applied if the settings already applied
 * Be sure to check DLPF availability at certain data rates(see MAX30003 data sheet).
 * recommend to change data rate before apply any changes of DLPF 

 * @param CNFG_ECG_DLPF_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals);

/**
 * ecg_change_datarate
 *
 * Change cnfg_ecg register D[23:22] value to achieve the goal of adjusting sample 
 * rate of ecg. This allow you to input any CNFGECG_RATE_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFG_ECG_RATE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_datarate(CNFGECG_RATE_VAL vals);

/**
 * ecg_init()
 *
 * Initializes and starts the ekg module with the default configurations
 * (see doucumentation for default ekg config)
 *
 * @return CONFIG_SUCCESS if successful, CONFIGFAILURE if initialization fails
 */
config_status ecg_init();

/**
 * ecg_switch
 *
 * Change cnfg_gen register D[19] value to achieve the goal of adjusting switch 
 * of ecg. This allow you to input any CNFGGEN_EN_ECG_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFGGEN_EN_ECG_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals);

/**
 * ecg_dcloff_switch
 *
 * Change cnfg_gen register D[13:12] value to achieve the goal of enable dc 
 * lead-off detection. This allow you to choose enable dc lead-off detection 
 * or not, the func checks for should any changes need to be applied if the 
 * settings already applied

 * @param CNFGGEN_EN_DCLOFF_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals);

/**
 * ecg_dcloff_ipol
 *
 * Change cnfg_ecg register D[11] value to achieve the goal of change dc  
 * lead-off current polarity of ecg. This allow you to input any DCLOFF_IPOL_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_IPOL_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals);

/**
 * ecg_dcloff_imag
 *
 * Change cnfg_ecg register D[10:8] value to achieve the goal of change dc  
 * lead-off current magnitude of ecg. This allow you to input any DCLOFF_IMAG_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_IMAG_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals);

/**
 * ecg_dcloff_vth
 *
 * Change cnfg_ecg register D[7:6] value to achieve the goal of change dc  
 * lead-off voltage threshold of ecg. This allow you to input any DCLOFF_VTH_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_VTH_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals);

/**
 * ecg_en_rbias
 *
 * Change cnfg_ecg register D[5:4] value to achieve the goal of enable
 * resistive lead-bias mode of ecg. This allow you to input any CNFGGEN_EN_RBIAS_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_EN_RBIAS_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals);

/**
 * ecg_en_rbiasv
 *
 * Change cnfg_ecg register D[3:2] value to achieve the goal of change
 * resistive lead-bias mode vale of ecg. This allow you to input any CNFGGEN_RBIASV_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASV_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals);

/**
 * ecg_en_rbiasp
 *
 * Change cnfg_ecg register D[1] value to achieve the goal of enable resistive lead-bias mode
 * on positive input of ecg. This allow you to input any CNFGGEN_RBIASV_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASP_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals);

/**
 * ecg_en_rbiasn
 *
 * Change cnfg_ecg register D[0] value to achieve the goal of enable resistive lead-bias mode
 * on negative input of ecg. This allow you to input any CNFGGEN_RBIASN_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASN_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals);

/**
 * ecg_en_dcloff_int
 *
 * enable the dc-lead off interrupt into either interrupt pin(1 or 2), detailed setup for dc-lead off detection is refered to func
 * with key word "dc" such as ecg_dcloff_vth() or ecg_dcloff_imag()

 * @param int_pin(see ecg.h), ENINT_ENDCLOFFINT_VAL(see max30003types.h), ENINT_INTBTYPE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_dcloff_int(int_pin pin, ENINT_ENDCLOFFINT_VAL vals, ENINT_INTBTYPE_VAL type);

/**
 * ecg_en_lon_int
 *
 * enable the lead on interrupt into either interrupt pin(1 or 2)

 * @param int_pin(see ecg.h), ENINT_ENLONINT_VAL(see max30003types.h), ENINT_INTBTYPE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_lon_int(int_pin pin, ENINT_ENLONINT_VAL vals, ENINT_INTBTYPE_VAL type);

/**
 * ecg_en_evof_int
 *
 * enable the fifo-overflow interrupt into either interrupt pin(1 or 2)

 * @param int_pin(see ecg.h), ENINT_ENLONINT_VAL(see max30003types.h), ENINT_INTBTYPE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_evof_int(int_pin pin, ENINT_ENEOVF_VAL vals, ENINT_INTBTYPE_VAL type);

/**
 * ecg_fifo_thres
 *
 * func to setup for ecg fifo interrupt threshold(issues FIFO Interrupt based on number of unread FIFO records, 
 * default value is 16, respectively MNGRINT_EFIT_VAL+1, this has be done before setup fifo interrupt pin

 * @param  MNGRINT_EFIT_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_fifo_thres(MNGRINT_EFIT_VAL vals);

/**
 * ecg_en_fifo_int
 *
 * enable the fifo interrupt into either interrupt pin(1 or 2) to tell the controller that fifo has stored enough
 * data to read

 * @param int_pin(see ecg.h), ENINT_ENLONINT_VAL(see max30003types.h), ENINT_INTBTYPE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_fifo_int(int_pin pin, ENINT_ENEINT_VAL vals, ENINT_INTBTYPE_VAL type);

/**
 * ecg_en_int
 *
 * a big func to set up all the interrupt term into one interrupt pin, the func needs to define the all the terms
 * of interrupt including EFINT, EVOF_INT, LON_INT, DCLOFF_INT, INTB(pin type) whether they are disabled or not, 
 * once put in the func, all these term will or in the pin with type you setup 
 
 * @param int_pin(see ecg.h), MAX30003_EN_INT_VALS(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_int(int_pin pin, MAX30003_EN_INT_VALS vals);

/**
 * ecg_sampling_process
 *
 * make the ecg start sampling and record data in the array. It set the initial place as the beginning of the array
 * to store the data in certain size. The parameter called SIZE should not beyond 850(Important!!!!!) to make sure 
 * few garbage data generate. The sum of initial point and SIZE should not beyond (size of storage array - 200) to 
 * make sure we do not collect garbage data(Important!!!!). At the end, we will abandon the last 200 bits of data in storage array
 * because they contains garbage data(Important!!!!). If our data storage array is less or equal than 970 and initial point is 0, then we don't need to 
 * to worry about garbage data, we could make the Initial point + Size = Storage, without minus 200 bits.
 * If I want to start collecting the 1000 sample of ecg data at 10th place at array. 
 * The func should write as ecg_sampling_process(10, Storage, 1000); 
 * @param uint16_t initial_point, signed int voltage[], uint16_t SIZE
 * @return the time step, should equal to the SIZE
 */
uint16_t ecg_sampling_process(uint16_t initial_point, ECG_SAMPLE Storage[], uint16_t Desired_Sample_Size);

#ifdef __cplusplus
}
#endif
#endif
