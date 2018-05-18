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
#include "max30003test.h"
#include "driver_init.h"

config_status ecg_change_gain(CNFGECG_GAIN_VAL vals){
	MAX30003_CNFG_ECG_VALS  originalvals;
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&originalvals);
	VALS = originalvals;
	if(originalvals.gain == vals){
		return SAME_CONFIG;
	}else{
	switch(vals){
		default:
		case (GAIN_20_V) :
			VALS.gain = GAIN_20_V;
			ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
			ecg_synch();
			ecg_get_cnfg_ecg(&VALS);
			if(VALS.gain == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
		case (GAIN_40_V) :
		    VALS.gain = GAIN_40_V;
			ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
			ecg_synch();
			ecg_get_cnfg_ecg(&VALS);
			if(VALS.gain == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;			
		case (GAIN_80_V) :
			VALS.gain = GAIN_80_V;
			ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
			ecg_synch();
			ecg_get_cnfg_ecg(&VALS);
			if(VALS.gain == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
		case (GAIN_160_V) :
			VALS.gain = GAIN_160_V;
			ecg_set_cnfg_ecg(VALS,(CNFGECG_GAIN));
			ecg_synch();
			ecg_get_cnfg_ecg(&VALS);
			if(VALS.gain == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;					
		}
	}
	
}


config_status ecg_change_datarate(CNFGECG_RATE_VAL vals){
	MAX30003_CNFG_ECG_VALS  originalvals;
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&originalvals);
	VALS = originalvals;
	if(originalvals.rate == vals){
		return SAME_CONFIG;
		}else{	
	switch(vals){
		default:
		case (RATE_MIN_SPS): 
		 VALS.rate = RATE_MIN_SPS;
		 ecg_set_cnfg_ecg(VALS,(CNFGECG_RATE));
		 ecg_synch();
		 ecg_get_cnfg_ecg(&VALS);
		 if(VALS.rate == vals){
			 return CONFIG_SUCCESS;
		 }else{
			 return CONFIG_FAILURE;
		 }
		 break;
		case (RATE_MED_SPS):
		 VALS.rate = vals;
		 ecg_set_cnfg_ecg(VALS,(CNFGECG_RATE));
		 ecg_synch();
		 ecg_get_cnfg_ecg(&VALS);
		 if(VALS.rate == vals){
			 return CONFIG_SUCCESS;
		 }else{
			 return CONFIG_FAILURE;
		 }
		 break;
		case (RATE_MAX_SPS):
		VALS.rate = vals;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_RATE));
		ecg_synch();
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.rate == vals){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
		break;		    
		}
	}
		
}

config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals){
	MAX30003_CNFG_ECG_VALS  originalvals;
	MAX30003_CNFG_ECG_VALS	VALS;
	ecg_get_cnfg_ecg(&originalvals);
	if(originalvals.dlpf == vals){
		return SAME_CONFIG;
		}else{
	switch(vals){
		case (DLPF_BYPASS):
		VALS.dlpf = DLPF_BYPASS;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
		ecg_synch();
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.dlpf == DLPF_BYPASS){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
		break;
		default:
		case (DLPF_40_HZ):
		VALS.dlpf = DLPF_40_HZ;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
		ecg_synch();
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.dlpf == DLPF_40_HZ){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}
		break;
		case (DLPF_100_HZ): 
		if(originalvals.rate == RATE_MIN_SPS){
			return CONFIG_FAILURE;
		}
		VALS.dlpf = DLPF_100_HZ;
		ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
		ecg_synch();
		ecg_get_cnfg_ecg(&VALS);
		if(VALS.dlpf == DLPF_100_HZ){
			return CONFIG_SUCCESS;
			}else{
			return CONFIG_FAILURE;
		}
		break;
		case (DLPF_150_HZ):
		if(originalvals.rate == RATE_MAX_SPS){
			VALS.dlpf = DLPF_150_HZ;
			ecg_set_cnfg_ecg(VALS,(CNFGECG_DLPF));
			ecg_synch();
			ecg_get_cnfg_ecg(&VALS);
			if(VALS.dlpf == DLPF_150_HZ){
				return CONFIG_SUCCESS;
				}else{
				return CONFIG_FAILURE;
			}
			
		}else{
			return CONFIG_FAILURE;
		}
		break;
		}
	}
}

config_status ecg_init(){
	test_result_t t;
	t =  MAX30003_INIT_TEST_ROUND();
	if(t == TEST_SUCCESS){
		return CONFIG_SUCCESS; 
	}else{
		return CONFIG_FAILURE;
	}
}

config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.en_ecg == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			case (ENECG_ENABLED): 
			VALS.en_ecg = ENECG_ENABLED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_ECG);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_ecg == ENECG_ENABLED){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			default:
			case (ENECG_DISABLED):
			VALS.en_ecg = ENECG_DISABLED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_ECG);
			ecg_synch();			
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_ecg == ENECG_DISABLED){

				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
		}
	}
	
}

config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.en_dcloff == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case (ENDCLOFF_DISABLED):
			VALS.en_dcloff = ENDCLOFF_DISABLED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_DCLOFF);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_dcloff == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case (ENDCLOFF_ENABLED):
			VALS.en_dcloff = ENDCLOFF_ENABLED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_DCLOFF);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_dcloff == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case (_ENDCLOFF_RESERVED1):
			case (_ENDCLOFF_RESERVED2):
				return CONFIG_FAILURE;
			break;
		}
	}
}

config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.ipol == vals){
		return SAME_CONFIG;
		}else{
			switch(vals){
				default:
				case(DCLOFFIPOL_P_UP_N_DOWN):
				VALS.ipol = DCLOFFIPOL_P_UP_N_DOWN;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IPOL);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.ipol == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
				case(DCLOFFIPOL_P_DOWN_N_UP):
				VALS.ipol = DCLOFFIPOL_P_DOWN_N_UP;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IPOL);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.ipol == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;				
			}
	}
}

config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.imag == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case (DCLOFFIMAG_0_nA):
				VALS.imag = DCLOFFIMAG_0_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFIMAG_100_nA):
				VALS.imag = DCLOFFIMAG_100_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFIMAG_10_nA):
				VALS.imag = DCLOFFIMAG_10_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFIMAG_20_nA):
				VALS.imag = DCLOFFIMAG_20_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFIMAG_50_nA):
				VALS.imag = DCLOFFIMAG_50_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFIMAG_5_nA):
				VALS.imag = DCLOFFIMAG_5_nA;
				ecg_set_cnfg_gen(VALS,CNFGGEN_IMAG);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.imag == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case _DCLOFFIMAG_RESERVED1:
			case _DCLOFFIMAG_RESERVED2:
				return CONFIG_FAILURE;
			break;														
		}
	}	
}

config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.vth == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case (DCLOFFVTH_300_mV):
				VALS.vth = DCLOFFVTH_300_mV;
				ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.vth == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFVTH_400_mV):
				VALS.vth = DCLOFFVTH_400_mV;
				ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.vth == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFVTH_450_mV):
				VALS.vth = DCLOFFVTH_450_mV;
				ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.vth == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;
			case (DCLOFFVTH_500_mV):
				VALS.vth = DCLOFFVTH_500_mV;
				ecg_set_cnfg_gen(VALS,CNFGGEN_VTH);
				ecg_synch();
				ecg_get_cnfg_gen(&VALS);
				if(VALS.vth == vals){
					return CONFIG_SUCCESS;
					}else{
					return CONFIG_FAILURE;
				}
				break;												
		}
	}	
}

config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.en_rbias == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case ENRBIAS_DISABLED:
			VALS.en_rbias = ENRBIAS_DISABLED;
			ecg_set_cnfg_gen(VALS, CNFGGEN_EN_RBIAS);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_rbias == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case EBRBIAS_ENABLED:
			VALS.en_rbias = EBRBIAS_ENABLED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_EN_RBIAS);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.en_rbias == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case _ENRBIAS_RESERVED1:
			case _ENRBIAS_RESERVED2:
			return CONFIG_FAILURE;
			break;
		}
	}	
}
	

config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.rbiasv == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			case RBIASV_50_MOHM:
			VALS.rbiasv = RBIASV_50_MOHM;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASV);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasv == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			default:
			case RBIASV_100_MOHM:
			VALS.rbiasv = RBIASV_100_MOHM;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASV);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasv == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case RBIASV_200_MOHM:
			VALS.rbiasv = RBIASV_200_MOHM;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASV);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasv == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case _RBIASV_RESERVED:
				return CONFIG_FAILURE;
			break; 						
		}
	}
}


config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.rbiasp == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case RBIASP_NOT_CONNECTED:
			VALS.rbiasp = RBIASP_NOT_CONNECTED;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASP);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasp == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case RBIASP_CONNECTED:
			VALS.rbiasp = RBIASP_CONNECTED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASP);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasp == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
		}
	}
}
	
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals){
	MAX30003_CNFG_GEN_VALS originalvals;
	MAX30003_CNFG_GEN_VALS VALS;
	ecg_get_cnfg_gen(&originalvals);
	VALS = originalvals;
	if(originalvals.rbiasn == vals){
		return SAME_CONFIG;
	}else{
		switch(vals){
			default:
			case RBIASN_NOT_CONNECTED:
			VALS.rbiasn = RBIASN_NOT_CONNECTED;
			ecg_set_cnfg_gen(VALS, CNFGGEN_RBIASN);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasn == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
			case RBIASN_CONNECTED:
			VALS.rbiasn = RBIASN_CONNECTED;
			ecg_set_cnfg_gen(VALS,CNFGGEN_RBIASN);
			ecg_synch();
			ecg_get_cnfg_gen(&VALS);
			if(VALS.rbiasn == vals){
				return CONFIG_SUCCESS;
			}else{
				return CONFIG_FAILURE;
			}
			break;
		}
	}	
}

config_status ecg_en_dcloff_int2(ENINT_ENDCLOFFINT_VAL vals,ENINT_INTBTYPE_VAL type){
	MAX30003_EN_INT_VALS originalvals;
	MAX30003_EN_INT_VALS VALS;
	ecg_get_en_int2(&originalvals);
	VALS = originalvals;
	if(originalvals.en_dcloffint == vals && originalvals.intb_type == type){
		return SAME_CONFIG;
	}else if(originalvals.en_dcloffint == vals){
		VALS.intb_type = type;
		ecg_set_en_int2(VALS, ENINT_INTB_TYPE);
		ecg_synch();
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type){
			return CONFIG_SUCCESS;
		}else{
			return CONFIG_FAILURE;
		}		

	}else if(originalvals.intb_type == type){
		VALS.en_dcloffint = vals;
		ecg_set_en_int2(VALS, ENINT_EN_DCLOFFINT);
		ecg_synch();
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
		ecg_synch();
		ecg_get_en_int2(&VALS);
		if(VALS.intb_type == type && VALS.en_dcloffint == vals){
			return CONFIG_SUCCESS;

		}else{
			return CONFIG_FAILURE;
		}
	}
		
	
	}

