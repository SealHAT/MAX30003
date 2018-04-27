#include "atmel_start.h"
#include "max30003.h"

void ecg_init(struct spi_m_sync_descriptor *_ecg_spi_descriptor, struct spi_xfer *_ecg_spi_msg, const uint8_t _CS)
{
	/* enable the spi descriptor for the ecg */
	spi_m_sync_set_mode(_ecg_spi_descriptor, SPI_MODE_0);
	spi_m_sync_enable(_ecg_spi_descriptor);
	
	/* associate the transfer and chip select functions to their ecg counterparts */
	ecg_spi_xfer		= &spi_m_sync_transfer;
	ecg_set_csb_level	= &gpio_set_pin_level;
	
	/* associate the spi transfer buffers */
    _ecg_spi_msg->size  = ECG_BUF_SZ;
	_ecg_spi_msg->rxbuf = ECG_BUF_I;
	_ecg_spi_msg->txbuf = ECG_BUF_O;
	
	
	/* associate the buffers and chip variables select to their ecg counterparts */
	ecg_init_spi(_ecg_spi_descriptor, _ecg_spi_msg);
	ecg_init_csb(_CS);
}

int main(void)
{
	struct spi_xfer ecg_spi_msg;
    //MAX30003_CNFG_GEN_VALS vals;
    MAX30003_INFO_VALS  info_vals;
	
	atmel_start_init();

    /* TODO abstract to ecg_init_spi */
    spi_m_sync_set_mode(&ECG_SPI_DEV_0, SPI_MODE_0);
    spi_m_sync_enable(&ECG_SPI_DEV_0);

    gpio_set_pin_level(CS,true);

	ecg_init(&ECG_SPI_DEV_0, &ecg_spi_msg, CS);    
        	
	for(;;) {		
        ecg_get(&info_vals, REG_INFO);
        delay_ms(1000);
	}
} 
