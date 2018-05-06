#include "atmel_start.h"
#include "seal_UTIL.h"
#include "max30003.h"
#include "max30003test.h"
#include "si5351-samd21-minimal.h"

/* Message Strings */
char WELCOME[]       = "Welcome to the SealHAT EKG test suite!\nPlease start the capture to textfile within CoolTerm now!\nBe sure to name your file \"sealtest.txt\" and change your baudrate to max.\n";
char START_TEST[]    = "Please press \"r\" to begin!\n";
char NEXT_TEST[]     = "Please press \"n\" if you are ready to proceed to the next test.\n";
char TEST_COMPLETE[] = "Test complete.\n";
char GOODBYE[]       = "All tests are complete. The device may now be disconnected. Goodbye!\n";
char PASS[]          = "All tests passed!\n";
char FAIL[]          = "One or more tests failed :(\n";

//#define HOTHPITAL (0)
void spi_init();
void fclock_init();

int main(void)
{
    /* VARIABLE DECLARATIONS */
	MAX30003_STATUS_VALS status_vals;
    test_result_t result;
    bool test_complete;
    int  retVal;
    char charBuffer[16];

    /* ATMEL INIT */
    atmel_start_init();
	
	gpio_set_pin_level(CS,true);
	
	i2c_unblock_bus(SDA, SCL);
	
    spi_init();
	
	gpio_set_pin_level(CS,false);
	
	fclock_init();
	
	gpio_set_pin_level(CS,true);
    /* YOUR INIT CODE HERE */
    result          = TEST_FAILURE;
    test_complete   = false;

    /* Set up USB connection */
    /* Wait for USB connection to be made with computer. Must be down to receive (DTR). */
    do { /* NOTHING */ } while (!usb_dtr());
        
    /* Write welcome message to the serial console. If the operation fails, it will continue
     * trying to send until it is successful. */
    do {
        retVal = usb_write((uint8_t *) WELCOME, sizeof(WELCOME));
    } while((retVal != USB_OK) || !usb_dtr());

#ifdef HOTHPITAL
	
    /**********
     * TEST 1 *
     **********/
    do { retVal = usb_write((uint8_t *) START_TEST, sizeof(START_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'r');
    snprintf(charBuffer, 14,"Begin test %1d\n", 1);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 1 GOES HERE */
    result = MAX30003_INIT_TEST();
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 2 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 2);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 2 GOES HERE */
    result = MAX30003_FIFO_TEST();
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 3 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 3);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 3 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 4 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 4);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 4 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 5 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 5);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 5 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 6 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 6);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 6 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 7 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 7);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 7 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 8 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 8);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 8 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /**********
     * TEST 9 *
     **********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 14,"Begin test %1d\n", 9);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 9 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    /***********
     * TEST 10 *
     ***********/
    do { retVal = usb_write((uint8_t *) NEXT_TEST, sizeof(NEXT_TEST)); } while((retVal != USB_OK) || !usb_dtr());
    do { /* NOTHING */ } while(usb_get() != 'n');
    snprintf(charBuffer, 15,"Begin test %1d\n", 10);
    do { retVal = usb_write((uint8_t *) charBuffer, sizeof(charBuffer)); } while((retVal != USB_OK) || !usb_dtr());
    
    /* FUNCTION CALL FOR TEST 10 GOES HERE */
    
    
    do { retVal = usb_write((uint8_t *) TEST_COMPLETE, sizeof(TEST_COMPLETE)); } while((retVal != USB_OK) || !usb_dtr());
    
    

#endif // HOTHPITAL    
    
    /* test 0.1 - setup */
//     result = MAX30003_INIT_TEST_ROUND();
//     delay_ms(1000);

    if(result == true)
    {
        do { retVal = usb_write((uint8_t *) PASS, sizeof(PASS)); } while((retVal != USB_OK) || !usb_dtr());
    }
    else
    {
        do { retVal = usb_write((uint8_t *) FAIL, sizeof(FAIL)); } while((retVal != USB_OK) || !usb_dtr());
    }

    /***********
     * GOODBYE *
     ***********/
    do { retVal = usb_write((uint8_t *) GOODBYE, sizeof(GOODBYE)); } while((retVal != USB_OK) || !usb_dtr());
	
	for(int i = 0; i < ECG_LOG_SZ; i++) {
		ECG_LOG[i] = 0;
	}
	MAX30003_FIFO_VALS vals;
	bool eof = false;
	uint16_t step = 0;
	uint32_t word = 0;
	int32_t  sampv = 0;
	uint32_t sampt = 0;
	ecg_synch();
	delay_ms(1000);
	
	for(;;) {
		if (step < ECG_LOG_SZ) {
			ecg_get_sample(&vals);
				
			switch (vals.etag) {
				case ETAG_VALID_EOF :
				case ETAG_FAST_EOF  :
					eof = true; /* exit, but save the sample as a valid sample */
					vals.etag = (ECGFIFO_ETAG_VAL)( (uint8_t)vals.etag & 0x01);
				case ETAG_VALID     :
				case ETAG_FAST      :
					/* format and store the sample */
					word |= (uint32_t)vals.etag << 0;
					word |= (uint32_t)step      << 3;
					word |= (uint32_t)vals.data << 14;

					ECG_LOG[step] = word;
					
					/* increment, clear, and get next sample */
					step++;
					word = 0x00000000;
					break;
					
				case ETAG_FIFO_OVERFLOW :
					ecg_fifo_reset();
				case ETAG_FIFO_EMPTY    :
					break;
				default :   
					delay_ms(1000); /* TODO error handling */
			}
		} else {
			gpio_toggle_pin_level(LED_BUILTIN);
			delay_ms(250);
			/* [VVVV VVVV VVVV VVVV VVTT TTTT TTTT TEEE] */
			sampt = ((uint32_t)(ECG_LOG[step % ECG_LOG_SZ]) & 0x00003FF8) >> 3;
			sampv = (int32_t)(ECG_LOG[step % ECG_LOG_SZ]);
			sampv = sampv >> 14;
			
			snprintf(charBuffer, 14, "%7li,%4lu\n", sampv, sampt);
			do { retVal = usb_write((uint8_t *)charBuffer, 13); } while((retVal != USB_OK) || !usb_dtr());
			step++;
		}
			
	}
} 

void spi_init()
{
    spi_m_sync_set_mode(&ECG_SPI_DEV_0, SPI_MODE_0);
    spi_m_sync_enable(&ECG_SPI_DEV_0);
    gpio_set_pin_level(CS,true);

    ecg_spi_msg.size  = ECG_BUF_SZ;
    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
}

void fclock_init()
{	
	struct Si5351Frac pll_frac, ms_frac;
	/* I think the adafruit breakout using a 10pF crystal, known 25MHz (default) */
	si5351_init(&wire, SI5351_CRYSTAL_LOAD_10PF, 0);
	
	pll_frac.a = 28;
	pll_frac.b = 7012;
	pll_frac.c = 390625;
	
	ms_frac.a = 21184;
	ms_frac.b = 0;
	ms_frac.c = 16;
	
	/* set the clock to 25 32.768kHz */
	//si5351_set_freq(32768UL, SI5351_CLK0); /* 1MHz min */
	si5351_set_pll(pll_frac, SI5351_PLLA);
	si5351_set_ms(SI5351_CLK0, ms_frac, 0, SI5351_OUTPUT_CLK_DIV_16, 0);
	
	/* (optional) update the output drive power */
	//si5351_drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA);
	
	
}