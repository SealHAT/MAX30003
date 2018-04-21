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

void ecg_set_en_int(MAX30003_EN_INT_VALS VALS, const MAX30003_EN_INT_MASKS MASKS)
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

void ecg_decode_en_int(MAX30003_EN_INT_VALS *vals, const MAX30003_DATA_t data)
{
    uint32_t word; /* store the 3x 8-bit data words into a 32-bit number */

    word = 0x00000000;

    /* extract and assign bytes from data word to be endian safe */
    word |= ((uint32_t)(data.byte[2]) << 16);
    word |= ((uint32_t)(data.byte[1]) << 8 );
    word |= ((uint32_t)(data.byte[0]) << 0 );
    
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


MAX30003_DATA_t ecg_set_cnfg_gen(MAX30003_CNFG_GEN_VALS vals, const MAX30003_CNFG_GEN_MASKS MASK)
{
    uint32_t word;
    MAX30003_DATA_t data;
     
    word = 0x00000000;

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
	vals->rbiasp		= (MAX30003_CNFG_GEN_RBIASP_VAL)( (word & CNFGGEN_RBIASP) >> 1 );
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

void ecg_read_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals)
{	
    /* create a (read) command by shifting in the read indicator */
    ecg_msg.command = ECG_REG_R(REG_CNFG_GEN);

	/* perform the spi read action */
    ecg_read(&ecg_msg);
	
	/* extract data from input buffer */
	ecg_msg.data.byte[0] = ECG_BUF_I[0];
	ecg_msg.data.byte[1] = ECG_BUF_I[1];
	ecg_msg.data.byte[2] = ECG_BUF_I[2];
	
	ecg_get_cnfg_gen(vals, ecg_msg.data);
}

void ecg_write_cnfg_gen(const MAX30003_CNFG_GEN_VALS VALS, const MAX30003_CNFG_GEN_MASKS MASKS) 
{
    MAX30003_CNFG_GEN_VALS oldvals;
    uint8_t *data;
    
    /* read the current configuration */
    ecg_read_cnfg_gen(&oldvals);

    /* format and mask out the values to be modified */


    /* arrange the selected values as the ECG data word for sending over SPI */
	ecg_msg.command = ((uint8_t)REG_CNFG_GEN << 1) | MAX30003_W_INDICATOR;
    ecg_msg.data = ecg_set_cnfg_gen(VALS, MASKS);

    /* mask out the values that are not to be modified */
    
    /* combine the two data buffers to a complete message */
    //data = ((uint32_t*)&data[0]) & ~(uint32_t)MASKS);

    
    ecg_msg.data.byte[0] = data[0];

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

//uint8_t ecg_xfer(MAX30003_MSG *msg)
//{
    //uint8_t xfer_bytes;
//
    ///* add the command and data words to the TX buffer */
    //ecg_clear_iobuf();
    //ECG_BUF_O[ECG_CMND_POS] = (uint8_t)msg->command;
    //ECG_BUF_I[0] = msg->data[0];
    //ECG_BUF_I[1] = msg->data[1];
    //ECG_BUF_I[2] = msg->data[2];
//
    ///* perform spi transfer */
    //ecg_set_csb_level(ECG_CSB_PIN, false);
    //xfer_bytes = ecg_spi_xfer(&ECG_SPI_DEV_0, ECG_SPI_MSG);
    //ecg_set_csb_level(ECG_CSB_PIN, true);
//
    //return xfer_bytes;
//}