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
    if (spi_m_sync_set_mode(&SPI_MOD, SPI_MODE_0)) {
        return ERR_NOT_INITIALIZED;
    }
    spi_m_sync_enable(&SPI_MOD);
    gpio_set_pin_level(MOD_CS,true);
    
    ecg_spi_msg.size  = ECG_BUF_SZ;
    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
    
    return ERR_NONE;
}    


/* default values for registers */
const MAX30003_CNFG_GEN_VALS CNFGGEN_VALS_DEFAULT = {
	.en_ecg     = ENECG_DISABLED,
};

const MAX30003_CNFG_ECG_VALS CNFECG_VALS_DEFAULT = {
	.dhpf = DHPF_HALF,
	.dlpf = DLPF_40_HZ,
	.gain = GAIN_40_V,
	.rate = RATE_MIN_SPS
};

const MAX30003_MNGR_INT_VALS MNGR_INT_VALS_DEFAULT = {
	.efit = EFIT_AS_16,
};

const MAX30003_CNFG_ECG_MASKS CNFG_ECG_DEFAULT_MASK = CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE;
const MAX30003_CNFG_GEN_MASKS CNFG_GEN_DEFAULT_MASK = CNFGGEN_EN_ECG;
const MAX30003_MNGR_INT_MASKS MNGR_INT_DEFAULT_MASK = MNGRINT_EFIT;

config_status ecg_change_gain(CNFGECG_GAIN_VAL vals)
{
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.gain == vals)
	{
		return SAME_CONFIG;
	}else{
		VALS.gain = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.gain == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
	
}

config_status ecg_change_datarate(CNFGECG_RATE_VAL vals)
{
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.rate == vals)
	{
		return SAME_CONFIG;
	}else{
		VALS.rate = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_RATE));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.rate == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
	
}

config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals)
{
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.dlpf == vals)
	{
		return SAME_CONFIG;
	}
	else if (vals == DLPF_100_HZ && VALS.rate == RATE_MIN_SPS)
	{
		return CONFIG_FAILURE;
	}
	else if (vals == DLPF_150_HZ && VALS.rate == RATE_MIN_SPS)
	{
		return CONFIG_FAILURE;	
	}
	else if (vals == DLPF_150_HZ && VALS.rate == RATE_MED_SPS)
	{
		return CONFIG_FAILURE;
	}
	else{
		VALS.dlpf = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.dlpf == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
}

config_status ecg_init()
{
    MAX30003_VALS   old_vals;
    MAX30003_VALS   new_vals;
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    
    new_vals.cnfg_gen.rbiasn       = RBIASN_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasp       = RBIASP_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasv       = RBIASV_100_MOHM;
    new_vals.cnfg_gen.en_rbias     = ENRBIAS_DISABLED;
    new_vals.cnfg_gen.en_dcloff    = ENDCLOFF_DISABLED;
    new_vals.cnfg_gen.en_ecg       = ENECG_ENABLED;
    new_vals.cnfg_gen.fmstr        = FMSTR_512_HZ;
    
    ecg_set_cnfg_gen(new_vals.cnfg_gen, CNFGGEN_DEFAULT_MASK);
    ecg_get_cnfg_gen(&old_vals.cnfg_gen);
    
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
config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_ecg == vals)
	{
		return SAME_CONFIG;
	}else{
		VALS.en_ecg = vals;
		ecg_set_cnfg_gen(VALS,CNFGGEN_EN_ECG);
		ecg_get_cnfg_gen(&VALS);
		if(VALS.en_ecg == vals){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
		
	}
	
}

config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_dcloff == vals)
	{
		return SAME_CONFIG;
	}
	else if(vals == _ENDCLOFF_RESERVED1 || vals == _ENDCLOFF_RESERVED2)
	{
		return CONFIG_FAILURE;
	}else{
		VALS.en_dcloff = vals;
		ecg_set_cnfg_gen(VALS,CNFGGEN_EN_DCLOFF);
		ecg_get_cnfg_gen(&VALS);
		if(VALS.en_dcloff == vals)
		{
			return CONFIG_SUCCESS;
		}else{
				return CONFIG_FAILURE;
		}
	}
}

config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.ipol == vals)
	{
		return SAME_CONFIG;
	}else{
		VALS.ipol = vals;
		ecg_set_cnfg_gen(VALS,CNFGGEN_IPOL);
		ecg_get_cnfg_gen(&VALS);
		if(VALS.ipol == vals){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
}

config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.imag == vals)
	{
		return SAME_CONFIG;
	}
	else if (vals == _DCLOFFIMAG_RESERVED1 || vals == _DCLOFFIMAG_RESERVED2)
	{
		return CONFIG_FAILURE;
	}
	else{
		VALS.imag = vals;
		ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
		ecg_get_cnfg_gen(&VALS);
		if(VALS.imag == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}	
}

config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.vth == vals)
	{
		return SAME_CONFIG;
	}else{
			VALS.vth = vals;
			ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.vth == vals)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}	
}

config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_rbias == vals)
	{
		return SAME_CONFIG;
	}else if (vals == _ENRBIAS_RESERVED1 || vals == _ENRBIAS_RESERVED2)
	{
		return CONFIG_FAILURE;
	}else{
			VALS.en_rbias = vals;
			ecg_set_cnfg_gen(VALS, CNFGGEN_EN_RBIAS);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_rbias == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}	
}
	

config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasv == vals)
	{
		return SAME_CONFIG;
	}else if (vals == _RBIASV_RESERVED)
	{
		return CONFIG_FAILURE;
	}
	else{
			VALS.rbiasv = vals;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASV);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasv == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}
}


config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasp == vals)
	{
		return SAME_CONFIG;
	}else{
			VALS.rbiasp = vals;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASP);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasp == vals)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}
}
	
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals)
{
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasn == vals)
	{
		return SAME_CONFIG;
	}else{
			VALS.rbiasn = vals;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASN);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasn == vals)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}	
}

config_status ecg_en_dcloff_int(int_pin pin, ENINT_ENDCLOFFINT_VAL vals, ENINT_INTBTYPE_VAL type)
{
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
	case INT_PIN_1:
	ecg_get_en_int(&VALS);
	if(VALS.en_dcloffint == vals && VALS.intb_type == type)
	{
		return SAME_CONFIG;
	}else if(VALS.en_dcloffint == vals)
	{
		VALS.intb_type = type;
		ecg_set_en_int(VALS, ENINT_INTB_TYPE);
		ecg_get_en_int(&VALS);
		if(VALS.intb_type == type){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}		

	}else if(VALS.intb_type == type)
	{
		VALS.en_dcloffint = vals;
		ecg_set_en_int(VALS, ENINT_EN_DCLOFFINT);
		ecg_get_en_int(&VALS);
		if(VALS.en_dcloffint == vals){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}else{
		VALS.en_dcloffint = vals;
		VALS.intb_type = type;
		ecg_set_en_int(VALS,ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE);
		ecg_get_en_int(&VALS);
		if(VALS.intb_type == type && VALS.en_dcloffint == vals){
			return CONFIG_SUCCESS;

		}else{
			return CONFIG_FAILURE;
		}
	}
	break;
	case INT_PIN_2:
	ecg_get_en_int2(&VALS);
	if(VALS.en_dcloffint == vals && VALS.intb_type == type)
	{
		return SAME_CONFIG;
	}else if(VALS.en_dcloffint == vals)
	{
		VALS.intb_type = type;
		ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}

	}else if(VALS.intb_type == type)
	{
		VALS.en_dcloffint = vals;
		ecg_set_en_int2(VALS, ENINT_EN_DCLOFFINT);
		ecg_get_en_int2(&VALS);
		if(VALS.en_dcloffint == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}else{
		VALS.en_dcloffint = vals;
		VALS.intb_type = type;
		ecg_set_en_int2(VALS,ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE);
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type && VALS.en_dcloffint == vals)
		{
			return CONFIG_SUCCESS;

		}else{
			return CONFIG_FAILURE;
		}
	}
	break;	
  }
	return CONFIG_FAILURE;
	
}

config_status ecg_en_lon_int(int_pin pin, ENINT_ENLONINT_VAL vals, ENINT_INTBTYPE_VAL type)
{
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
	    ecg_get_en_int(&VALS);
		if(VALS.en_lonint == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_lonint == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}

		}else if(VALS.intb_type == type)
		{
			VALS.en_lonint = vals;
			ecg_set_en_int(VALS, ENINT_EN_LONINT);
			ecg_get_en_int(&VALS);
			if(VALS.en_lonint == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
		}else{
			VALS.en_lonint = vals;
			VALS.intb_type = type;
			ecg_set_en_int(VALS,ENINT_EN_LONINT|ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type && VALS.en_lonint == vals)
			{
				return CONFIG_SUCCESS;

			}else{
				return CONFIG_FAILURE;
			}
		}
		break;
		case INT_PIN_2:
	    ecg_get_en_int2(&VALS);
		if(VALS.en_lonint == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_lonint == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}

		}else if(VALS.intb_type == type)
		{
			VALS.en_lonint = vals;
			ecg_set_en_int2(VALS, ENINT_EN_LONINT);
			ecg_get_en_int2(&VALS);
			if(VALS.en_lonint == vals)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
		}else{
			VALS.en_lonint = vals;
			VALS.intb_type = type;
			ecg_set_en_int2(VALS,ENINT_EN_LONINT|ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type && VALS.en_lonint == vals)
			{
				return CONFIG_SUCCESS;

			}else{
				return CONFIG_FAILURE;
			}
		}
		break;
	}
	return CONFIG_FAILURE;	
}

config_status ecg_en_evof_int(int_pin pin, ENINT_ENEOVF_VAL vals, ENINT_INTBTYPE_VAL type)
{
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_eovf == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_eovf == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}

		}else if(VALS.intb_type == type)
		{
			VALS.en_eovf = vals;
			ecg_set_en_int(VALS, ENINT_EN_EOVF);
			ecg_get_en_int(&VALS);
			if(VALS.en_eovf == vals)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			
		}else{
			VALS.en_eovf = vals;
			VALS.intb_type = type;
			ecg_set_en_int(VALS,ENINT_EN_EOVF|ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type && VALS.en_eovf == vals)
			{
				return CONFIG_SUCCESS;

			}else{
				return CONFIG_FAILURE;
			}
		}
		break;
		case INT_PIN_2:
		ecg_get_en_int2(&VALS);
		if(VALS.en_eovf == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_eovf == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}

		}else if(VALS.intb_type == type)
		{
			VALS.en_eovf = vals;
			ecg_set_en_int2(VALS, ENINT_EN_EOVF);
			ecg_get_en_int2(&VALS);
			if(VALS.en_eovf == vals){
					return CONFIG_SUCCESS;
				}else{
					return CONFIG_FAILURE;
			    }
		}else{
			VALS.en_eovf = vals;
			VALS.intb_type = type;
			ecg_set_en_int2(VALS,ENINT_EN_EOVF|ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type && VALS.en_eovf == vals){
					return CONFIG_SUCCESS;
				}else{
					return CONFIG_FAILURE;
			    }
		}
		break;
	}
	return CONFIG_FAILURE;	
}

config_status ecg_fifo_thres(MNGRINT_EFIT_VAL vals)
{
	MAX30003_MNGR_INT_VALS VALS;
	ecg_get_mngr_int(&VALS);
	if(VALS.efit == vals)
	{
		return SAME_CONFIG;
	}else{
		VALS.efit = vals;
		ecg_set_mngr_int(VALS, MNGRINT_EFIT);
		ecg_get_mngr_int(&VALS);
		if(VALS.efit == vals)
		{
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
}

config_status ecg_en_fifo_int(int_pin pin, ENINT_ENEINT_VAL vals, ENINT_INTBTYPE_VAL type)
{
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_eint == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_eint == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			    }

		}else if(VALS.intb_type == type)
		{
			VALS.en_eint = vals;
			ecg_set_en_int(VALS, ENINT_EN_EINT);
			ecg_get_en_int(&VALS);
			if(VALS.en_eint == vals){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			    }
			
		}else{
			VALS.en_eint = vals;
			VALS.intb_type = type;
			ecg_set_en_int(VALS,ENINT_EN_EINT|ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type && VALS.en_eint == vals){
				return CONFIG_SUCCESS;

				}else{
				return CONFIG_FAILURE;
			}
		}
		break;
		case INT_PIN_2:
		ecg_get_en_int2(&VALS);
		if(VALS.en_eint == vals && VALS.intb_type == type)
		{
			return SAME_CONFIG;
		}else if(VALS.en_eint == vals)
		{
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			    }

		}else if(VALS.intb_type == type)
		{
			VALS.en_eint = vals;
			ecg_set_en_int2(VALS, ENINT_EN_EINT);
			ecg_get_en_int2(&VALS);
			if(VALS.en_eint == vals){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			    }
		}else{
			VALS.en_eint = vals;
			VALS.intb_type = type;
			ecg_set_en_int2(VALS,ENINT_EN_EINT|ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type && VALS.en_eint == vals){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			    }
		}
		break;
	}
	return CONFIG_FAILURE;	
}

config_status ecg_en_int(int_pin pin, MAX30003_EN_INT_VALS vals)
{
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type && VALS.en_samp == vals.en_samp && VALS.en_rrint == vals.en_rrint && VALS.en_pllint == vals.en_pllint && VALS.en_fstint == vals.en_fstint)
		{
			return SAME_CONFIG;
		}else{
			VALS = vals;
			ecg_set_en_int(VALS,ENINT_EN_EINT|ENINT_EN_EOVF|ENINT_EN_LONINT|ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE|ENINT_EN_SAMP|ENINT_EN_FSTINT|ENINT_EN_RRINT|ENINT_EN_PLLINT);
			ecg_get_en_int(&VALS);
			if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type && VALS.en_samp == vals.en_samp && VALS.en_rrint == vals.en_rrint && VALS.en_pllint == vals.en_pllint && VALS.en_fstint == vals.en_fstint)
			{
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	       }
		break;
		case INT_PIN_2:
		ecg_get_en_int2(&VALS);
		if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type && VALS.en_samp == vals.en_samp && VALS.en_rrint == vals.en_rrint && VALS.en_pllint == vals.en_pllint && VALS.en_fstint == vals.en_fstint)
		{
			return SAME_CONFIG;
		}else{
			VALS = vals;
			ecg_set_en_int2(VALS,ENINT_EN_EINT|ENINT_EN_EOVF|ENINT_EN_LONINT|ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE|ENINT_EN_SAMP|ENINT_EN_FSTINT|ENINT_EN_RRINT|ENINT_EN_PLLINT);
			ecg_get_en_int2(&VALS);
			if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type && VALS.en_samp == vals.en_samp && VALS.en_rrint == vals.en_rrint && VALS.en_pllint == vals.en_pllint && VALS.en_fstint == vals.en_fstint){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
		}
	
	}
	return CONFIG_FAILURE;
}

uint16_t ecg_sampling_process(uint16_t initial_point, ECG_SAMPLE_t Storage[], uint16_t Desired_Sample_Size)
{
	MAX30003_FIFO_VALS FIFO[Desired_Sample_Size];// FIFO array to store the data
	MAX30003_CNFG_GEN_VALS check_switch;// value used to check the condition of switch
	config_status t = CONFIG_FAILURE;// config_status of the switch
	uint16_t step = 0;// for loop parameter,considered time-step per interrupt
	uint16_t n = initial_point;
    int32_t tem = 0; // temporary variable to store the FIFO data 
	uint16_t Number_Of_Valid_Data = 0;// Number of valid data of total sample period
	ecg_get_cnfg_gen(&check_switch);
	/*if ecg switch is not enabled, then enable it*/
	if(check_switch.en_ecg == ENECG_DISABLED)
	{
		t = ecg_switch(ENECG_ENABLED);
	}
		for(step = 0;step<Desired_Sample_Size;step++)
		{
			ecg_get_sample(&FIFO[step]);
				switch(FIFO[step].etag)
				{
					//based on the data sheet 
					case ETAG_VALID:
					case ETAG_VALID_EOF:
				    case _ETAG_RESERVED1:
				    case _ETAG_RESERVED2:
				    case ETAG_FAST:
				    case ETAG_FAST_EOF:
						if((FIFO[step].data & 0x00020000)==0x00020000){
							tem = FIFO[step].data | 0xFFFE0000;
						}else{
							tem = FIFO[step].data;
						}
						Storage[n].data=tem;
						Storage[n].tag = FIFO[step].etag;
						Storage[n].step = step+1;
						Number_Of_Valid_Data++;
						n++;
						break;
				  /*time step valid but data invalid, data abandoned but time increment, based on data sheet*/

				  /*Discard the sample without incrementing the time base, suspend read back operations, based on datasheet*/
				   case ETAG_FIFO_EMPTY:
						if(step>0){
							step--;
						}
						delay_ms(10);
						break;
					/*if ecg func well, there is not supposed to happen overflow, if happened, ecg broke or chip broke*/
				   case ETAG_FIFO_OVERFLOW:
					// if data overflow, clear the fifo and break the func				
						ecg_fifo_reset();
						return Number_Of_Valid_Data;	 
						break;						
			    }
			
	
	}
	return Number_Of_Valid_Data;// step should equal to Size if ecg works
}

