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
#include "driver_init.h"


/* default values for registers */
const MAX30003_CNFG_GEN_VALS CNFGGEN_VALS_DEFAULT = {
/*	.rbiasn     = RBIASN_NOT_CONNECTED,
	.rbiasp     = RBIASP_NOT_CONNECTED,
	.rbiasv     = RBIASV_100_MOHM,
	.en_rbias   = ENRBIAS_DISABLED,
	.vth        = DCLOFFVTH_300_mV,
	.imag       = DCLOFFIMAG_0_nA,
	.ipol       = DCLOFFIPOL_P_UP_N_DOWN,
	.en_dcloff  = ENDCLOFF_DISABLED,*/
	.en_ecg     = ENECG_ENABLED,
/*	.fmstr      = FMSTR_512_HZ,
	.en_ulp_lon = ENULPLON_DISABLED*/
};

const MAX30003_CNFG_ECG_VALS CNFECG_VALS_DEFAULT = {
	.dhpf = DHPF_HALF,
	.dlpf = DLPF_40_HZ,
	.gain = GAIN_20_V,
	.rate = RATE_MIN_SPS
};

const MAX30003_MNGR_INT_VALS MNGR_INT_VALS_DEFAULT = {
	.efit = EFIT_AS_16,
	.clr_samp = CLRSAMP_SELF,
	.samp_it = SAMPIT_EVERY_2ND
};

const MAX30003_CNFG_ECG_MASKS CNFG_ECG_DEFAULT_MASK = CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE;
const MAX30003_CNFG_GEN_MASKS CNFG_GEN_DEFAULT_MASK = CNFGGEN_EN_ECG;
const MAX30003_MNGR_INT_MASKS MNGR_INT_DEFAULT_MASK = MNGRINT_EFIT|MNGRINT_CLR_SAMP|MNGRINT_SAMP_IT;

config_status ecg_change_gain(CNFGECG_GAIN_VAL vals){
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.gain == vals){
		return SAME_CONFIG;
		}else{
		VALS.gain = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.gain == vals){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
	}
	
}


config_status ecg_change_datarate(CNFGECG_RATE_VAL vals){
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.rate == vals){
		return SAME_CONFIG;
		}else{
		VALS.rate = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_RATE));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.rate == vals){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
	}
	
}

config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals){
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&VALS);
	if(VALS.dlpf == vals){
		return SAME_CONFIG;
		}
	else if (vals == DLPF_100_HZ && VALS.rate == RATE_MIN_SPS){
		return CONFIG_FAILURE;
		}
	else if (vals == DLPF_150_HZ && VALS.rate == RATE_MIN_SPS){
		return CONFIG_FAILURE;	
		}
	else if (vals == DLPF_150_HZ && VALS.rate == RATE_MED_SPS){
		return CONFIG_FAILURE;
	}
	else{
		VALS.dlpf = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.dlpf == vals){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
	}
}

config_status ecg_init(){
	int success = 0;
	bool cnfg_gen_sucess    = false;
	bool cnfg_ecg_sucess    = false;
	MAX30003_CNFG_GEN_VALS  cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS  cnfg_ecg_vals;
	ecg_sw_reset();
	delay_ms(100);
	ecg_set_cnfg_gen(CNFGGEN_VALS_DEFAULT,CNFG_GEN_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_cnfg_ecg(CNFECG_VALS_DEFAULT,CNFG_ECG_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_mngr_int(MNGR_INT_VALS_DEFAULT,MNGR_INT_DEFAULT_MASK);
	delay_ms(100);
	ecg_get_cnfg_gen(&cnfg_gen_vals);
	if(cnfg_gen_vals.en_ecg == ENECG_ENABLED){
		success++;
	}
	if(success==1){
		cnfg_gen_sucess = true;
		}else{
		cnfg_gen_sucess = false;
	}
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.dhpf == DHPF_HALF){
		success++;
	}
	if(cnfg_ecg_vals.dlpf == DLPF_40_HZ){
		success++;
	}
	if(cnfg_ecg_vals.gain == GAIN_20_V){
		success++;
	}
	if(cnfg_ecg_vals.rate == RATE_MIN_SPS){
		success++;
	}
	if(success == 5){
		return CONFIG_SUCCESS;
	}else{
		return CONFIG_FAILURE;
	}
	
	
}

config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_ecg == vals){
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

config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_dcloff == vals){
		return SAME_CONFIG;
	}
	else if(vals == _ENDCLOFF_RESERVED1 || vals == _ENDCLOFF_RESERVED2){
		return CONFIG_FAILURE;
	}
	else{
			VALS.en_dcloff = vals;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_DCLOFF);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_dcloff == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}
}

config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.ipol == vals){
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

config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.imag == vals){
		return SAME_CONFIG;
	}
	else if (vals == _DCLOFFIMAG_RESERVED1 || vals == _DCLOFFIMAG_RESERVED2){
		return CONFIG_FAILURE;
	}
	else{
				VALS.imag = vals;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
	}	
}

config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.vth == vals){
		return SAME_CONFIG;
	}else{
				VALS.vth = vals;
				ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
				ecg_get_cnfg_gen(&VALS);
				if(VALS.vth == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
	}	
}

config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.en_rbias == vals){
		return SAME_CONFIG;
	}else if (vals == _ENRBIAS_RESERVED1 || vals == _ENRBIAS_RESERVED2){
		return CONFIG_FAILURE;
	}
	else{
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
	

config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasv == vals){
		return SAME_CONFIG;
	}else if (vals == _RBIASV_RESERVED){
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


config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasp == vals){
		return SAME_CONFIG;
	}else{
			VALS.rbiasp = vals;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASP);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasp == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}
}
	
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals){
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&VALS);
	if(VALS.rbiasn == vals){
		return SAME_CONFIG;
	}else{
			VALS.rbiasn = vals;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASN);
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasn == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	}	
}

config_status ecg_en_dcloff_int(int_pin pin, ENINT_ENDCLOFFINT_VAL vals, ENINT_INTBTYPE_VAL type){
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
	case INT_PIN_1:
	ecg_get_en_int(&VALS);
	if(VALS.en_dcloffint == vals && VALS.intb_type == type){
		return SAME_CONFIG;
	}else if(VALS.en_dcloffint == vals){
		VALS.intb_type = type;
		ecg_set_en_int(VALS, ENINT_INTB_TYPE);
		ecg_get_en_int(&VALS);
		if(VALS.intb_type == type){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}		

	}else if(VALS.intb_type == type){
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
	if(VALS.en_dcloffint == vals && VALS.intb_type == type){
		return SAME_CONFIG;
		}else if(VALS.en_dcloffint == vals){
		VALS.intb_type = type;
		ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}

		}else if(VALS.intb_type == type){
		VALS.en_dcloffint = vals;
		ecg_set_en_int2(VALS, ENINT_EN_DCLOFFINT);
		ecg_get_en_int2(&VALS);
		if(VALS.en_dcloffint == vals){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
		}else{
		VALS.en_dcloffint = vals;
		VALS.intb_type = type;
		ecg_set_en_int2(VALS,ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE);
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type && VALS.en_dcloffint == vals){
			return CONFIG_SUCCESS;

			}else{
			return CONFIG_FAILURE;
		}
	}
	break;	
}
	
}

config_status ecg_en_lon_int(int_pin pin, ENINT_ENLONINT_VAL vals, ENINT_INTBTYPE_VAL type){
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
	    ecg_get_en_int(&VALS);
		if(VALS.en_lonint == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_lonint == vals){
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
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
			if(VALS.intb_type == type && VALS.en_lonint == vals){
				return CONFIG_SUCCESS;

				}else{
				return CONFIG_FAILURE;
			}
		}
		break;
		case INT_PIN_2:
	    ecg_get_en_int2(&VALS);
		if(VALS.en_lonint == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_lonint == vals){
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
			VALS.en_lonint = vals;
			ecg_set_en_int2(VALS, ENINT_EN_LONINT);
			ecg_get_en_int2(&VALS);
			if(VALS.en_lonint == vals){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}
			}else{
			VALS.en_lonint = vals;
			VALS.intb_type = type;
			ecg_set_en_int2(VALS,ENINT_EN_LONINT|ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type && VALS.en_lonint == vals){
				return CONFIG_SUCCESS;

				}else{
				return CONFIG_FAILURE;
			}
		}
		break;
	}	
}

config_status ecg_en_evof_int(int_pin pin, ENINT_ENEOVF_VAL vals, ENINT_INTBTYPE_VAL type){
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_eovf == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_eovf == vals){
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
			VALS.en_eovf = vals;
			ecg_set_en_int(VALS, ENINT_EN_EOVF);
			ecg_get_en_int(&VALS);
			if(VALS.en_eovf == vals){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}
			
			}else{
			VALS.en_eovf = vals;
			VALS.intb_type = type;
			ecg_set_en_int(VALS,ENINT_EN_EOVF|ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type && VALS.en_eovf == vals){
				return CONFIG_SUCCESS;

				}else{
				return CONFIG_FAILURE;
			}
		}
		break;
		case INT_PIN_2:
		ecg_get_en_int2(&VALS);
		if(VALS.en_eovf == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_eovf == vals){
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
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
}

config_status ecg_fifo_thres(MNGRINT_EFIT_VAL vals){
	MAX30003_MNGR_INT_VALS VALS;
	ecg_get_mngr_int(&VALS);
	if(VALS.efit == vals){
		return SAME_CONFIG;
	}else{
		VALS.efit = vals;
		ecg_set_mngr_int(VALS, MNGRINT_EFIT);
		ecg_get_mngr_int(&VALS);
		if(VALS.efit == vals){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
	}
}

config_status ecg_en_fifo_int(int_pin pin, ENINT_ENEINT_VAL vals, ENINT_INTBTYPE_VAL type){
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_eint == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_eint == vals){
			VALS.intb_type = type;
			ecg_set_en_int(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
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
		if(VALS.en_eint == vals && VALS.intb_type == type){
			return SAME_CONFIG;
			}else if(VALS.en_eint == vals){
			VALS.intb_type = type;
			ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
			ecg_get_en_int2(&VALS);
			if(VALS.intb_type == type){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}

			}else if(VALS.intb_type == type){
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
}

config_status ecg_en_int(int_pin pin, MAX30003_EN_INT_VALS vals){
	MAX30003_EN_INT_VALS VALS;
	switch(pin){
		case INT_PIN_1:
		ecg_get_en_int(&VALS);
		if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type &&VALS.en_samp == vals.en_samp){
			return SAME_CONFIG;
		}else{
			VALS = vals;
			ecg_set_en_int(VALS,ENINT_EN_EINT|ENINT_EN_EOVF|ENINT_EN_LONINT|ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE|ENINT_EN_SAMP);
			ecg_get_en_int(&VALS);
			if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type &&VALS.en_samp == vals.en_samp){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
	       }
		break;
		case INT_PIN_2:
		ecg_get_en_int2(&VALS);
		if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type &&VALS.en_samp == vals.en_samp){
			return SAME_CONFIG;
		}else{
			VALS = vals;
			ecg_set_en_int2(VALS,ENINT_EN_EINT|ENINT_EN_EOVF|ENINT_EN_LONINT|ENINT_EN_DCLOFFINT|ENINT_INTB_TYPE|ENINT_EN_SAMP);
			ecg_get_en_int2(&VALS);
			if(VALS.en_dcloffint == vals.en_dcloffint && VALS.en_eint == vals.en_eint && VALS.en_eovf == vals.en_eovf && VALS.en_lonint == vals.en_lonint && VALS.intb_type == vals.intb_type&&VALS.en_samp == vals.en_samp){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
		}
	
  }
}

uint16_t ecg_sampling_process(uint16_t initial_point, signed int voltage[], uint16_t SIZE){
	MAX30003_FIFO_VALS FIFO[SIZE];// FIFO array to store the data
	MAX30003_CNFG_GEN_VALS check_switch;// value used to check the condition of switch
	config_status t;
	uint16_t i; 
	uint16_t n = initial_point;
	int32_t tem; // temporary variable to store the FIFO data, can be removed 
	int8_t situation = 0;//check if ecg is not functional;
	uint16_t step;// time step
	ecg_get_cnfg_gen(&check_switch);
	/*if ecg switch is not enabled, then enable it*/
	if(check_switch.en_ecg == ENECG_DISABLED){
		t = ecg_switch(ENECG_ENABLED);
	}
	/*clear the fifo before sampling*/
	ecg_fifo_reset();
		for(i = 0;i<SIZE;i++){
		  if(situation<5){//ecg functional if no many situations happened
			ecg_get_sample(&FIFO[i]);
				switch(FIFO[i].etag){
					//based on the data sheet 
					case ETAG_VALID:
					case ETAG_VALID_EOF:
						tem = FIFO[i].data<<14;
						voltage[n] = tem>>14;
						step++;
						n++;
						situation = 0;
						break;
				   case _ETAG_RESERVED1:
				   case _ETAG_RESERVED2:
				   case ETAG_FAST:
				   case ETAG_FAST_EOF:
						situation++;
						i--;
						break;
				   case ETAG_FIFO_EMPTY:
						situation++;
						i--;
						delay_ms(10);
						break;
					/*if ecg func well, there is not supposed to happen overflow at this point, if happened, ecg broke or chip broke*/
				   case ETAG_FIFO_OVERFLOW:
				        situation=5;
						n = initial_point;
						i = 0;
						step = 0;
						ecg_fifo_reset();
						break;						
			}
			
		}else{
			return step;// if ecg broke, return the current step
		}
	
	}
	return step;// step should equal to Size if ecg works
}

