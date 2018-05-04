/*
 * max30003test.c
 *
 * Created: 5/2/2018 3:24:08 PM
 *  Author: dli40
 */ 

#include "max30003test.h"

int nextstep = 0;

void MAX30003_INIT_TEST(){
	/* create struct to hold the register values */
	MAX30003_EN_INT_VALS en_int_vals;
	MAX30003_EN_INT_VALS en_int_vals2;
	MAX30003_MNGR_INT_VALS mngr_int_vals;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	/* change desired values in the struct */
	en_int_vals.en_eint = ENINT_ENABLED;
	en_int_vals.intb_type = INTBTYPE_NMOS_WITH_PU;
	en_int_vals2.en_lonint = ENLONINT_ENABLED;
	en_int_vals2.intb_type = INTBTYPE_NMOS_WITH_PU;
	mngr_int_vals.efit = EFIT_AS_24;
	cnfg_gen_vals.en_ecg = ENECG_ENABLED;
	cnfg_ecg_vals.rate = RATE_MIN_SPS;
	cnfg_ecg_vals.gain = GAIN_20_V;
	cnfg_ecg_vals.dhpf = DHPF_HALF;
	cnfg_ecg_vals.dlpf = DLPF_40_HZ;
	/* call the set function with the struct, and bitwise OR of the masks to change */
	ecg_set_en_int(en_int_vals, ENINT_EN_EINT|ENINT_INTB_TYPE);
	delay_ms(100);
    ecg_set_en_int2(en_int_vals2, ENINT_EN_EINT|ENINT_INTB_TYPE);
	delay_ms(100);
	ecg_set_mngr_int(mngr_int_vals,MNGRINT_EFIT);
	delay_ms(100);
	ecg_set_cnfg_gen(cnfg_gen_vals,CNFGGEN_EN_ECG );
	delay_ms(100);
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE|CNFGECG_DLPF|CNFGECG_GAIN|CNFGECG_DHPF);
	delay_ms(100);
	// TODO for Tony, change these to match above


	/* before checking, get the register values by passing the struct by reference to the get function */
	ecg_get_en_int(&en_int_vals);
	
	/* check by accessing member of the now updated struct */
	if(en_int_vals.en_eint == ENINT_ENABLED){
		//LED is on
	}
	//if button clicked, LED is off
	nextstep = 1;
	while(nextstep == 1)
	{
		ecg_get_en_int(&en_int_vals2);
		if(en_int_vals.intb_type==INTBTYPE_NMOS_WITH_PU){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_get_en_int2(&en_int_vals2);
	if(en_int_vals2.en_lonint==ENLONINT_ENABLED){
		//LED is on
	}
	//if button clicked, LED is off
	nextstep = 1;
	while(nextstep == 1)
	{
		ecg_get_en_int(&en_int_vals2);
		if(en_int_vals2.intb_type==INTBTYPE_NMOS_WITH_PU)
		{
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_get_mngr_int(&mngr_int_vals);
	if(mngr_int_vals.efit ==EFIT_AS_24){
		//LED is on
	}
	//if button clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		ecg_get_cnfg_gen(&cnfg_gen_vals);
		if(cnfg_gen_vals.en_ecg == ENECG_ENABLED){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MIN_SPS){
		//LED is on
	}
	//if button is clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		if(cnfg_ecg_vals.gain==GAIN_20_V){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	if(cnfg_ecg_vals.dhpf==DHPF_HALF){
		//LED is on
	}
	//if button is clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		if(cnfg_ecg_vals.dlpf==DLPF_40_HZ){
			//LED is on
		}
		//if button is clicked, break the loop;
	}
	nextstep = 0;
}

void MAX30003_INIT_SETUP()
{
	ecg_sw_reset();
	delay_ms(100);
	/*MAX30003_EN_INT_VALS en_int_vals;
	MAX30003_EN_INT_VALS en_int_vals2;
	MAX30003_MNGR_INT_VALS mngr_int_vals;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	/* change desired values in the struct */
	/*en_int_vals.en_eint = ENINT_ENABLED;
	en_int_vals.intb_type = INTBTYPE_NMOS_WITH_PU;
	en_int_vals2.en_lonint = ENLONINT_ENABLED;
	en_int_vals2.intb_type = INTBTYPE_NMOS_WITH_PU;
	mngr_int_vals.efit = EFIT_AS_24;
	cnfg_gen_vals.en_ecg = ENECG_ENABLED;
	cnfg_ecg_vals.rate = RATE_MIN_SPS;
	cnfg_ecg_vals.gain = GAIN_20_V;
	cnfg_ecg_vals.dhpf = DHPF_HALF;
	cnfg_ecg_vals.dlpf = DLPF_40_HZ;
	/* call the set function with the struct, and bitwise OR of the masks to change */
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
}

void MAX30003_TEST_TRANS_RATE()
{
	MAX30003_INIT_SETUP();
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
/*	cnfg_ecg_vals.gain = GAIN_20_V;*/
/*	ecg_set_cnfg_ecg(cnfg)*/
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	
}