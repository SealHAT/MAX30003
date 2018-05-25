#include "atmel_start.h"
#include "seal_UTIL.h"
#include "max30003.h"
#include "max30003test.h"
#include "ecg.h"
#include "si5351-samd21-minimal.h"

/* Buffer for storing ECG samples */
//#define ECG_LOG_SZ	(1221)
//ECG_SAMPLE ECG_LOG[ECG_LOG_SZ];
signed int data[2000];
//MAX30003_FIFO_VALS VALS[ECG_LOG_SZ];//test ecg get sample only
int i;
int n = 0;
/* initializes SPI for the ECG device		*/
void spi_init();	// TODO place in a device header
/* initializes the clock generator module	*/
void fclock_init();	// TODO remove when no longer needed

int main(void)
{
    /* VARIABLE DECLARATIONS */
	config_status t;
    /* ATMEL INIT */
	i2c_unblock_bus(SDA, SCL);	/* unblocks I2C line, remove if not needed */
    atmel_start_init();

	/* YOUR INIT CODE HERE */
	spi_init();		
	fclock_init();
	ecg_sw_reset();
	/* clear the ECG sample log */
//	memset(ECG_LOG, 0, ECG_LOG_SZ);
	memset(data, 0, 1000);
	/*Intilizae the ecg and set for configuration we want*/
	t = ecg_init();

	/*set up for the interrupt pin of ecg to the uc*/

   MAX30003_STATUS_VALS shit;
   uint16_t step=0;
   uint16_t nextstep = 0;
   ecg_get_status(&shit);
   ecg_fifo_reset();
  // ecg_stop_synch();
	for(;;)
	{       
    step = ecg_sampling_process(0,data,1000);
	nextstep = ecg_sampling_process(step,data,1000);
	ecg_switch(ENECG_DISABLED);
	delay_ms(10);
	    
	
	  //  ecg_sampling_process(START_SAMPLING,ECG_LOG,ECG_LOG_SZ);
	    
		 
	

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

	ms_frac.a = 1336;
	ms_frac.b = 0;
	ms_frac.c = 1;

	/* set the clock to 25 32.768kHz */
	si5351_set_pll(pll_frac, SI5351_PLLA);
	si5351_set_ms(SI5351_CLK0, ms_frac, 0, SI5351_OUTPUT_CLK_DIV_16, 0);
    si5351_set_correction(0);

	/* (optional) update the output drive power */
	//si5351_drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA);
}

