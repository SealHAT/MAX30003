/*
 * max30003test.c
 *
 * Created: 5/2/2018 3:24:08 PM
 *  Author: dli40
 */ 

#include "max30003test.h"

int nextstep = 0;
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
	/*ecg_set_en_int(en_int_vals, ENINT_EN_EINT|ENINT_INTB_TYPE);
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
	int success = 0;
	bool enint_success = false;
	bool enint2_success = false;
	bool mngr_int_sucess = false;
	bool cnfg_gen_sucess = false;
	bool cnfg_ecg_sucess = false;
	bool result = false;
	MAX30003_INIT_SETUP();
	MAX30003_EN_INT_VALS en_int_vals;
	MAX30003_EN_INT_VALS en_int_vals2;
	MAX30003_MNGR_INT_VALS mngr_int_vals;
	MAX30003_CNFG_GEN_VALS cnfg_gen_vals;
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
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
		result = true;
	}else{
		result = false;
	}
	
	return result;		
}

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

void MAX30003_TEST_TRANS_RATE()
{
	nextstep = 0;
	MAX30003_INIT_SETUP();
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
/*	cnfg_ecg_vals.gain = GAIN_20_V;*/
/*	ecg_set_cnfg_ecg(cnfg)*/
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate==RATE_MIN_SPS){
		//LED is on
	}else{
	  MAX30003_INIT_SETUP();//rerun the initak function if the rate is not set correctly;
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
	//if button is clicked, nextstep = 1;
	while(nextstep==1){
	cnfg_ecg_vals.rate = RATE_MED_SPS;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MED_SPS){
		//LED is on
	}else{
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	}
	//if button is clicked, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
		//FIFO_INTERRUPT = !FIFO_INTERRUPT
	}//inside the while loop
	//LED is always on(outside while loop) to indicate this rate of test finished
	//if button is clicked, break the loop, next step = 2;
	}
	while(nextstep==2){
	cnfg_ecg_vals.rate = RATE_MAX_SPS;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.rate == RATE_MAX_SPS){
		//LED is on
		}else{
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
		delay_ms(100);
		ecg_synch();
		delay_ms(100);
	}
	//if button is clicked, start counting the time and record the data
	//while time is not expired:
	if(FIFO_INTERRUPT){
		//Toggle LED
		//Record data in the storage
		//Reset FIFO
		//FIFO_INTERRUPT = !FIFO_INTERRUPT
	}//inside the while loop
	//LED is always on(outside while loop) to indicate this rate of test finished
	}
}

void MAX30003_TEST_GAIN()
{
	nextstep = 0;
	MAX30003_INIT_SETUP();
	MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	/*	cnfg_ecg_vals.gain = GAIN_20_V;*/
	/*	ecg_set_cnfg_ecg(cnfg)*/
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_20_V){
		//LED is on
	}else{
		MAX30003_INIT_SETUP();//rerun the initak function if the rate is not set correctly;
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
	//if button is clicked, nextstep = 1;
	while(nextstep==1){
	cnfg_ecg_vals.gain = GAIN_40_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_40_V){
		//LED is on
	}else{
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
	delay_ms(100);	
	ecg_synch();
	delay_ms(100);	
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
	//if button is clicked, break the loop and nextstep = 2;
	}
	while(nextstep==2){
	cnfg_ecg_vals.gain = GAIN_80_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_80_V){
		//LED is on
		}else{
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
		delay_ms(100);
	ecg_synch();
	delay_ms(100);
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
	//if button is clicked, break the loop and nextstep = 3;		
	}
	while(nextstep==3){
	cnfg_ecg_vals.gain = GAIN_160_V;
	ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
	delay_ms(100);
	ecg_synch();
	delay_ms(100);
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.gain==GAIN_160_V){
		//LED is on
		}else{
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
		delay_ms(100);
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
	//if button is clicked, break the loop and nextstep = 0;		
	}
	
		
}

void MAX30003_TEST_Fre(){
	nextstep = 0;
	MAX30003_INIT_SETUP();
    MAX30003_CNFG_ECG_VALS cnfg_ecg_vals;
	ecg_get_cnfg_ecg(&cnfg_ecg_vals);
	if(cnfg_ecg_vals.dlpf==DLPF_40_HZ){
		//LED is on
		}else{
		MAX30003_INIT_SETUP();//rerun the initak function if the rate is not set correctly;
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
	//if button is clicked, nextstep = 1;
	while(nextstep==1){
		cnfg_ecg_vals.dlpf = DLPF_100_HZ;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
	ecg_synch();
	delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_100_HZ){
			//LED is on
			}else{
			ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
			delay_ms(100);
			ecg_synch();
			delay_ms(100);
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
		//if button is clicked, break the loop and nextstep = 2;
	}
	while(nextstep==2){
		cnfg_ecg_vals.dlpf = DLPF_150_HZ;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
		ecg_synch();
		delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_150_HZ){
			//LED is on
			}else{
			ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
			delay_ms(100);
			ecg_synch();
			delay_ms(100);
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
		//if button is clicked, break the loop and nextstep = 3;
	}
	while(nextstep==3){
		cnfg_ecg_vals.dlpf = DLPF_BYPASS;
		ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);
		delay_ms(100);
		ecg_get_cnfg_ecg(&cnfg_ecg_vals);
		if(cnfg_ecg_vals.dlpf==DLPF_BYPASS){
			//LED is on
			}else{
			ecg_set_cnfg_ecg(cnfg_ecg_vals,CNFGECG_RATE);//rerun the initak function if the rate is not set correctly;
			delay_ms(100);
			ecg_synch();
			delay_ms(100);
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
		//if button is clicked, break the loop and nextstep = 0;
	}
	
	
			
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
	nextstep = 0;
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
	while(nextstep==1){
		if(FIFO_INTERRUPT){
			//LED is on
			}else{
			//LEd is off
		}
	}
	//LED always on indicate test is finished	
}
