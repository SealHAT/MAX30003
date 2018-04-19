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

#ifndef MAX30003_H
#define MAX30003_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplu

#include <stdbool.h>
#include <stdint.h>

#include "max30003types.h"
(uint8_t)(CNFG_GEN << 1) | MAX30003_R_INDICATOR

#define ECG_REG_R(R)    ( (uint8_t)(R << 1) | MAX30003_R_INDICATOR) )
#define ECG_REG_W(R)    ( (uint8_t)(R << 1) | MAX30003_W_INDICATOR) )
#define ECG_BUF_SZ      (64)
#define ECG_BUF_CLR     (0x00)

enum ECG_WORD_POS {
    ECG_CMND_POS = 0,
    ECG_DATA_POS = 1
};

extern uint8_t ECG_BUF_I[ECG_BUF_SZ];
extern uint8_t ECG_BUF_O[ECG_BUF_SZ];

typedef struct MAX30003_DATA_t { uint8_t byte[3]; } MAX30003_DATA_t;
//typedef uint8_t MAX30003_DATA_t[3];
typedef uint8_t MAX30003_ADDR_t;


typedef struct MAX30003_MSG
{
    uint8_t command;
    MAX30003_DATA_t data;
} MAX30003_MSG;

typedef struct MAX30003_CNFG_GEN_VALS {
    MAX30003_CNFG_GEN_RBIASN_VAL        rbiasn;
    MAX30003_CNFG_GEN_RBIASP_VAL        rbiasp;
    MAX30003_CNFG_GEN_RBIASV_VAL        rbiasv;
    MAX30003_CNFG_GEN_EN_RBIAS_VAL      en_rbias;
    MAX30003_CNFG_GEN_DCLOFF_VTH_VAL    vth;
    MAX30003_CNFG_GEN_DCLOFF_IMAG_VAL   imag;
    MAX30003_CNFG_GEN_DCLOFF_IPOL_VAL   ipol;
    MAX30003_CNFG_GEN_EN_DCLOFF_VAL     en_dcloff;
    MAX30003_CNFG_GEN_EN_ECG_VAL        en_ecg;
    MAX30003_CNFG_GEN_FMSTR_VAL         fmstr;
    MAX30003_CNFG_GEN_EN_ULP_LON_VAL    en_ulp_lon;
} MAX30003_CNFG_GEN_VALS;

/* ASF function pointers for using SAML21 calls without cluttering the MAX30003 namespace */
int32_t (*ecg_spi_xfer)(void * descriptor, const void *buffer);		/* spi_xfer */
void    (*ecg_set_csb_level)(const uint8_t pin, const bool level);	/* gpio_set_pin_level */

void ecg_init_spi(void *spi_desc, const void *spi_msg);
void ecg_init_csb(const uint8_t ecg_csb_pin);
void ecg_clear_ibuf();
void ecg_clear_obuf();
void ecg_clear_iobuf();
uint8_t ecg_write(MAX30003_MSG msg);

MAX30003_DATA_t ecg_set_cnfg_gen(MAX30003_CNFG_GEN_VALS vals, const MAX30003_CNFG_GEN_MASKS MASKS);

void ecg_read_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals);

void ecg_write_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, const MAX30003_CNFG_GEN_MASKS MASKS);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003_H */
