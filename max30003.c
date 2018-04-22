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
#include "driver_init.h"

// int32_t (*ecg_spi_xfer)(void * descriptor, const void *buffer);
// void    (*ecg_set_csb)(const uint8_t pin, const bool level);

static void *ECG_SPI_DESC;
static const void *ECG_SPI_MSG;
static uint8_t ECG_CSB_PIN;
/*static uint8_t ECG_BUF[64];*/
uint8_t ECG_BUF_I[ECG_BUF_SZ];
uint8_t ECG_BUF_O[ECG_BUF_SZ];

static MAX30003_MSG ecg_msg;
static const MAX30003_DATA_t NULL_DATA = {
    .byte[0] = 0x00,
    .byte[1] = 0x00,
    .byte[2] = 0x00,
};

void ecg_get_status(MAX30003_STATUS_VALS *vals)
{
    uint8_t bytes;

    /* build the message to send */
    ecg_msg.command = ECG_REG_R(REG_STATUS);
    ecg_msg.data    = NULL_DATA;

    /* transfer over SPI and populate the msg */
    bytes = ecg_read(&ecg_msg);

    if(bytes != MAX30003_DATA_BYTES) {
        /* missing data */
        // TODO error
        } else {
        /* populate the value struct from the data */
        ecg_decode_status(vals, ecg_msg.data);
    }
}

void ecg_decode_status(MAX30003_STATUS_VALS *vals, const MAX30003_DATA_t data)
{
    uint32_t word; /* store the 3x 8-bit data words into a 32-bit number */

    word = 0x00000000;

    /* extract and assign bytes from data word to be endian safe */
    word |= ((uint32_t)(data.byte[2]) << 16);
    word |= ((uint32_t)(data.byte[1]) << 8 );
    word |= ((uint32_t)(data.byte[0]) << 0 );
    
    /* mask in the bits to their respective values as booleans */
    vals->ldoff_nl  = (bool)(word & STATUS_LDOFF_NL);
    vals->ldoff_nh  = (bool)(word & STATUS_LDOFF_NH);
    vals->ldoff_pl  = (bool)(word & STATUS_LDOFF_PL);
    vals->ldoff_ph  = (bool)(word & STATUS_LDOFF_PH);
    vals->pllint    = (bool)(word & STATUS_PLLINT);
    vals->samp      = (bool)(word & STATUS_SAMP);
    vals->rrint     = (bool)(word & STATUS_RRINT);
    vals->lonint    = (bool)(word & STATUS_LONINT);
    vals->dcloffint = (bool)(word & STATUS_DCLOFFINT);
    vals->fstint    = (bool)(word & STATUS_FSTINT);
    vals->eovf      = (bool)(word & STATUS_EOVF);
    vals->eint      = (bool)(word & STATUS_EINT);
}

void ecg_get_en_int(MAX30003_EN_INT_VALS *vals)
{
    MAX30003_MSG msg;
    uint8_t bytes;
    
    msg.command = ECG_REG_R(REG_EN_INT);
    msg.data    = NULL_DATA;

    bytes = ecg_read(&msg);

    if(bytes != MAX30003_DATA_BYTES) {
        /* missing data */
        // TODO error
    } else {
        /* populate the value struct from the data */
        ecg_decode_en_int(vals, msg.data);
    }
}

void ecg_set_en_int(const MAX30003_EN_INT_VALS VALS, const MAX30003_EN_INT_MASKS MASKS)
{
    MAX30003_MSG msg;
    MAX30003_DATA_t newdata;

    msg.command = ECG_REG_R(REG_EN_INT);
    msg.data    = NULL_DATA;

    /* get the 24-bit data word for the current and new configurations */
    ecg_read(&msg);
    ecg_encode_en_int(VALS, &newdata);

    /* modify the current data with the new data */
    msg.data.byte[0] = (msg.data.byte[0] & ~MASKS) | (newdata.byte[0] & MASKS);
    msg.data.byte[1] = (msg.data.byte[1] & ~MASKS) | (newdata.byte[1] & MASKS);
    msg.data.byte[2] = (msg.data.byte[2] & ~MASKS) | (newdata.byte[2] & MASKS);

    /* write out the message */
    ecg_write(&msg);    
}

void ecg_encode_en_int(const MAX30003_EN_INT_VALS VALS, MAX30003_DATA_t *data)
{
    uint32_t word;

    word = 0x00000000;

    word |= VALS.intb_type      << 0;
    word |= VALS.en_pllint      << 8;
    word |= VALS.en_samp        << 9;
    word |= VALS.en_rrint       << 10;
    word |= VALS.en_lonint      << 11;
    word |= VALS.en_dcloffint   << 20;
    word |= VALS.en_fstint      << 21;
    word |= VALS.en_eovf        << 22;
    word |= VALS.en_eint        << 23;

    data->byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
    data->byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
    data->byte[2] = (uint8_t)( (word >> 16  ) & ( 0x00FFFFFF >> 0  ) );
}

void ecg_decode_en_int(MAX30003_EN_INT_VALS *vals, const MAX30003_DATA_t DATA)
{
    uint32_t word; /* store the 3x 8-bit data words into a 32-bit number */

    word = 0x00000000;

    /* extract and assign bytes from data word to be endian safe */
    word |= ((uint32_t)(DATA.byte[2]) << 16);
    word |= ((uint32_t)(DATA.byte[1]) << 8 );
    word |= ((uint32_t)(DATA.byte[0]) << 0 );
    
    /* extract and assign bytes from data word to be endian safe */
    vals->intb_type     = (ENINT_INTBTYPE_VAL   )( (word & ENINT_INTB_TYPE) >> 0 );
    vals->en_pllint     = (ENINT_ENPLLINT_VAL   )( (word & ENINT_EN_PLLINT) >> 8 );
    vals->en_samp       = (ENINT_ENSAMP_VAL     )( (word & ENINT_EN_SAMP  ) >> 9 );
    vals->en_rrint      = (ENINT_ENRRINT_VAL    )( (word & ENINT_EN_RRINT ) >> 10);
    vals->en_lonint     = (ENINT_ENLONINT_VAL   )( (word & ENINT_EN_LONINT) >> 11);
    vals->en_dcloffint  = (ENINT_ENDCLOFFINT_VAL)( (word & ENINT_EN_DCLOFFINT) >> 20);
    vals->en_fstint     = (ENINT_ENFSTINT_VAL   )( (word & ENINT_EN_FSTINT) >> 21);
    vals->en_eovf       = (ENINT_ENEOVF_VAL     )( (word & ENINT_EN_EOVF) >> 22);
    vals->en_eint       = (ENINT_ENEINT_VAL     )( (word & ENINT_EN_EINT) >> 23);
}

void ecg_encode_mngr_int(const MAX30003_MNGR_INT_VALS VALS, MAX30003_DATA_t *data)
{
	uint32_t word;

	word = 0x00000000;

	word |= VALS.samp_it	<< 0;
	word |= VALS.clr_samp	<< 2;
	word |= VALS.clr_rrint	<< 4;
	word |= VALS.clr_fast	<< 6;
	word |= VALS.efit		<< 20;
	
	data->byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
	data->byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
	data->byte[2] = (uint8_t)( (word >> 16  ) & ( 0x00FFFFFF >> 0 ) );
}

void ecg_decode_mngr_int(MAX30003_MNGR_INT_VALS *vals, const MAX30003_DATA_t DATA)
{
	uint32_t word; /* store the 3x 8-bit data words into a 32-bit number */

	word = 0x00000000;

	/* extract and assign bytes from data word to be endian safe */
	word |= ((uint32_t)(DATA.byte[2]) << 16);
	word |= ((uint32_t)(DATA.byte[1]) << 8 );
	word |= ((uint32_t)(DATA.byte[0]) << 0 );
	    
	/* extract and assign bytes from data word to be endian safe */
	vals->samp_it       = (MNGRINT_SAMPIT_VAL   )( (word & MNGRINT_SAMP_IT  ) >> 0 );
	vals->clr_samp      = (MNGRINT_CLRSAMP_VAL  )( (word & MNGRINT_CLR_SAMP ) >> 2 );
	vals->clr_rrint     = (MNGRINT_CLRRRINT_VAL )( (word & MNGRINT_CLR_RRINT) >> 4 );
	vals->clr_fast      = (MNGRINT_CLRFAST_VAL  )( (word & MNGRINT_CLR_FAST ) >> 6 );
	vals->efit          = (MNGRINT_EFIT_VAL     )( (word & MNGRINT_EFIT     ) >> 20);
}

void ecg_decode_mngr_dyn(MAX30003_MNGR_DYN_VALS *vals, const MAX30003_DATA_t DATA)
{
	uint8_t word; /* store the 3x 8-bit data words into a 8-bit number */

	/* extract and assign bytes from data word to be endian safe */
	word = DATA.byte[2];
		
	/* extract and assign bytes from data word to be endian safe */
	vals->fast_th   = (MNGRDYN_FASTTH_VAL)( (word & MNGRDYN_FAST_TH) >> 0 );
	vals->fast		= (MNGRDYN_FAST_VAL  )( (word & MNGRDYN_FAST   ) >> 6 );
}

void ecg_encode_mngr_dyn(const MAX30003_MNGR_DYN_VALS VALS, MAX30003_DATA_t *data)
{
	uint8_t word;

	word = 0x00;

	word |= VALS.fast_th	<< 0;
	word |= VALS.fast		<< 6;
	
	data->byte[0] = 0x00;
	data->byte[1] = 0x00;
	data->byte[2] = word;	
}

void ecg_encode_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, MAX30003_DATA_t *data)
{
    uint32_t word;
     
    word = 0x00000000;

    /* shift values into the 24-bit data word */
    word |= VALS.rbiasn        << 0;
    word |= VALS.rbiasp        << 1;
    word |= VALS.rbiasv        << 2;
    word |= VALS.en_rbias      << 4;
    word |= VALS.vth           << 6;
    word |= VALS.imag          << 8;
    word |= VALS.ipol          << 11;
    word |= VALS.en_dcloff     << 12;
    word |= VALS.en_ecg        << 15;
    word |= VALS.fmstr         << 16;
    word |= VALS.en_ulp_lon    << 20;

    /* extract and assign bytes from data word to be endian safe */
    data.byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
    data.byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
    data.byte[2] = (uint8_t)( (word >> 16 ) & ( 0x00FFFFFF >> 0  ) );
}

void ecg_decode_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals, const MAX30003_DATA_t DATA)
{
	uint32_t word;
	
	word = 0x00000000;
	/* extract and assign bytes from data word to be endian safe */
	word |= ((uint32_t)(DATA.byte[2]) << 16);
	word |= ((uint32_t)(DATA.byte[1]) << 8 );
	word |= ((uint32_t)(DATA.byte[0]) << 0 );
	
	/* shift values from the 24-bit data word into the value struct */
	vals->rbiasn		= (CNFGGEN_RBIASN_VAL     )( (word & CNFGGEN_RBIASN) >> 0 );
	vals->rbiasv		= (CNFGGEN_RBIASV_VAL     )( (word & CNFGGEN_RBIASV) >> 2 );
	vals->en_rbias		= (CNFGGEN_EN_RBIAS_VAL   )( (word & CNFGGEN_EN_RBIAS) >> 4);
	vals->vth			= (CNFGGEN_DCLOFF_VTH_VAL )( (word & CNFGGEN_VTH) >> 6);
	vals->imag			= (CNFGGEN_DCLOFF_IMAG_VAL)( (word & CNFGGEN_IMAG) >> 8);
	vals->ipol			= (CNFGGEN_DCLOFF_IPOL_VAL)( (word & CNFGGEN_IPOL) >> 11);
	vals->en_dcloff		= (CNFGGEN_EN_DCLOFF_VAL  )( (word & CNFGGEN_EN_DCLOFF) >> 12);
	vals->en_ecg		= (CNFGGEN_EN_ECG_VAL     )( (word & CNFGGEN_EN_ECG) >> 15);
	vals->fmstr			= (CNFGGEN_FMSTR_VAL      )( (word & CNFGGEN_FMSTR) >> 16);
	vals->en_ulp_lon	= (CNFGGEN_EN_ULP_LON_VAL )( (word & CNFGGEN_EN_ULP_LON) >> 20);
}

void ecg_decode_cnfg_cal(MAX30003_CNFG_CAL_VALS *vals, const MAX30003_DATA_t DATA)
{
	uint32_t word;
		
	word = 0x00000000;
	/* extract and assign bytes from data word to be endian safe */
	word |= ((uint32_t)(DATA.byte[2]) << 16);
	word |= ((uint32_t)(DATA.byte[1]) << 8 );
	word |= ((uint32_t)(DATA.byte[0]) << 0 );
		
	/* shift values from the 24-bit data word into the value struct */
	vals->thigh		= (CNFGCAL_THIGH_VAL  )( (word & CNFGCAL_THIGH  ) >> 0 );
	vals->fifty		= (CNFGCAL_FIFTY_VAL  )( (word & CNFGCAL_FIFTY  ) >> 10);
	vals->fcal		= (CNFGCAL_FCAL_VAL   )( (word & CNFGCAL_FCAL   ) >> 11);
	vals->vmag		= (CNFGCAL_VMAG_VAL   )( (word & CNFGCAL_VMAG   ) >> 20);
	vals->vmode		= (CNFGCAL_VMODE_VAL  )( (word & CNFGCAL_VMODE  ) >> 21);
	vals->en_vcal	= (CNFGCAL_EN_VCAL_VAL)( (word & CNFGCAL_EN_VCAL) >> 22);
}

void ecg_encode_cnfg_cal(const MAX30003_CNFG_CAL_VALS VALS, MAX30003_DATA_t *data)
{
	uint32_t word;
	
	word = 0x00000000;

	/* shift values into the 24-bit data word */
	word |= VALS.thigh		<< 0;
	word |= VALS.fifty      << 10;
	word |= VALS.fcal		<< 11;
	word |= VALS.vmag		<< 20;
	word |= VALS.vmode      << 21;
	word |= VALS.en_vcal	<< 22;

	/* extract and assign bytes from data word to be endian safe */
	data.byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
	data.byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
	data.byte[2] = (uint8_t)( (word >> 16 ) & ( 0x00FFFFFF >> 0  ) );
}

void ecg_init_spi(void *spi_desc, const void *spi_msg)
{
    ECG_SPI_DESC = spi_desc;
    ECG_SPI_MSG  = spi_msg;
}

void ecg_init_csb(const uint8_t ecg_csb_pin)
{
    ECG_CSB_PIN = ecg_csb_pin;
    ecg_set_csb_level(ECG_CSB_PIN, true);
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
    int i;
    for(i = 0; i < ECG_BUF_SZ; i++) {
        ECG_BUF_I[i] = ECG_BUF_CLR;
        ECG_BUF_O[i] = ECG_BUF_CLR;
    }
}

void ecg_get_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals)
{	
	MAX30003_MSG msg;
	uint8_t		 bytes;
	
    /* create a (read) command by shifting in the read indicator */
    ecg_msg.command = ECG_REG_R(REG_CNFG_GEN);
	msg.data		= NULL_DATA;

	/* perform the spi read action */
    if(ecg_read(&msg) != MAX30003_DATA_BYTES) {
		/* missing data */
		// TODO error
	} else {
		ecg_decode_cnfg_gen(vals, msg.data);
	}
	
}

void ecg_set_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, const MAX30003_CNFG_GEN_MASKS MASKS) 
{
    MAX30003_MSG msg;
    MAX30003_DATA_t newdata;

    msg.command = ECG_REG_R(REG_CNFG_GEN);
    msg.data    = NULL_DATA;

    /* get the 24-bit data word for the current and new configurations */
    ecg_read(&msg);
    ecg_encode_cnfg_gen(VALS, &newdata);

    /* modify the current data with the new data */
    msg.data.byte[0] = (msg.data.byte[0] & ~MASKS) | (newdata.byte[0] & MASKS);
    msg.data.byte[1] = (msg.data.byte[1] & ~MASKS) | (newdata.byte[1] & MASKS);
    msg.data.byte[2] = (msg.data.byte[2] & ~MASKS) | (newdata.byte[2] & MASKS);

    /* write out the message */
    ecg_write(&msg);
}

uint8_t ecg_read(MAX30003_MSG *msg)
{
    uint8_t xfer_bytes;

    /* add the command message to the TX buffer */
    ecg_clear_obuf();
    ECG_BUF_O[ECG_CMND_POS] = (uint8_t)msg->command;

    /* perform spi transfer */
    ecg_set_csb_level(ECG_CSB_PIN, false);
    xfer_bytes = ecg_spi_xfer(&ECG_SPI_DEV_0, ECG_SPI_MSG);
    ecg_set_csb_level(ECG_CSB_PIN, true);

    /* return the bytes transfered, data is also updated */
    return xfer_bytes;
}

uint8_t ecg_write(MAX30003_MSG *msg)
{
    uint8_t xfer_bytes;

    /* add the command and data words to the TX buffer */
    ecg_clear_ibuf();
    ECG_BUF_O[ECG_CMND_POS] = msg->command;
    ECG_BUF_I[ECG_DATA_POS] = ((uint32_t*)msg->data.byte)[0];

    /* perform spi transfer */
    ecg_set_csb_level(ECG_CSB_PIN, false);
    xfer_bytes = ecg_spi_xfer(&ECG_SPI_DEV_0, ECG_SPI_MSG);
    ecg_set_csb_level(ECG_CSB_PIN, true);

    return xfer_bytes;
}
