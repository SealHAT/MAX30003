#include "atmel_start.h"
#include "max30003.h"
//#include "max30003test.h"

#define BURST 0
/*static int32_t ecg_log[ECG_LOG_SZ];*/

// const MAX30003_CNFG_GEN_VALS cnfggen_vals_test = {
//     .rbiasn     = RBIASN_NOT_CONNECTED,
//     .rbiasp     = RBIASP_NOT_CONNECTED,
//     .rbiasv     = RBIASV_100_MOHM,
//     .en_rbias   = ENRBIAS_DISABLED,
//     .vth        = DCLOFFVTH_300_mV,
//     .imag       = DCLOFFIMAG_0_nA,
//     .ipol       = DCLOFFIPOL_P_UP_N_DOWN,
//     .en_dcloff  = ENDCLOFF_DISABLED,
//     .en_ecg     = ENECG_ENABLED,
//     .fmstr      = FMSTR_512_HZ,
//     .en_ulp_lon = ENULPLON_DISABLED
// };

int main(void)
{
    volatile bool result;
	uint16_t count;
    uint16_t size;
	
    result = false;
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

//     result = MAX30003_INIT_TEST_ROUND();
//     delay_ms(1000);
    MAX30003_INFO_VALS info_vals;
	for(;;) {
        ecg_get(&info_vals, REG_INFO);
	}
} 

