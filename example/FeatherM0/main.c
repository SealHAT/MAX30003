#include "atmel_start.h"
#include "seal_UTIL.h"
#include "max30003.h"
#include "max30003test.h"
#include "ecg.h"
#include "si5351-samd21-minimal.h"
#include "max30003test.h"

#include <stdio.h>

/* Buffer for storing ECG samples */
#define ECG_FIFO_SZ (24)
#define ECG_LOG_SZ	(ECG_DATA_SZ * ECG_FIFO_SZ)
ECG_SAMPLE ECG_LOG[ECG_LOG_SZ];

#define CNFGGEN_DEFAULT_MASK (CNFGGEN_EN_ECG)
#define CNFGECG_DEFAULT_MASK (CNFGECG_DLPF|CNFGECG_DHPF|CNFGECG_GAIN|CNFGECG_RATE)
#define MNGRINT_DEFAULT_MASK (MNGRINT_EFIT)
#define ENINT1_DEFUALT_MASK  (ENINT_INTB_TYPE|ENINT_EN_EINT)
#define ENINT2_DEFUALT_MASK  (ENINT_INTB_TYPE|ENINT_EN_LONINT)

/* initializes SPI for the ECG device		*/
void spi_init();	// TODO place in a device header
int32_t ecg_init();

int main(void)
{
    /* VARIABLE DECLARATIONS */
    int         retval;
    char        char_buf[40];
    uint16_t    log_count;
    MAX30003_FIFO_VALS samp;
    
    /* clear the ECG sample log */
    memset(ECG_LOG, 0, ECG_LOG_SZ);

    /* ATMEL INIT */
	i2c_unblock_bus(SDA, SCL);	/* unblocks I2C line, remove if not needed */
    atmel_start_init();

	/* YOUR INIT CODE HERE */
	spi_init();
    ecg_sw_reset();
    delay_ms(500);
    //ecg_init();
    MAX30003_INIT_TEST_ROUND();
    
    gpio_set_pin_level(INT1, true);
	ecg_fifo_reset();
	
	for(count = 0;count<313;)
	{
        /* wait for interrupt */
        if (gpio_get_pin_level(INT1) == false) {
            //ecg_get_sample(&samp);
            log_count = ecg_get_sample_burst(ECG_LOG, ECG_LOG_SZ);
            
            for(int i = 0; i < log_count; i++) {
                sprintf(char_buf, "%7d,%4d,%d\n", ECG_LOG[i].data, ECG_LOG[i].step, ECG_LOG[i].tag);
                do { retval = usb_write((uint8_t *)char_buf, 15); } while((retval != USB_OK) || !usb_dtr());    
            }
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

int32_t ecg_init()
{
    MAX30003_VALS   old_vals;
    MAX30003_VALS   new_vals;
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    
    new_vals.cnfg_gen.rbiasn       = RBIASN_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasp       = RBIASP_NOT_CONNECTED;
    new_vals.cnfg_gen.rbiasv       = RBIASV_100_MOHM;
    new_vals.cnfg_gen.en_rbias     = ENRBIAS_DISABLED;
    new_vals.cnfg_gen.en_dcloff    = ENDCLOFF_DISABLED;
    new_vals.cnfg_gen.en_ecg       = ENECG_ENABLED;
    new_vals.cnfg_gen.fmstr        = FMSTR_512_HZ;
    
    ecg_set_cnfg_gen(new_vals.cnfg_gen, CNFGGEN_DEFAULT_MASK);
    ecg_get_cnfg_gen(&old_vals.cnfg_gen);
    /* TODO - check vals */
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.cnfg_ecg.dlpf = DLPF_40_HZ;
    new_vals.cnfg_ecg.dhpf = DHPF_HALF;
    new_vals.cnfg_ecg.gain = GAIN_20_V;
    new_vals.cnfg_ecg.rate = RATE_MIN_SPS;
    
    ecg_set_cnfg_ecg(new_vals.cnfg_ecg, CNFGECG_DEFAULT_MASK);
    ecg_get_cnfg_ecg(&old_vals.cnfg_ecg);
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.mngr_int.efit = EFIT_AS_24;
    
    ecg_set_mngr_int(new_vals.mngr_int, MNGRINT_DEFAULT_MASK);
    ecg_get_mngr_int(&old_vals.mngr_int);
    
    memset(&new_vals, 0, MAX30003_DATA_BYTES);
    new_vals.en_int.en_eint    = ENINT_ENABLED;
    new_vals.en_int.intb_type  = INTBTYPE_NMOS_WITH_PU;
    
    ecg_set_en_int(new_vals.en_int, ENINT1_DEFUALT_MASK);
    ecg_get_en_int(&old_vals.en_int);
    
    return 0;
}