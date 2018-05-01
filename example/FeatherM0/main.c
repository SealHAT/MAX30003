#include "atmel_start.h"
#include "max30003.h"

#define ECG_LOG_SZ 2048
static uint32_t ecg_log[ECG_LOG_SZ];

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
    MAX30003_CNFG_GEN_VALS vals;
	MAX30003_FIFO_VALS fifo;
	
	int count;
	
	count = 0;
	atmel_start_init();
	
	for(int i = 0; i < ECG_LOG_SZ; i++) {
		ecg_log[i] = 0;
	}

    /* TODO abstract to ecg_init_spi */
    spi_m_sync_set_mode(&ECG_SPI_DEV_0, SPI_MODE_0);
    spi_m_sync_enable(&ECG_SPI_DEV_0);

    gpio_set_pin_level(CS,true);

	ecg_init(&ECG_SPI_DEV_0, &ecg_spi_msg, CS);    
        	
	ecg_get(&vals, REG_CNFG_GEN);
	delay_ms(1000);

	vals.en_ecg = ENECG_ENABLED;
	ecg_set_cnfg_gen(vals, CNFGGEN_EN_ECG);
	delay_ms(1000);
    ecg_get_cnfg_gen(&vals);
    delay_ms(1000);
    ecg_fifo_reset();
	for(;;) {
		if (count < ECG_LOG_SZ) {
			ecg_get_sample(&fifo);
			ecg_log[count] = (fifo.data << 6) | (fifo.etag << 3) | fifo.ptag;
			count++;
		} else {
            delay_ms(1000);
        }
		
	}
} 
