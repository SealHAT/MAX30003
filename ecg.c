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
 
#include "ecg.h"
#include <string.h>

int32_t ecg_spi_init()
{
    /* grab the SPI descriptor */
    if (spi_m_sync_set_mode(&SPI_MOD, SPI_MODE_0)) {
        return ERR_NOT_INITIALIZED;
    }
    spi_m_sync_enable(&SPI_MOD);
    gpio_set_pin_level(MOD_CS,true);
    
    /* set up the SPI message buffer */
    ecg_spi_msg.size  = ECG_BUF_SZ;
    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
    
    return ERR_NONE;
}    

config_status ecg_init()
{
    MAX30003_VALS   old_vals;
    MAX30003_VALS   new_vals;
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    
    /* choose default values for CNFG_GEN register */
    new_vals.cnfg_gen.rbiasn       = RBIASN_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasp       = RBIASP_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasv       = RBIASV_100_MOHM;
    new_vals.cnfg_gen.en_rbias     = ENRBIAS_DISABLED;
    new_vals.cnfg_gen.en_dcloff    = ENDCLOFF_DISABLED;
    new_vals.cnfg_gen.en_ecg       = ENECG_ENABLED;
    new_vals.cnfg_gen.fmstr        = FMSTR_512_HZ;
    
    /* set the new values and confirm they have changed */
    ecg_set_cnfg_gen(new_vals.cnfg_gen, CNFGGEN_DEFAULT_MASK);
    ecg_get_cnfg_gen(&old_vals.cnfg_gen);
    
    /* verify the ECG has been enabled */
    if(new_vals.cnfg_gen.en_ecg != old_vals.cnfg_gen.en_ecg) {
        return CONFIG_FAILURE;
    }
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.cnfg_ecg.dlpf = DLPF_40_HZ;
    new_vals.cnfg_ecg.dhpf = DHPF_HALF;
    new_vals.cnfg_ecg.gain = GAIN_20_V;
    new_vals.cnfg_ecg.rate = RATE_MIN_SPS;
    
    ecg_set_cnfg_ecg(new_vals.cnfg_ecg, CNFGECG_DEFAULT_MASK);
    ecg_get_cnfg_ecg(&old_vals.cnfg_ecg);
    
    if( new_vals.cnfg_ecg.dhpf != old_vals.cnfg_ecg.dhpf &&
        new_vals.cnfg_ecg.dlpf != old_vals.cnfg_ecg.dlpf &&
        new_vals.cnfg_ecg.gain != old_vals.cnfg_ecg.gain &&
        new_vals.cnfg_ecg.rate != old_vals.cnfg_ecg.rate ) {
            return CONFIG_FAILURE;
        }
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.mngr_int.efit = EFIT_AS_24;
    
    ecg_set_mngr_int(new_vals.mngr_int, MNGRINT_DEFAULT_MASK);
    ecg_get_mngr_int(&old_vals.mngr_int);
    
    if ( new_vals.mngr_int.efit != old_vals.mngr_int.efit ) {
        return CONFIG_FAILURE;
    }
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.en_int.en_eint    = ENINT_ENABLED;
    new_vals.en_int.intb_type  = INTBTYPE_NMOS_WITH_PU;
    
    ecg_set_en_int(new_vals.en_int, ENINT1_DEFUALT_MASK);
    ecg_set_en_int2(new_vals.en_int, ENINT1_DEFUALT_MASK);
    ecg_get_en_int(&old_vals.en_int);
    
    if ( new_vals.en_int.en_eint   != old_vals.en_int.en_eint &&
         new_vals.en_int.intb_type != old_vals.en_int.intb_type ) {
             return CONFIG_FAILURE;
    }
    
    return CONFIG_SUCCESS;
}