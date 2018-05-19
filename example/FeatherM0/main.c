#include "atmel_start.h"
#include "seal_UTIL.h"
#include "max30003.h"
#include "max30003test.h"
#include "si5351-samd21-minimal.h"

#define ECG_LOG_SZ	(1024)
int32_t ECG_LOG[ECG_LOG_SZ];

void spi_init();
void fclock_init();
void ecg_testheader();


int main(void)
{
    /* VARIABLE DECLARATIONS */
    int  retVal;
    char charBuffer[30];


    /* ATMEL INIT */
	i2c_unblock_bus(SDA, SCL);
    atmel_start_init();

	/* YOUR INIT CODE HERE */
	spi_init();
	fclock_init();
	ecg_sw_reset();
	delay_ms(1000);


	for(int i = 0; i < ECG_LOG_SZ; i++) {
		ECG_LOG[i] = 0;
	}
	MAX30003_FIFO_VALS vals;
	bool fifo_eof = false;
	bool fifo_err = false;
	bool fifo_emp = false;
	bool fifo_ovf = false;

	uint8_t rate_val, gain_val, lowpass_val;
	uint8_t test_num = 1;
	int32_t step = 0;

	uint32_t word = 0;
	int32_t  sampv = 0;
	uint32_t sampt = 0;

	delay_ms(100);

	ecg_fifo_reset();
	for(;;)
	{
		if(usb_get() == 'n')
		{
			ecg_test_interactive_switch(test_num, &rate_val, &gain_val, &lowpass_val);
		}

		if(gpio_get_pin_level(INT1) == false)
		{
			while (step < ECG_LOG_SZ && fifo_eof == false && fifo_err == false)
			{
				ecg_get_sample(&vals);

				switch (vals.etag)
				{
					case ETAG_VALID_EOF :
					case ETAG_FAST_EOF  :
						fifo_eof = true; /* exit, but save the sample as a valid sample */
						vals.etag = (ECGFIFO_ETAG_VAL)( (uint8_t)vals.etag & 0x01);
					case ETAG_VALID     :
					case ETAG_FAST      :
						/* format and store the sample */
						word |= (uint32_t)vals.etag << 0;
						word |= (uint32_t)step      << 3;
						word |= (uint32_t)vals.data << 14;

						ECG_LOG[step] = word;
						sampt = ((uint32_t)(ECG_LOG[step]) & 0x00003FF8) >> 3;
						sampv = (int32_t)(ECG_LOG[step]);
						sampv = sampv >> 14;

						/* increment, clear, and get next sample */
						step++;
						word = 0x00000000;
						break;

					case ETAG_FIFO_OVERFLOW :
						ecg_synch();
						gpio_toggle_pin_level(LED_BUILTIN);
						fifo_ovf = true;
						break;
					case ETAG_FIFO_EMPTY    :
						fifo_emp = true;
						break;
					default :
						gpio_toggle_pin_level(LED_BUILTIN);
						delay_ms(1000); /* TODO error handling */
						gpio_toggle_pin_level(LED_BUILTIN);
						fifo_err = true;
						break;
				} /* done with single sample */
			} /* done (log full, fifo empty, or error) */

			/* if all samples in fifo were read, print */
			if (fifo_eof == true || step == ECG_LOG_SZ)
			{
				for( int i = 0; i < step; i++)
				{
					sampt = ((uint32_t)(ECG_LOG[i]) & 0x00003FF8) >> 3;
					sampv = (int32_t)(ECG_LOG[i]);
					sampv = sampv >> 14;
					ECG_LOG[i] = 0;
						
					snprintf(charBuffer, 30, "%7li,%4lu,%d,%d,%d\n", sampv, sampt, rate_val, gain_val, lowpass_val);
					do { retVal = usb_write((uint8_t *)charBuffer, 29); } while((retVal != USB_OK) || !usb_dtr());
					/* done printing */
				}
			}
			else if (fifo_err == true)
			{ /* error */
				snprintf(charBuffer, 12, "err=%4lu\n",step);
				do { retVal = usb_write((uint8_t *)charBuffer, 11); } while((retVal != USB_OK) || !usb_dtr());
			}
			else if (fifo_emp == true)
			{ /* empty? */
				snprintf(charBuffer, 12, "emp=%4lu\n",step);
				do { retVal = usb_write((uint8_t *)charBuffer, 11); } while((retVal != USB_OK) || !usb_dtr());
			}
			else if( fifo_ovf == true)
			{
				snprintf(charBuffer, 12, "ovf=%4lu\n",step);
				do { retVal = usb_write((uint8_t *)charBuffer, 11); } while((retVal != USB_OK) || !usb_dtr());
			}
			else
			{
				/* cant be here */
				delay_ms(5000);
			}
			step = 0;
			fifo_err = false;
			fifo_eof = false;
			fifo_emp = false;
			fifo_ovf = false;
			ecg_fifo_reset();
		} /* fifo should be empty, wait until full again */
	} /* forever loop */
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

