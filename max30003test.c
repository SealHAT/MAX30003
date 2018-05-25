/*
 * max30003test.c
 *
 * Created: 5/2/2018 3:24:08 PM
 *  Author: dli40
 */

#include "max30003test.h"
#include "driver_init.h"

/* Message Strings */
char WELCOME[]       = "Welcome to the SealHAT EKG test suite!\nPlease start the capture to textfile within CoolTerm now!\nBe sure to name your file \"sealtest.txt\" and change your baudrate to max.\n";
char START_TEST[]    = "Please press \"b\" to begin!\n";
char TEST_PASS[]     = "Test complete. Result: PASS\n";
char TEST_FAIL[]     = "Test complete. Result: FAIL ";
char GOODBYE[]       = "\n\nAll tests are complete. The device may now be disconnected. Goodbye!\n";
char PASS[]          = "All tests passed!\n";
char FAIL[]          = "One or more tests failed :(\n";
char DATA_COLLECT[]  = "Data collection is finished. Test complete.\n";
char RATE[]			 = "New rate: \n";
char GAIN[]			 = "New gain: \n";
char LOWPASS[]		 = "New lowpass: \n";

char NEXT_OR_REDO[]  = "Press \'r\' to redo the test or \'n\' to go to the next test.\n";


/* default values for registers */
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
    .en_lonint = ENLONINT_DISABLED,
    .intb_type = INTBTYPE_NMOS_WITH_PU
};
const MAX30003_MNGR_INT_VALS MNGR_INT_VALS_DEFAULT = {
    .efit = EFIT_AS_24
};

/* constant of masks in each register */
const MAX30003_CNFG_ECG_MASKS CNFG_ECG_DEFAULT_MASK = CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE;
const MAX30003_MNGR_INT_MASKS MNGR_INT_DEFAULT_MASK = MNGRINT_EFIT;
const MAX30003_EN_INT_MASKS EN_INT_DEFAULT_MASK = ENINT_INTB_TYPE|ENINT_EN_EINT;
const MAX30003_EN_INT_MASKS EN_INT2_DEFAULT_MASK = ENINT_INTB_TYPE|ENINT_EN_LONINT;
const MAX30003_CNFG_GEN_MASKS CNFG_GEN_DEFAULT_MASK = CNFGGEN_EN_ECG;

/* global flags and error states */
TEST_ER test_errno  = TEST_NOERROR;	/* errno for checking why a test has failed */
bool flag_timeout	= false; /* flag if a test ran for longer than expected */
bool int1_level_n   = false; /*	interrupt 1 pin state, active low */
bool int2_level_n   = false; /*	interrupt 2 pin state, active low */

/* strings for error values */
char NO_ERROR_STR[] = "TEST_NOERROR\n";
char TIMEOUT_STR[]  = "TEST_TIMEOUT\n";
char CFG_FAIL_STR[] = "TEST_CFGFAIL\n";
char RUN_FAIL_STR[] = "TEST_RUNFAIL\n";

const int ERROR_STR_LEN = 14;



test_result_t MAX30003_INIT_TEST_ROUND(){
	int success             = 0;
	bool enint_success      = false;
	bool enint2_success     = false;
	bool mngr_int_sucess    = false;
	bool cnfg_gen_sucess    = false;
	bool cnfg_ecg_sucess    = false;
	test_result_t result    = TEST_FAILURE;
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
	if(en_int_vals2.en_lonint == ENLONINT_DISABLED){
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
		test_errno = TEST_NOERROR;
	}else{
		result = TEST_FAILURE;
		test_errno = TEST_CFGFAIL;
	}

	return result;
}

test_result_t MAX30003_INIT_SETUP()
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

char* error_no_to_string()
{
    switch(test_errno)
    {
        case(TEST_NOERROR):
            return NO_ERROR_STR;
            break;
        case(TEST_TIMEOUT):
            return TIMEOUT_STR;
            break;
        case(TEST_CFGFAIL):
            return CFG_FAIL_STR;
            break;
        case(TEST_RUNFAIL):
            return RUN_FAIL_STR;
            break;
        default:
            return NO_ERROR_STR;
            break;
    }
}

void ecg_test_welcome()
{
	int  retVal;
	/* Set up USB connection */
    /* Wait for USB connection to be made with computer. Must be down to receive (DTR). */
    do { /* NOTHING */ } while (!usb_dtr());

    /* Write welcome message to the serial console. If the operation fails, it will continue
     * trying to send until it is successful. */
    do {
        retVal = usb_write((uint8_t *) WELCOME, sizeof(WELCOME) - 1);
    } while((retVal != USB_OK) || !usb_dtr());
}

void ecg_test_goodbye()
{
	int retVal;
	do { retVal = usb_write((uint8_t *) GOODBYE, sizeof(GOODBYE) - 1); } while((retVal != USB_OK) || !usb_dtr());
}

void ecg_runtest(const char MSG[], uint8_t test_num, test_result_t(*test_function)(void))
{
	uint32_t		retVal;
	char			charBuffer[30];
	char			getCharValue;
	test_result_t	result;
	bool			test_complete = false;

    do { retVal = usb_write((uint8_t *) START_TEST, sizeof(START_TEST) - 1); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'b');

    while (test_complete == false)
    {

	    snprintf(charBuffer, 15,"\nBegin test %1d\n", 1);
	    do { retVal = usb_write((uint8_t *) charBuffer, 14); } while((retVal != USB_OK) || !usb_dtr());

	    /* FUNCTION CALL FOR TEST 1 GOES HERE */
	    result = test_function();

	    /* Print success or failure message to the console. */
	    if(result == TEST_SUCCESS)
	    {
		    do { retVal = usb_write((uint8_t *) TEST_PASS, sizeof(TEST_PASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
	    }
	    else
	    {
		    do { retVal = usb_write((uint8_t *) TEST_FAIL, sizeof(TEST_FAIL) - 1); } while((retVal != USB_OK) || !usb_dtr());
		    do { retVal = usb_write((uint8_t *) error_no_to_string(), ERROR_STR_LEN - 1); } while((retVal != USB_OK) || !usb_dtr());
	    }

	    /* Determine if the user wants to redo the test ('r') or go to the next test ('n') */
	    do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
	    do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');

	    if(getCharValue == 'n')
	    {
		    test_complete = true;
	    }

	    } /* End test 1 loop. */
}

void ecg_test_interactive_switch(uint8_t test_num, uint8_t *rate_val, uint8_t *gain_val, uint8_t *lowpass_val)
{
	uint32_t		retVal;
	char			charBuffer[30];
	char			getCharValue;
	
	do { retVal = usb_write((uint8_t *) NEXT_OR_REDO, sizeof(NEXT_OR_REDO) - 1); } while((retVal != USB_OK) || !usb_dtr());
	do { getCharValue = usb_get(); } while(getCharValue != 'n' && getCharValue != 'r');
			
	if(getCharValue == 'n')
	{
		/* Print end-of-test mark to file. */
		snprintf(charBuffer, 9,"%1d,%1d,%1d,%1d\n", *rate_val, *gain_val, *lowpass_val, test_num);
		do { retVal = usb_write((uint8_t *) charBuffer, 8); } while((retVal != USB_OK) || !usb_dtr());
				
		test_num++;
				
		do { retVal = usb_write((uint8_t *) RATE, sizeof(RATE) - 1); } while((retVal != USB_OK) || !usb_dtr());
		do { getCharValue = usb_get(); } while(getCharValue != '0' && getCharValue != '1' && getCharValue != '2');
		rate_val = (uint8_t)(getCharValue) - 48;
		do { retVal = usb_write((uint8_t *) GAIN, sizeof(GAIN) - 1); } while((retVal != USB_OK) || !usb_dtr());
		do { getCharValue = usb_get(); } while(getCharValue != '0' && getCharValue != '1' && getCharValue != '2' && getCharValue != '3');
		gain_val = (uint8_t)(getCharValue) - 48;
		do { retVal = usb_write((uint8_t *) LOWPASS, sizeof(LOWPASS) - 1); } while((retVal != USB_OK) || !usb_dtr());
		do { getCharValue = usb_get(); } while(getCharValue != '0' && getCharValue != '1' && getCharValue != '2' && getCharValue != '3');
		lowpass_val = (uint8_t)(getCharValue) - 48;
				
		MAX30003_CONFIG_TEST(*rate_val, *gain_val, *lowpass_val);
		ecg_synch();
		ecg_fifo_reset();
	}	
}

test_result_t MAX30003_CONFIG_TEST(const uint8_t SPS, const uint8_t GAIN, const uint8_t LOWPASS)
{
    MAX30003_CNFG_ECG_VALS  vals;
    MAX30003_CNFG_ECG_MASKS masks;

    vals.dhpf = DHPF_HALF;

    // test for invalid lowpass settings (higher lowpass freq requires higher sample rate)
    if((LOWPASS == 2 && SPS > 1) || (LOWPASS == 3 && SPS > 0 )) {
        return TEST_FAILURE;
    }

    switch(SPS) {
        case 0 : vals.rate = RATE_MAX_SPS;
                 break;
        case 1 : vals.rate = RATE_MED_SPS;
                 break;
        case 2 : vals.rate = RATE_MIN_SPS;
                 break;
        default: return TEST_FAILURE;
    }

    switch(GAIN) {
        case 0 : vals.gain = GAIN_20_V;
                 break;
        case 1 : vals.gain = GAIN_40_V;
                 break;
        case 2 : vals.gain = GAIN_80_V;
                 break;
        case 3 : vals.gain = GAIN_160_V;
                 break;
        default: return TEST_FAILURE;
    }

    switch(LOWPASS) {
        case 0 : vals.dlpf = DLPF_BYPASS;
                 break;
        case 1 : vals.dlpf = DLPF_40_HZ;
                 break;
        case 2 : vals.dlpf = DLPF_100_HZ;
                 break;
        case 3 : vals.dlpf = DLPF_150_HZ;
                 break;
        default: return TEST_FAILURE;
    }

    ecg_set_cnfg_ecg(vals, (CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE));

    return TEST_SUCCESS;
}