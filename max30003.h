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
#endif // __cplusplus

#include <stdbool.h>
#include <stdint.h>

#include "max30003types.h"

#define ECG_REG_R(REG)  ( (uint8_t)(REG << 1) | MAX30003_R_INDICATOR )
#define ECG_REG_W(REG)  ( (uint8_t)(REG << 1) | MAX30003_W_INDICATOR )
#define ECG_BUF_SZ      (4)
#define ECG_CMND_SZ		(1)
#define ECG_DATA_SZ		(3)
#define ECG_BUF_CLR     (0x00)

enum ECG_WORD_POS {
    ECG_CMND_POS = 0,
    ECG_DATA_POS = 1
};

extern uint8_t ECG_BUF_I[ECG_BUF_SZ];
extern uint8_t ECG_BUF_O[ECG_BUF_SZ];

typedef struct MAX30003_DATA_t { uint8_t byte[3]; } MAX30003_DATA_t;
typedef uint8_t MAX30003_ADDR_t;

/* ECG_SAMPLE type
 *	struct for storing a bitmapped ECG sample in a 32-bit number
 *	packing and bit order is ignored as the total struct size is 32-bits
 */
typedef struct ECG_SAMPLE {
	uint32_t	tag:3;		/* ETAG data from the ECG_FIFO	*/
	int32_t		data:18;	/* voltage of the sample		*/
	uint32_t	step:11;	/* time step of the sample		*/
} ECG_SAMPLE;


typedef struct MAX30003_MSG {
    uint8_t command;
    MAX30003_DATA_t data;
} MAX30003_MSG;

/* all active high */
typedef struct MAX30003_STATUS_VALS {
    bool ldoff_nl;
    bool ldoff_nh;
    bool ldoff_pl;
    bool ldoff_ph;
    bool pllint;
    bool samp;
    bool rrint;
    bool lonint;
    bool dcloffint;
    bool fstint;
    bool eovf;
    bool eint;
} MAX30003_STATUS_VALS;

typedef struct MAX30003_EN_INT_VALS {
    ENINT_INTBTYPE_VAL     intb_type;
    ENINT_ENPLLINT_VAL     en_pllint;
    ENINT_ENSAMP_VAL       en_samp;
    ENINT_ENRRINT_VAL      en_rrint;
    ENINT_ENLONINT_VAL     en_lonint;
    ENINT_ENDCLOFFINT_VAL  en_dcloffint;
    ENINT_ENFSTINT_VAL     en_fstint;
    ENINT_ENEOVF_VAL       en_eovf;
    ENINT_ENEINT_VAL       en_eint;
} MAX30003_EN_INT_VALS;

typedef struct MAX30003_MNGR_INT_VALS {
	MNGRINT_SAMPIT_VAL		samp_it;
	MNGRINT_CLRSAMP_VAL		clr_samp;
	MNGRINT_CLRRRINT_VAL	clr_rrint;
	MNGRINT_CLRFAST_VAL		clr_fast;
	MNGRINT_EFIT_VAL		efit;
} MAX30003_MNGR_INT_VALS;

typedef struct MAX30003_MNGR_DYN_VALS {
	MNGRDYN_FASTTH_VAL		fast_th;
	MNGRDYN_FAST_VAL		fast;
} MAX30003_MNGR_DYN_VALS;

// TODO verify info data before settling on this
typedef struct MAX30003_INFO_VALS {
	uint8_t				_verification;
	INFO_REV_ID_VAL		rev_id;
	uint8_t				_partid;
	uint16_t			_serialnumber;
} MAX30003_INFO_VALS;

typedef struct MAX30003_CNFG_GEN_VALS {
    CNFGGEN_RBIASN_VAL        rbiasn;
    CNFGGEN_RBIASP_VAL        rbiasp;
    CNFGGEN_RBIASV_VAL        rbiasv;
    CNFGGEN_EN_RBIAS_VAL      en_rbias;
    CNFGGEN_DCLOFF_VTH_VAL    vth;
    CNFGGEN_DCLOFF_IMAG_VAL   imag;
    CNFGGEN_DCLOFF_IPOL_VAL   ipol;
    CNFGGEN_EN_DCLOFF_VAL     en_dcloff;
    CNFGGEN_EN_ECG_VAL        en_ecg;
    CNFGGEN_FMSTR_VAL         fmstr;
    CNFGGEN_EN_ULP_LON_VAL    en_ulp_lon;
} MAX30003_CNFG_GEN_VALS;

typedef struct MAX30003_CNFG_CAL_VALS {
	CNFGCAL_THIGH_VAL	thigh;
	CNFGCAL_FIFTY_VAL	fifty;
	CNFGCAL_FCAL_VAL	fcal;
	CNFGCAL_VMAG_VAL	vmag;
	CNFGCAL_VMODE_VAL	vmode;
	CNFGCAL_EN_VCAL_VAL	en_vcal;
} MAX30003_CNFG_CAL_VALS;

typedef struct MAX30003_CNFG_EMUX_VALS {
	CNFGEMUX_CALN_SEL_VAL	caln_sel;
	CNFGEMUX_CALP_SEL_VAL	calp_sel;
	CNFGEMUX_OPENN_VAL		openn;
	CNFGEMUX_OPENP_VAL		openp;
	CNFGEMUX_POL_VAL		pol;
} MAX30003_CNFG_EMUX_VALS;

typedef struct MAX30003_CNFG_ECG_VALS {
	CNFGECG_DLPF_VAL	dlpf;
	CNFGECG_DHPF_VAL	dhpf;
	CNFGECG_GAIN_VAL	gain;
	CNFGECG_RATE_VAL	rate;
} MAX30003_CNFG_ECG_VALS;

typedef struct MAX30003_CNFG_RTOR1_VALS {
	CNFGRTOR1_PTSF_VAL		ptsf;
	CNFGRTOR1_PAVG_VAL		pavg;
	CNFGRTOR1_EN_RTOR_VAL	en_rtor;
	CNFGRTOR1_GAIN_VAL		gain;
	CNFGRTOR1_WNDW_VAL		wndw;
} MAX30003_CNFG_RTOR1_VALS;

typedef struct MAX30003_CNFG_RTOR2_VALS {
	CNFGRTOR2_RHSF_VAL	rhsf;
	CNFGRTOR2_RAVG_VAL	ravg;
	CNFGRTOR2_HOFF_VAL	hoff;
} MAX30003_CNFG_RTOR2_VALS;

typedef struct MAX30003_FIFO_VALS {
	ECGFIFO_PTAG_VAL	ptag;
	ECGFIFO_ETAG_VAL	etag;
	ECGFIFO_DATA_VAL	data;
} MAX30003_FIFO_VALS;

typedef struct MAX30003_RTOR_VALS {
	RTOR_DATA_VAL	data;
} MAX30003_RTOR_VALS;

/* ASF function pointers for using SAML21 calls without cluttering the MAX30003 namespace */
int32_t (*ecg_spi_xfer)(void * descriptor, const void *buffer);		/* spi_xfer */
void    (*ecg_set_csb_level)(const uint8_t pin, const bool level);	/* gpio_set_pin_level */

/* initialization functions, run before using device */
void ecg_init_spi(void *spi_desc, const void *spi_msg, uint32_t* spi_msg_sz);
void ecg_init_csb(const uint8_t ecg_csb_pin);

// TODO sort/rename here
void ecg_fifo_reset();
void ecg_synch();

/* ecg register access functions */
void ecg_get(void *vals, const MAX30003_REG REG);
void ecg_get_sample(MAX30003_FIFO_VALS *vals);
uint16_t ecg_get_sample_burst(uint32_t *fifo, const uint16_t SIZE); /* returns number of samples recorded */
void ecg_get_status(MAX30003_STATUS_VALS *vals);
void ecg_get_en_int(MAX30003_EN_INT_VALS *vals);
void ecg_get_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals);

//void ecg_set(void *VALS, const uint32_t MASKS, const MAX30003_REG REG); // TODO make generic later
void ecg_set_en_int(const MAX30003_EN_INT_VALS VALS, const MAX30003_EN_INT_MASKS MASKS);
void ecg_set_en_int2(const MAX30003_EN_INT_VALS VALS, const MAX30003_EN_INT_MASKS MASKS);
void ecg_set_mngr_int(const MAX30003_MNGR_INT_VALS VALS, const MAX30003_MNGR_INT_MASKS MASKS);
void ecg_set_mngr_dyn(const MAX30003_MNGR_DYN_VALS VALS, const MAX30003_MNGR_DYN_MASKS MASKS);
void ecg_set_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, const MAX30003_CNFG_GEN_MASKS MASKS);
void ecg_set_cnfg_cal(const MAX30003_CNFG_CAL_VALS VALS, const MAX30003_CNFG_CAL_MASKS MASKS);
void ecg_set_cnfg_emux(const MAX30003_CNFG_EMUX_VALS VALS, const MAX30003_CNFG_EMUX_MASKS MASKS);
void ecg_set_cnfg_ecg(const MAX30003_CNFG_ECG_VALS VALS, const MAX30003_CNFG_ECG_MASKS MASKS);
void ecg_set_cnfg_rtor1(const MAX30003_CNFG_RTOR1_VALS VALS, const MAX30003_CNFG_RTOR1_MASKS MASKS);
void ecg_set_cnfg_rtor2(const MAX30003_CNFG_RTOR2_VALS VALS, const MAX30003_CNFG_RTOR2_MASKS MASKS);

/* internal register functions for shifting and masking values out of words */
void ecg_decode_status(MAX30003_STATUS_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_en_int(MAX30003_EN_INT_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_mngr_int(MAX30003_MNGR_INT_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_mngr_dyn(MAX30003_MNGR_DYN_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_info(MAX30003_INFO_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_cal(MAX30003_CNFG_CAL_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_emux(MAX30003_CNFG_EMUX_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_ecg(MAX30003_CNFG_ECG_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_rtor1(MAX30003_CNFG_RTOR1_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_rtor2(MAX30003_CNFG_RTOR2_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_ecg_fifo(MAX30003_FIFO_VALS *vals, const MAX30003_DATA_t DATA);
void ecg_decode_rtor(MAX30003_RTOR_VALS *vals, const MAX30003_DATA_t DATA);

void ecg_encode_en_int(const MAX30003_EN_INT_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_mngr_int(const MAX30003_MNGR_INT_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_mngr_dyn(const MAX30003_MNGR_DYN_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_cal(const MAX30003_CNFG_CAL_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_emux(const MAX30003_CNFG_EMUX_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_ecg(const MAX30003_CNFG_ECG_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_rtor1(const MAX30003_CNFG_RTOR1_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_rtor2(const MAX30003_CNFG_RTOR2_VALS VALS, MAX30003_DATA_t *data);

/* internal helper functions */
void ecg_clear_ibuf();
void ecg_clear_obuf();
void ecg_clear_iobuf();
void ecg_mask(MAX30003_DATA_t *new_vals, const MAX30003_DATA_t OLD_VALS, const uint32_t MASKS);

uint8_t ecg_read(MAX30003_MSG *msg);
uint8_t ecg_write(MAX30003_MSG *msg);
uint8_t ecg_burst();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003_H */
