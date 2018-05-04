#include "atmel_start.h"
#include "max30003.h"

#define ECG_LOG_SZ 1024
static int32_t ecg_log[ECG_LOG_SZ];

const MAX30003_CNFG_GEN_VALS cnfggen_vals_test = {
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

int32_t _spi_m_sync_transfer_voidparam(void * descriptor, const void * buffer)
{
    int32_t r = spi_m_sync_transfer((struct spi_m_sync_descriptor *)descriptor, (const struct spi_xfer*) buffer);
    return r;
}

void ecg_init(struct spi_m_sync_descriptor *_ecg_spi_descriptor, struct spi_xfer *_ecg_spi_msg, const uint8_t _CS)
{
    uint32_t *sz_p;
	/* enable the spi descriptor for the ecg */
	spi_m_sync_set_mode(_ecg_spi_descriptor, SPI_MODE_0);
	spi_m_sync_enable(_ecg_spi_descriptor);
	
	/* associate the transfer and chip select functions to their ecg counterparts */
	ecg_spi_xfer		= &_spi_m_sync_transfer_voidparam;
	ecg_set_csb_level	= &gpio_set_pin_level;
	
	/* associate the spi transfer buffers */
    _ecg_spi_msg->size  = ECG_BUF_SZ;
	_ecg_spi_msg->rxbuf = ECG_BUF_I;
	_ecg_spi_msg->txbuf = ECG_BUF_O;
    sz_p = &(_ecg_spi_msg->size);
	
	/* associate the buffers and chip variables select to their ecg counterparts */
	ecg_init_spi(_ecg_spi_descriptor, _ecg_spi_msg, sz_p);
	ecg_init_csb(_CS);
}

int main(void)
{
	struct spi_xfer ecg_spi_msg;
    MAX30003_CNFG_GEN_VALS cnfggen_vals;
    MAX30003_CNFG_EMUX_VALS emux_vals;
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
        	
	ecg_get(&cnfggen_vals, REG_CNFG_GEN);
	delay_ms(1000);

	cnfggen_vals.en_ecg = ENECG_ENABLED;

	ecg_set_cnfg_gen(cnfggen_vals_test, CNFGGEN_EN_ECG);
	delay_ms(1000);
    ecg_get_cnfg_gen(&cnfggen_vals);
    delay_ms(1000);

    if(cnfggen_vals.en_ecg != cnfggen_vals_test.en_ecg) {
        delay_ms(1000);
    }
    emux_vals.caln_sel = CALNSEL_IN_VCALN;
    emux_vals.calp_sel = CALPSEL_IN_VCALP;
    ecg_set_cnfg_emux(emux_vals, CNFGEMUX_CALN_SEL | CNFGEMUX_CALP_SEL);

    ecg_synch();
//     count = ecg_get_sample_burst((uint32_t*)ecg_log, ECG_LOG_SZ);
//     delay_ms(1000);
// 
//     ecg_fifo_reset();
    count = 0;
	for(;;) {
		if (count < ECG_LOG_SZ) {
			ecg_get_sample(&fifo);
			ecg_log[count] = (fifo.data << 14) | (fifo.etag << 3) | fifo.ptag;
			count++;
		} else {
            delay_ms(1000);
        }
		
	}
} 
