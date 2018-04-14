#include "atmel_start.h"
#include "max30003.h"

int main(void)
{
	atmel_start_init();

    struct spi_msg ecg_spi_msg;
    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
    ecg_spi_msg.size  = ECG_BUF_SZ;

    ecg_init_spi(spi_m_sync_transfer, &spi_dev, &ecg_spi_msg);
    ecg_init_csb(gpio_set_pin_level, CS);
    	
	for(;;) {		

	}
} 
