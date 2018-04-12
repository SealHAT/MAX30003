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

int32_t (*ecg_spi_xfer)(void * descriptor, void *buffer);
void    (*ecg_set_csb)(const uint8_t pin, const bool level);

static void *ECG_SPI_DESC;
static uint8_t ECG_CSB_PIN;
static uint8_t ECG_BUF[64];
static uint8_t ECG_IBUFF[32];
static uint8_t ECG_OBUFF[32];

MAX30003_DATA_t ecg_set_cnfg_gen(MAX30003_CNFG_GEN_VALS vals)
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

    /* extract and assign bytes from data word to be endian safe */
    data.byte[0] = (uint8_t)( (word >> 0  ) & ( 0x00FFFFFF >> 16 ) );
    data.byte[1] = (uint8_t)( (word >> 8  ) & ( 0x00FFFFFF >> 8  ) );
    data.byte[2] = (uint8_t)( (word >> 16 ) & ( 0x00FFFFFF >> 0  ) );

    return data;
}

void ecg_init_spi( int32_t(*spi_xfer_function)(void *, void *), void *ecg_spi_desc)
{

}

void ecg_init_csb( void(*csb_pin_level_function)(const uint8_t , const bool), const uint8_t ecg_csb_pin)
{

}


void ecg_read_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals)
{
    ECG_OBUFF[0] = ((uint8_t)CNFG_GEN << 1) | MAX30003_R_INDICATOR;

    /* TODO spi xfer */
    ecg_set_csb(ECG_CSB_PIN, false);
    ecg_spi_xfer(ECG_SPI_DESC, ECG_BUF);
}

void ecg_write_cnfg_gen(MAX30003_CNFG_GEN_MASKS MASKS, const MAX30003_CNFG_GEN_VALS VALS) {
    MAX30003_MSG msg;
    uint8_t *data;

    data = (uint8_t*)ecg_set_cnfg_gen(VALS).byte;

    msg.command = ((uint8_t)CNFG_GEN << 1) | MAX30003_W_INDICATOR;
    msg.data[0] = data[0];

}

/* example */
void ex() {
    MAX30003_CNFG_GEN_VALS values;

    ecg_read_cnfg_gen(&values);

    values.en_dcloff = MAX30003_CNFG_GEN_EN_DCLOFF_VAL.LOFF_DISABLED;

    ecg_write_cnfg_gen(MAX30003_CNFG_GEN_MASKS.EN_DCLOFF | EN_ECG, values);

}