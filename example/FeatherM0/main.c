#include "atmel_start.h"
#include "max30003.h"

#define BURST 0
/*static int32_t ecg_log[ECG_LOG_SZ];*/

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

int main(void)
{
    MAX30003_CNFG_GEN_VALS cnfggen_vals;
    MAX30003_CNFG_EMUX_VALS emux_vals;
    MAX30003_FIFO_VALS fifo;
    uint32_t word;
	uint16_t count;
    uint16_t size;
	
	count = 0;
    size = ECG_LOG_SZ;
	atmel_start_init();
	
	for(int i = 0; i < ECG_LOG_SZ; i++) {
		ECG_LOG[i] = 0;
	}

    spi_m_sync_set_mode(&ECG_SPI_DEV_0, SPI_MODE_0);
    spi_m_sync_enable(&ECG_SPI_DEV_0);

    gpio_set_pin_level(CS,true);

    ecg_spi_msg.rxbuf = ECG_BUF_I;
    ecg_spi_msg.txbuf = ECG_BUF_O;
    ecg_spi_msg.size  = ECG_BUF_SZ;

    ecg_sw_reset();
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
    delay_ms(1000);
    ecg_synch();
    delay_ms(50);
	for(;;) {
        #if BURST == 1
//         if(count + size <= ECG_LOG_SZ) {
//             count += ecg_get_sample_burst(ECG_LOG, count, size);
//             size -= count;
//         } else {
//             delay_ms(1000);
//         }
        #else
        if(count < ECG_LOG_SZ) {
            word = 0x000000;
            ecg_get_sample(&fifo);
            delay_ms(1);
            if(fifo.etag == ETAG_FIFO_EMPTY) {
                /* do nothing */
            } else if (fifo.etag == ETAG_FIFO_OVERFLOW) {
                ecg_synch();
            } else if (fifo.etag == _ETAG_RESERVED1 || fifo.etag == _ETAG_RESERVED2) {
                delay_ms(1000);
            } else {
                word |= (uint32_t)((fifo.etag & 0x01)    << 0);
                word |= (uint32_t)(count                 << 3);
                word |= (uint32_t)(fifo.data             << 14);
                ECG_LOG[count++] = (int32_t)word;
            }
        } else {
            delay_ms(1000);
        }
        #endif
	}
} 

