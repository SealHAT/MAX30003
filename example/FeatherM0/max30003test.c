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
	
	/* change desired values in the struct */
	en_int_vals.en_eint = ENINT_ENABLED;
	en_int_vals.intb_type = INTBTYPE_NMOS_WITH_PU;
	
	/* call the set function with the struct, and bitwise OR of the masks to change */
	ecg_set_en_int(en_int_vals, ENINT_EN_EINT|ENINT_INTB_TYPE);
	delay_ms(100);

	// TODO for Tony, change these to match above
	ecg_set_en_int2(ENINT_ENLONINT_VAL,ENLONINT_ENABLED);
	ecg_set_en_int2(ENINT_INTBTYPE_VAL,INTBTYPE_NMOS_WITH_PU);

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
		ecg_get_en_int(ENINT_INTBTYPE_VAL);
		if(ENINT_INTBTYPE_VAL==INTBTYPE_NMOS_WITH_PU){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_get_en_int(ENINT_ENLONINT_VAL);
	if(ENINT_ENLONINT_VAL==ENLONINT_ENABLED){
		//LED is on
	}
	//if button clicked, LED is off
	nextstep = 1;
	while(nextstep == 1)
	{
		ecg_get_en_int(ENINT_INTBTYPE_VAL);
		if(ENINT_INTBTYPE_VAL==INTBTYPE_NMOS_WITH_PU)
		{
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_set_mngr_int(MAX30003_MNGR_INT_VALS,EFIT_AS_24);
	delay_ms(100);
	if(MAX30003_MNGR_INT_VALS ==EFIT_AS_24){
		//LED is on
	}
	//if button clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		ecg_set_cnfg_gen(CNFGGEN_EN_ECG,ENECG_ENABLED);
		delay_ms(100);
		ecg_get_cnfg_gen(CNFGGEN_EN_ECG);
		if(CNFGGEN_EN_ECG == ENECG_ENABLED){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_set_cnfg_ecg(CNFGECG_RATE_512_PROG_VAL,RATE512_SPS_512);
	delay_ms(100);
	ecg_get_cnfg_ecg(CNFGECG_RATE_512_PROG_VAL);
	if(CNFGECG_RATE_512_PROG_VAL == RATE512_SPS_512){
		//LED is on
	}
	//if buttion is clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		ecg_set_cnfg_ecg(CNFGECG_GAIN_VAL,GAIN_20_V);
		delay_ms(100);
		ecg_get_cnfg_ecg(CNFGECG_GAIN_VAL);
		if(CNFGECG_GAIN_VAL==GAIN_20_V){
			//LED is on
		}
		//if button is clicked, break the loop
	}
	nextstep = 0;
	ecg_set_cnfg_ecg(CNFGECG_DHPF_VAL,DHPF_HALF);
	delay_ms(100);
	ecg_get_cnfg_ecg(CNFGECG_DHPF_VAL);
	if(CNFGECG_DHPF_VAL==DHPF_HALF){
		//LED is on
	}
	//if button is clicked, LED is off
	nextstep = 1;
	while(nextstep==1){
		ecg_set_cnfg_ecg(CNFGECG_DLPF_VAL,DLPF_40_HZ);
		delay_ms(100);
		ecg_get_cnfg_ecg(CNFGECG_DLPF_VAL);
		if(CNFGECG_DLPF_VAL==DLPF_40_HZ){
			//LED is on
		}
		//if button is clicked, break the loop;
	}
	nextstep = 0;
}