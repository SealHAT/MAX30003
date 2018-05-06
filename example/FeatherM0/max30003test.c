/*
 * max30003test.c
 *
 * Created: 5/2/2018 3:24:08 PM
 *  Author: dli40
 */ 

#include "max30003test.h"
#include "driver_init.h"

const MAX30003_CNFG_GEN_VALS CNFGGEN_VALS_DEFAULT = {
    .rbiasn     = RBIASN_NOT_CONNECTED,
    .rbiasp     = RBIASP_NOT_CONNECTED,
    .rbiasv     = RBIASV_100_MOHM,
    .en_rbias   = ENRBIAS_DISABLED,
    .vth        = DCLOFFVTH_300_mV,
    .imag       = DCLOFFIMAG_0_nA,
    .ipol       = DCLOFFIPOL_P_UP_N_DOWN,
    .en_dcloff  = ENDCLOFF_DISABLED,
    .en_ecg     = ENECG_ENABLED,
    .fmstr      = FMSTR_512_HZ,
    .en_ulp_lon = ENULPLON_DISABLED
};

const MAX30003_CNFG_ECG_VALS CNFECG_VALS_DEFAULT = {
    .dhpf = DHPF_HALF,
    .dlpf = DLPF_40_HZ,
    .gain = GAIN_20_V,
    .rate = RATE_MIN_SPS
};
const MAX30003_EN_INT_VALS EN_INT_VALS_DEFAULT = {
    .en_eint = ENINT_ENABLED,
    .intb_type = INTBTYPE_NMOS_WITH_PU
};
const MAX30003_EN_INT_VALS EN_INT2_VALS_DEFAULT = {
    .en_lonint = ENLONINT_ENABLED,
    .intb_type = INTBTYPE_NMOS_WITH_PU
};
const MAX30003_MNGR_INT_VALS MNGR_INT_VALS_DEFAULT = {
    .efit = EFIT_AS_24
};

//constant of masks in each register
const MAX30003_CNFG_ECG_MASKS CNFG_ECG_DEFAULT_MASK = CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE;
const MAX30003_MNGR_INT_MASKS MNGR_INT_DEFAULT_MASK = MNGRINT_EFIT;
const MAX30003_EN_INT_MASKS EN_INT_DEFAULT_MASK = ENINT_INTB_TYPE|ENINT_EN_EINT;
const MAX30003_EN_INT_MASKS EN_INT2_DEFAULT_MASK = ENINT_INTB_TYPE|ENINT_EN_LONINT;
const MAX30003_CNFG_GEN_MASKS CNFG_GEN_DEFAULT_MASK = CNFGGEN_EN_ECG;



int nextstep = 0;
bool FLAG_TIMEOUT   = false; /* flag if a test ran for longer than expected */
bool FIFO_INTERRUPT = false;//Flag of FIFO interrupt
bool FLAG_INTERRUPT = false;//Flag of LEAD-On detection

void MAX30003_INIT_TEST(){
	nextstep = 0;
	/* create struct to hold the register values */
	MAX30003_EN_INT_VALS en_int_vals;
	MAX30003_EN_INT_VALS en_int_vals2;
	MAX30003_MNGR_INT_VALS mngr_int_vals;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;

	/* before checking, get the register values by passing the struct by reference to the get function */
	MAX30003_INIT_SETUP();
	ecg_get_en_int(&en_int_vals);
	
	/* check by accessing member of the now updated struct */
	if(en_int_vals.en_eint == ENINT_ENABLED){
		//LED is on
	}
	//if button clicked, LED is off, break the loop;
	nextstep = 1;
	while(nextstep == 1)
	{
		ecg_get_en_int(&en_int_vals2);
		if(en_int_vals.intb_type==INTBTYPE_NMOS_WITH_PU){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 2;
	while(nextstep==2){
	ecg_get_en_int2(&en_int_vals2);
	if(en_int_vals2.en_lonint==ENLONINT_ENABLED){
		//LED is on
	}
	//if button clicked, LED is off, break the loop;
	}
	nextstep = 3;
	while(nextstep == 3)
	{
		ecg_get_en_int(&en_int_vals2);
		if(en_int_vals2.intb_type==INTBTYPE_NMOS_WITH_PU)
		{
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 4;
	while(nextstep==4){
	ecg_get_mngr_int(&mngr_int_vals);
	if(mngr_int_vals.efit ==EFIT_AS_24){
		//LED is on
	}
	//if button clicked, LED is off, break the loop;
	}
	nextstep = 5;
	while(nextstep==5){
		ecg_get_cnfg_gen(&cnfg_gen_vals);
		if(cnfg_gen_vals.en_ecg == ENECG_ENABLED){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 6;
	while(nextstep==6){
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MIN_SPS){
		//LED is on
	}
	//if button is clicked, LED is off, break the loop;
	}
	nextstep = 7;
	while(nextstep==7){
		if(cnfg_ecg_vals.gain==GAIN_20_V){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 8;
	while(nextstep==8){
	if(cnfg_ecg_vals.dhpf==DHPF_HALF){
		//LED is on
	}
	//if button is clicked, LED is off, break the loop;
	}
	nextstep = 9;
	while(nextstep==9){
		if(cnfg_ecg_vals.dlpf==DLPF_40_HZ){
			//LED is on
		}
		//if button is clicked, break the loop;
	}
	nextstep = 0;
}

bool MAX30003_INIT_TEST_ROUND(){
	int success             = 0;
	bool enint_success      = false;
	bool enint2_success     = false;
	bool mngr_int_sucess    = false;
	bool cnfg_gen_sucess    = false;
	bool cnfg_ecg_sucess    = false;
	TEST_RESULT result      = TEST_PENDING;
    MAX30003_EN_INT_VALS    en_int_vals;
    MAX30003_EN_INT_VALS    en_int_vals2;
    MAX30003_MNGR_INT_VALS  mngr_int_vals;
    MAX30003_CNFG_GEN_VALS  cnfg_gen_vals;
    MAX30003_CNFG_ECG_VALS  cnfg_ecg_vals;

	MAX30003_INIT_SETUP();

	ecg_get_en_int(&en_int_vals);
	if(en_int_vals.en_eint == ENINT_ENABLED){
		success++;
	}
	if(en_int_vals.intb_type==INTBTYPE_NMOS_WITH_PU){
		success++;
	}
	if(success==2){
		enint_success = true;
	}else{
		enint_success = false;
	}

	ecg_get_en_int2(&en_int_vals2);
	if(en_int_vals2.en_lonint == ENLONINT_ENABLED){
		success++;
	}
	if(en_int_vals2.intb_type==INTBTYPE_NMOS_WITH_PU){
		success++;
	}
	if(success==4){
		enint2_success = true;
	}else{
		enint2_success = false;
	}

	ecg_get_mngr_int(&mngr_int_vals);
	if(mngr_int_vals.efit==EFIT_AS_24){
		success++;
	}
	if(success==5){
		mngr_int_sucess = true;
	}else{
		mngr_int_sucess = false;
	}

	ecg_get_cnfg_gen(&cnfg_gen_vals);
	if(cnfg_gen_vals.en_ecg == ENECG_ENABLED){
		success++;
	}
	if(success==6){
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
	if(success==10){
		cnfg_ecg_sucess = true;
	}else{
		cnfg_ecg_sucess = false;
	}
    	
	if(cnfg_ecg_sucess&&cnfg_gen_sucess&&enint2_success&&enint_success&&mngr_int_sucess){
		//set a counter, LED is on for a while;
		result = TEST_SUCCESS;
	}else{
		result = TEST_CFGFAIL;
	}
	
	return result;		
}

TEST_RESULT MAX30003_CHECK_INIT_VALS_ROUND(){
	int success = 0;
    int attempts = 0;
	bool enint_success = false;
	bool enint2_success = false;
	bool mngr_int_sucess = false;
	bool mngr_dyn_success = false;
	bool cnfg_gen_sucess = false;
	bool cnfg_ecg_sucess = false;
	bool cnfg_rtor1_success = false;
	bool cnfg_emux_success = false;
	bool cnfg_cal_success = false;
	TEST_RESULT result = TEST_CFGFAIL;
	
	MAX30003_EN_INT_VALS en_int_vals;
	MAX30003_EN_INT_VALS en_int_vals2;
	MAX30003_MNGR_INT_VALS mngr_int_vals;
	MAX30003_MNGR_DYN_VALS mngr_dyn_vals;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	MAX30003_CNFG_EMUX_VALS cnfg_emux_vals;
	MAX30003_CNFG_CAL_VALS cnfg_cal_vals;
	MAX30003_CNFG_RTOR1_VALS cnfg_rtor1_vals;
	while(TEST_CFGFAIL && attempts < 3) {
        
	    ecg_get_en_int(&en_int_vals);
	    if(en_int_vals.en_eint == ENINT_ENABLED){
		    success++;
	    }
	    if(en_int_vals.intb_type==INTBTYPE_NMOS_WITH_PU){
		    success++;
	    }
	    if(success==2){
		    enint_success = true;
		    }else{
		    enint_success = false;
	    }

	    ecg_get_en_int2(&en_int_vals2);
	    if(en_int_vals2.en_lonint == ENLONINT_ENABLED){
		    success++;
	    }
	    if(en_int_vals2.intb_type==INTBTYPE_NMOS_WITH_PU){
		    success++;
	    }
	    if(success==4){
		    enint2_success = true;
		    }else{
		    enint2_success = false;
	    }

	    ecg_get_mngr_int(&mngr_int_vals);
	    if(mngr_int_vals.efit==EFIT_AS_24){
		    success++;
	    }
	    if(success==5){
		    mngr_int_sucess = true;
		    }else{
		    mngr_int_sucess = false;
	    }	

	    ecg_get_mngr_dyn(&mngr_dyn_vals);
	    if(mngr_dyn_vals.fast == FAST_NORMAL){
		    success++;//mngr_dyn_success = true; 
	    }
	    if(success==6){
		    mngr_dyn_success = true;
	    }
	    else{
		    mngr_dyn_success = false;
	    }	

	    ecg_get_cnfg_gen(&cnfg_gen_vals);
	    if(cnfg_gen_vals.en_ecg == ENECG_ENABLED){
		    success++;
	    }
	    if(cnfg_gen_vals.en_dcloff == ENDCLOFF_DISABLED){
		    success++;
	    }
	    if(success==7){
		    cnfg_gen_sucess = true;
		    }else{
		    cnfg_gen_sucess = false;
	    }

	    ecg_get_cnfg_cal(&cnfg_cal_vals);
	    if(cnfg_cal_vals.en_vcal == ENVCAL_DISABLED){
		    success++;
	    }
	    if(success==7){
		    cnfg_cal_success = true;
	    }else{
		    cnfg_cal_success = false;
	    }

	    ecg_get_cnfg_emux(&cnfg_emux_vals);
	    if(cnfg_emux_vals.pol == POL_NON_INVERTED){
		    success++;
	    }
	    if(success==8){
		    cnfg_emux_success = true;
	    }else{
		    cnfg_emux_success = false;
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
	    if(success==12){
		    cnfg_ecg_sucess = true;
	    }else{
		    cnfg_ecg_sucess = false;
	    }

	    ecg_get_cnfg_rtor1(&cnfg_rtor1_vals);
	    if(cnfg_rtor1_vals.en_rtor == ENRTOR_DISABLED){
		    success++;
	    }
	    if(success==13){
		    cnfg_rtor1_success = true;
	    }else{
		    cnfg_rtor1_success = false;
	    }
	    if(cnfg_rtor1_success&&cnfg_ecg_sucess&&cnfg_emux_success&&cnfg_cal_success&&cnfg_gen_sucess&&mngr_dyn_success&&mngr_int_sucess&&enint2_success&&enint_success){
		    result = TEST_SUCCESS;
	    }else{
		    result = TEST_CFGFAIL;
            attempts++;
	    }

        
	    if(result != TEST_SUCCESS){
            MAX30003_INIT_SETUP();
	    }
	}

	return result;
}
// The function initialize the MAX30003
void MAX30003_INIT_SETUP()
{
	ecg_sw_reset();
	delay_ms(100);
	ecg_set_en_int(EN_INT_VALS_DEFAULT, EN_INT_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_en_int2(EN_INT2_VALS_DEFAULT, EN_INT2_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_mngr_int(MNGR_INT_VALS_DEFAULT,MNGR_INT_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_cnfg_gen(CNFGGEN_VALS_DEFAULT,CNFG_GEN_DEFAULT_MASK);
	delay_ms(100);
	ecg_set_cnfg_ecg(CNFECG_VALS_DEFAULT,CNFG_ECG_DEFAULT_MASK);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
}
// The function to test the data rate
void MAX30003_TEST_TRANS_RATE()
{
	//Initialize the variable needed in the function
	nextstep = 0;
	TEST_RESULT test;
	int attempts = 0;
	bool data_trans_rate_changed = false;
	
	
	//check the registers' values are the one we want or not. if they are, we continue the test, otherwise
	while(nextstep==0 && attempts<3){
	test = MAX30003_CHECK_INIT_VALS_ROUND();
	if(test==TEST_SUCCESS){
		nextstep=1;
	}else{
		MAX30003_INIT_SETUP();
		attempts++;
	}
}
	
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	//set a timer, start counting the time and record the data.
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while !TimeExpired loop
	//Continue the next selection data-transfer rate
	
    nextstep = 2;
	attempts=0;
	while(nextstep==2&&!data_trans_rate_changed&&attempts<3){
	cnfg_ecg_vals.rate = RATE_MED_SPS;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MED_SPS){
		data_trans_rate_changed = true;
		}else{
		attempts++;
	}
}

	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while !TimeExpired loop

    nextstep = 3;
	//reset the bool data_trans_rate change
	data_trans_rate_changed = false;
	attempts = 0;
	while(nextstep==3&&!data_trans_rate_changed&&attempts<3){
	cnfg_ecg_vals.rate = RATE_MAX_SPS;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MAX_SPS){
		data_trans_rate_changed = true;
	}else{
		attempts++;
	}
	
}
	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while !TimeExpired loop
	
	//LED is always on(outside while loop) to indicate this rate of test finished
}

void MAX30003_TEST_GAIN()
{
	nextstep = 0;
	TEST_RESULT test;
	int attempts = 0;
	bool data_gain_changed = false;
	//check the registers' values are the one we want or not. if they are, we continue the test, otherwise
	while(nextstep==0 && attempts<3){
		test = MAX30003_CHECK_INIT_VALS_ROUND();
		if(test==TEST_SUCCESS){
			nextstep=1;
		}else{
			MAX30003_INIT_SETUP();
			attempts++;
		}
	}
	attempts = 0;
	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while !TimeExpired loop
	
	nextstep = 2;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	while(nextstep==2&&!data_gain_changed&&attempts<3){
	cnfg_ecg_vals.gain = GAIN_40_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_40_V){
		data_gain_changed = true;
	}else{
		attempts++;
	}
}

	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
		//FIFO_INTERRUPT = !FIFO_INTERRUPT
	}//inside the while loop		

	nextstep = 3;
	//reset the bool _gain change
	data_gain_changed = false;
	attempts = 0;
	while(nextstep==3&&!data_gain_changed&&attempts<3){
	cnfg_ecg_vals.gain = GAIN_80_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_80_V){
		data_gain_changed = true;
		}else{
		attempts++;
	}
}

	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while loop

	nextstep = 4;		
	//reset the bool _gain change
	data_gain_changed = false;
	attempts = 0;
	while(nextstep==4&&!data_gain_changed&&attempts<3){
	cnfg_ecg_vals.gain = GAIN_160_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_160_V){
		data_gain_changed = true;
		}else{
		attempts++;
	}
}
	//if button is clicked, start counting the time and record the data(we can disable the ecg in intial setup and enable it when button is clicked)
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while loop
	//LED is always on(outside while loop) to indicate this rate of test finished
		
}

void MAX30003_TEST_Fre(){
	nextstep = 0;
	TEST_RESULT test;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	int attempts = 0;
	bool data_fre_changed = false;
	//check the registers' values are the one we want or not. if they are, we continue the test, otherwise
	while(nextstep==0 && attempts<3){
		test = MAX30003_CHECK_INIT_VALS_ROUND();
		if(test==TEST_SUCCESS){
			nextstep=1;
			}else{
			MAX30003_INIT_SETUP();
			attempts++;
		}
	}
	//set a timer, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
	}//inside the while loop
	//LED is always on(outside while loop) to indicate this rate of test finished
	
	nextstep = 2;
	attempts = 0;
	while(nextstep==2&&!data_fre_changed&&attempts<3){
		cnfg_ecg_vals.dlpf = DLPF_100_HZ;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
		ecg_synch();
		delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_100_HZ){
			data_fre_changed = true;
			}else{
			attempts++;
		}
	}
		//set a timer, start counting the time and record the data(we can disable the ecg in intial setup and enable it when button is clicked)
		//while time is not expired:
		if(FIFO_INTERRUPT){
			//Toggle LED
			//Record data in the storage
			//Reset FIFO
		}//inside the while loop
		
	 nextstep = 3;
	//reset bool data_fre_change
	!data_fre_changed = false;
	attempts = 0;
	while(nextstep==3&&!data_fre_changed&&attempts<3){
		cnfg_ecg_vals.dlpf = DLPF_150_HZ;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
		ecg_synch();
		delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_150_HZ){
			data_fre_changed = true;
		}else{
			attempts++;
		}
		
		//set a timer, start counting the time and record the data
		//while time is not expired:
		if(FIFO_INTERRUPT){
			//Toggle LED
			//Record data in the storage
			//Reset FIFO
		}//inside the while loop
		//LED is always on(outside while loop) to indicate this rate of test finished
		
    nextstep = 4;
	//reset bool data_fre_change
	!data_fre_changed = false;
	attempts = 0;
	while(nextstep==4&&!data_fre_changed&&attempts<3){
		cnfg_ecg_vals.dlpf = DLPF_BYPASS;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_BYPASS){
			data_fre_changed = true;
		}else{
			attempts++;
		}
		//if button is clicked, start counting the time and record the data(we can disable the ecg in intial setup and enable it when button is clicked)
		//while time is not expired:
		if(FIFO_INTERRUPT){
			//Toggle LED
			//Record data in the storage
			//Reset FIFO
			//FIFO_INTERRUPT = !FIFO_INTERRUPT
		}//inside the while loop
		
		//LED is always on(outside while loop) to indicate this rate of test finished
		
}

void MAX30003_TEST_HELLO_WORLD(){
	bool pass_Init_test;
	pass_Init_test = MAX30003_INIT_TEST_ROUND();
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	cnfg_gen_vals.en_ecg = ENECG_ENABLED;
	if(pass_Init_test == true){
	// LED is on	
	}else{//force to open ecg 
	ecg_sw_reset();
	delay_ms(100);
	ecg_set_cnfg_gen(cnfg_gen_vals,CNFGGEN_EN_ECG );
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	}
	//if button is clicked, start the counter and start record the data
	//while time is not expierd:
	if(FIFO_INTERRUPT){
		//toogle the led;
		//transfer data into storage
		//reset the FIFO
	}
	//outside the while loop
	//LED is always on to indicate the test is finished.
}

void MAX30003_FLAG_TEST(){
	nextstep = 0;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	cnfg_gen_vals.en_ecg = ENECG_ENABLED;
	MAX30003_INIT_SETUP();
	ecg_get_cnfg_gen(&cnfg_gen_vals);
	if(cnfg_gen_vals.en_ulp_lon==ENULPLON_ENABLED){
		//LED is on
	}else{
		MAX30003_INIT_SETUP();
	}
	//if button is clicked, next step = 1;
	while(nextstep==1){
	if(FLAG_INTERRUPT){
	 //LED is on	
	}else{
		//LEd is off
	}
	}
}

void MAX30003_FIFO_TEST(){
    /* STEPS:
        1. Check relevant register values. [do for every test]
            - (optional) set and check again
            - (optional) repeat for a FINITE number of times
            - return ```TEST_CFGFAIL``` if check fails, otherwise continue
        2. Delay, then reset ecg_fifo, don't delay after.
        3. Start Timer and enter a loop that checks for interrupt.
            - document how long the timer will run for
            - use the function ```gpio_get_pin_level(INT1)```
                - ```false``` indicates an interrupt
                - there is also the ```INT2``` pin
            - increment the counter if there is an interrupt
        4. Exit the loop after a set number of counts
            - should also exit after fixed amount of time 
                - check for global flag ```FLAG_TIMEOUT``` in loop
                - set ```result = TEST_TIMEOUT``` and exit test
        5. Stop the timer and calculate if interrupt rate is okay
            - allow room for error, document calculation and expectations
        6. Set ```result = TEST_SUCCESS``` or ```result = TEST_FAILURE```, and exit
    */
    
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	cnfg_gen_vals.en_ecg = ENECG_ENABLED;
	bool INIT_TEST_PASS;
	INIT_TEST_PASS = MAX30003_INIT_TEST_ROUND();
	if(INIT_TEST_PASS){
		//LED is on
	}else{
	ecg_sw_reset();
	delay_ms(100);
	ecg_set_cnfg_gen(cnfg_gen_vals,CNFGGEN_EN_ECG );
	delay_ms(100);
	ecg_synch();
	delay_ms(100);	
	}




	//if button is clicked, next step = 1 and start counter, and !timeexpiered in while loop;
    if(gpio_get_pin_level(INT1) == false ) {
        delay_ms(10000);
    }

	while(nextstep==1){
		if(FIFO_INTERRUPT){
			//LED is on
			}else{
			//LEd is off
		}
	}
	//LED always on indicate test is finished	
}
