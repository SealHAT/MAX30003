#include "atmel_start.h"
#include "seal_UTIL.h"
#include "max30003.h"
#include "max30003test.h"
#include "ecg.h"
#include "si5351-samd21-minimal.h"

/* Buffer for storing ECG samples */
#define ECG_LOG_SZ	(200)
signed int data[ECG_LOG_SZ];

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
	memset(data, 0, sizeof(data));
	/*Initialize the ecg and set for configuration we want*/
	t = ecg_init();
//	t = ecg_fifo_thres(EFIT_AS_16);
	/*set up the interrupt pin, i set up ENINT as interrupt Pin 1, with default threshold 16, you can use func config_status ecg_fifo_thres(MNGRINT_EFIT_VAL vals) to setup your own thresholds(see ecg.h)*/

   uint16_t step=0;
   uint16_t nextstep = 0;
   MAX30003_STATUS_VALS shit;
   ecg_get_status(&shit);
 //  delay_ms(100);
	for(;;)
	{
	/*start sampling the data for 1000 sample when there was an interrupt*/
	if(gpio_get_pin_level(INT1)==false){       
    step = ecg_sampling_process(0,data,200);
	/*keep sampling*/
/*	nextstep = ecg_sampling_process(step,data,1000);//make sure the size parameter did not go beyond 1000
	nextstep = ecg_sampling_process(nextstep+step,data,1000);
	nextstep = ecg_sampling_process(nextstep*2+step,data,1000);
	nextstep = ecg_sampling_process(nextstep*3+step,data,800);//make sure the available place for us to store equal to size of storage array - 200;
	/*we can disable ecg for some time if necessary and reopen it*/
	}
	ecg_get_status(&shit);
	memset(data, 0, sizeof(data));//clear the storage array, when in state machine, we should put the data into storage and then clear it;

	
	    
		 
	

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

