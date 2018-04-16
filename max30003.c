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
 
#include "max30003.h"

// int32_t (*ecg_spi_xfer)(void * descriptor, const void *buffer);
// void    (*ecg_set_csb)(const uint8_t pin, const bool level);

static void *ECG_SPI_DESC;
static const void *ECG_SPI_MSG;
static uint8_t ECG_CSB_PIN;
/*static uint8_t ECG_BUF[64];*/
uint8_t ECG_BUF_I[ECG_BUF_SZ];
uint8_t ECG_BUF_O[ECG_BUF_SZ];

MAX30003_DATA_t ecg_set_cnfg_gen(MAX30003_CNFG_GEN_VALS vals, const MAX30003_CNFG_GEN_MASKS MASK)
{
    uint32_t word;
    MAX30003_DATA_t data;
     
    word = 0x000000;

    /* shift values into the 24-bit data word */
    word |= vals.rbiasn        << 0;
    word |= vals.rbiasp        << 1;
    word |= vals.rbiasv        << 2;
    word |= vals.en_rbias      << 4;
    word |= vals.vth           << 6;
    word |= vals.imag          << 8;
    word |= vals.ipol          << 11;
    word |= vals.en_dcloff     << 12;
    word |= vals.en_ecg        << 15;
    word |= vals.fmstr         << 16;
    word |= vals.en_ulp_lon    << 20;

    word &= (uint32_t)MASK;

    /* extract and assign bytes from data word to be endian safe */
    data.byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
    data.byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
    data.byte[2] = (uint8_t)( (word >> 16 ) & ( 0x00FFFFFF >> 0  ) );

    return data;
}

void ecg_get_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals, const MAX30003_DATA_t data)
{
	uint32_t word;
	
	word = 0x00000000;
	/* extract and assign bytes from data word to be endian safe */
	word |= ((uint32_t)(data.byte[2]) << 16);
	word |= ((uint32_t)(data.byte[1]) << 8 );
	word |= ((uint32_t)(data.byte[0]) << 0 );
	
	/* shift values from the 24-bit data word into the value struct */
	vals->rbiasn		= (MAX30003_CNFG_GEN_RBIASN_VAL)( (word & CNFGGEN_RBIASN) >> 0 );
	vals->rbiasp		= (MAX30003_CNFG_GEN_RBIASP_VAL)( (word & CNFGGEN_RBIASN) >> 1 );
	vals->rbiasv		= (MAX30003_CNFG_GEN_RBIASV_VAL)( (word & CNFGGEN_RBIASV) >> 2 );
	vals->en_rbias		= (MAX30003_CNFG_GEN_EN_RBIAS_VAL)( (word & CNFGGEN_EN_RBIAS) >> 4);
	vals->vth			= (MAX30003_CNFG_GEN_DCLOFF_VTH_VAL)( (word & CNFGGEN_VTH) >> 6);
	vals->imag			= (MAX30003_CNFG_GEN_DCLOFF_IMAG_VAL)( (word & CNFGGEN_IMAG) >> 8);
	vals->ipol			= (MAX30003_CNFG_GEN_DCLOFF_IPOL_VAL)( (word & CNFGGEN_IPOL) >> 11);
	vals->en_dcloff		= (MAX30003_CNFG_GEN_EN_DCLOFF_VAL)( (word & CNFGGEN_EN_DCLOFF) >> 12);
	vals->en_ecg		= (MAX30003_CNFG_GEN_EN_ECG_VAL)( (word & CNFGGEN_EN_ECG) >> 15);
	vals->fmstr			= (MAX30003_CNFG_GEN_FMSTR_VAL)( (word & CNFGGEN_FMSTR) >> 16);
	vals->en_ulp_lon	= (MAX30003_CNFG_GEN_EN_ULP_LON_VAL)( (word & CNFGGEN_EN_ULP_LON) >> 20);
}

void ecg_init_spi(void *spi_desc, const void *spi_msg)
{
    ECG_SPI_DESC = spi_desc;
    ECG_SPI_MSG  = spi_msg;
}

void ecg_init_csb(const uint8_t ecg_csb_pin)
{
    ECG_CSB_PIN = ecg_csb_pin;
}

void ecg_clear_ibuf()
{
    int i;
    for(i = 0; i < ECG_BUF_SZ; i++) {
        ECG_BUF_I[i] = 0;
    }
}
void ecg_clear_obuf()
{
    int i;
    for(i = 0; i < ECG_BUF_SZ; i++) {
        ECG_BUF_O[i] = 0;
    }
}
void ecg_clear_iobuf()
{
    ecg_clear_ibuf();
    ecg_clear_obuf();
}

void ecg_read_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals)
{
	MAX30003_MSG msg;
	
    /* create a config general (read) command */
	msg.command = (uint8_t)(CNFG_GEN << 1) | MAX30003_R_INDICATOR;
	
    /* send command over spi */
	ecg_clear_obuf();
	ECG_BUF_O[ECG_CMND_POS] = (uint8_t)msg.command;
	
    ecg_set_csb_level(ECG_CSB_PIN, false);
    ecg_spi_xfer(ECG_SPI_DESC, ECG_SPI_MSG);
    ecg_set_csb_level(ECG_CSB_PIN, true);
	
	/* extract data from input buffer */
	msg.data.byte[0] = ECG_BUF_I[0];
	msg.data.byte[1] = ECG_BUF_I[1];
	msg.data.byte[2] = ECG_BUF_I[2];
	
	ecg_get_cnfg_gen(vals, msg.data);
}

void ecg_write_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, const MAX30003_CNFG_GEN_MASKS MASKS) 
{
    MAX30003_MSG msg;
    MAX30003_CNFG_GEN_VALS oldvals;
    uint8_t *data;
    
    /* read the current configuration */
    ecg_read_cnfg_gen(&oldvals);
    /* format and mask out the values to be modified */

    /* arrange the selected values as the ECG data word for sending over SPI */
	msg.command = ((uint8_t)CNFG_GEN << 1) | MAX30003_W_INDICATOR;
    msg.data = ecg_set_cnfg_gen(VALS, MASKS);

    /* mask out the values that are not to be modified */
    
    /* combine the two data buffers to a complete message */
    //data = ((uint32_t*)&data[0]) & ~(uint32_t)MASKS);

    
    msg.data.byte[0] = data[0];

}
