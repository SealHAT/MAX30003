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
#include "max30003test.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum config_status {
	SAME_CONFIG = 0,
	CONFIG_SUCCESS = 1,
	CONFIG_FAILURE = 2
} config_status;

config_status ecg_change_gain(CNFGECG_GAIN_VAL vals);
config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals);
config_status ecg_change_datarate(CNFGECG_RATE_VAL vals);
config_status ecg_init();
config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals);
config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals);
config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals);
config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals);
config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals);
config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals);
config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals);
config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals);
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals);
config_status ecg_en_dcloff_int2(ENINT_ENDCLOFFINT_VAL vals,ENINT_INTBTYPE_VAL type);
#ifdef __cplusplus
}
#endif
#endif
