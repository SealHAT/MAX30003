/* MIT License
 *
 * Copyright (c) 2018 SealHAT: Seal Heart and Activity Tracker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MAX30003_H
#define MAX30003_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <stdbool.h>
#include <stdint.h>

#include "max30003types.h"	/* typedefs for the MAX30003 registers	*/
#include "driver_init.h"	/* "Atmel Start" files for spi			*/

/* MACROS for applying a read/write bit and shift to register address values */
#define ECG_REG_R(REG)  ( (uint8_t)(REG << 1) | MAX30003_R_INDICATOR )
#define ECG_REG_W(REG)  ( (uint8_t)(REG << 1) | MAX30003_W_INDICATOR )

#define ECG_BUF_SZ      (12)	/* SPI buffer size	*/
#define ECG_BUF_CLR     (0x00)	/* clear byte		*/

// TODO activate these and change ecg_spi_msg size as needed for static memory optimization */
// #define ECG_CMND_SZ		(1)
// #define ECG_DATA_SZ		(3)

/* SPI variables */
extern struct spi_xfer ecg_spi_msg;		/* SPI message struct	*/
extern uint8_t	ECG_BUF_I[ECG_BUF_SZ];	/* SPI input buffer		*/
extern uint8_t	ECG_BUF_O[ECG_BUF_SZ];	/* SPI output buffer	*/

enum ECG_WORD_POS {
    ECG_CMND_POS = 0,
    ECG_DATA_POS = 1
};

// TODO consider switching to bitfields
/* typedef to enforce size of SPI message components */
typedef struct MAX30003_DATA_t { uint8_t byte[3]; } MAX30003_DATA_t;
typedef uint8_t MAX30003_ADDR_t;

/* ECG_SAMPLE type
 *	struct for storing a bit-mapped ECG sample in a 32-bit number
 *	packing and bit order is ignored as the total struct size is 32-bits
 */
typedef struct ECG_SAMPLE {
	uint8_t		tag:3;		/* ETAG data from the ECG_FIFO	*/
	int32_t		data:18;	/* voltage of the sample		*/
	uint16_t	step:11;	/* time step of the sample		*/
} ECG_SAMPLE;

/* MAX30003_MSG type
 *	structure for storing a message to send/receive over SPI
 */
typedef struct MAX30003_MSG {
    uint8_t command;		/* address of the register to communicate with	*/
    MAX30003_DATA_t data;	/* data word to send to the addresses			*/
} MAX30003_MSG;

// TODO consider abstracting these again for portability
/* ASF function pointers for using SAML21 calls without cluttering the MAX30003 namespace */
//int32_t (*ecg_spi_xfer)(void * descriptor, const void *buffer);		/* spi_xfer */
//void    (*ecg_set_csb_level)(const uint8_t pin, const bool level);	/* gpio_set_pin_level */

/* initialization functions, run before using device */
//void ecg_init_spi(void *spi_desc, const void *spi_msg, uint32_t* spi_msg_sz);
//void ecg_init_csb(const uint8_t ecg_csb_pin);

// TODO sort/rename here
void ecg_fifo_reset();
void ecg_sw_reset();
void ecg_synch();
void ecg_sw_reset();


/* MAX30003 register GET functions ************************************************************************
 *	each function reads the values from a register of the MAX30003 ECG device
 *  INPUTS: (use enumerated types)
 *		*vals	= pointer to a value struct to populate with the register's current values
 *	OUTPUTS:
 *		*vals	= updated with current register values
 *********************************************************************************************************/
void ecg_get_sample		(MAX30003_FIFO_VALS			*vals);
void ecg_get_status		(MAX30003_STATUS_VALS		*vals);
void ecg_get_en_int		(MAX30003_EN_INT_VALS		*vals);
void ecg_get_en_int2	(MAX30003_EN_INT_VALS		*vals);
void ecg_get_mngr_int	(MAX30003_MNGR_INT_VALS		*vals);
void ecg_get_mngr_dyn	(MAX30003_MNGR_DYN_VALS		*vals);
void ecg_get_cnfg_gen	(MAX30003_CNFG_GEN_VALS		*vals);
void ecg_get_cnfg_cal	(MAX30003_CNFG_CAL_VALS		*vals);
void ecg_get_cnfg_emux	(MAX30003_CNFG_EMUX_VALS	*vals);
void ecg_get_cnfg_ecg	(MAX30003_CNFG_ECG_VALS		*vals);

/* ecg_get_sample_burst *************************************************************************************
 *	Reads from the MAX30003 ECG sample fifo while there is valid data in the fifo
 *	INPUTS:
 *		*log	= pointer to an array of sample structs to hold the sample reading with data, step, tag
 *		SIZE	= constant size of the log array
 *	OUTPUTS:
 *		*log	= updated with sampled values
 *	RETURNS:
 *		the number of samples recorded into the log array
 ***********************************************************************************************************/
uint16_t ecg_get_sample_burst(ECG_SAMPLE *log, const uint16_t SIZE); /* returns number of samples recorded */



/* MAX30003 register SET functions ************************************************************************
 *	each function writes to a command register of the MAX30003 ECG device
 *  INPUTS: (use enumerated types)
 *		VALS	= constant register value struct
 *		MASKS	= bitwise OR of the the fields that should change
 *	OUTPUTS:
 *		n/a
 *********************************************************************************************************/
void ecg_set_en_int		(const MAX30003_EN_INT_VALS		VALS, const MAX30003_EN_INT_MASKS		MASKS);
void ecg_set_en_int2	(const MAX30003_EN_INT_VALS		VALS, const MAX30003_EN_INT_MASKS		MASKS);
void ecg_set_mngr_int	(const MAX30003_MNGR_INT_VALS	VALS, const MAX30003_MNGR_INT_MASKS		MASKS);
void ecg_set_mngr_dyn	(const MAX30003_MNGR_DYN_VALS	VALS, const MAX30003_MNGR_DYN_MASKS		MASKS);
void ecg_set_cnfg_gen	(const MAX30003_CNFG_GEN_VALS	VALS, const MAX30003_CNFG_GEN_MASKS		MASKS);
void ecg_set_cnfg_cal	(const MAX30003_CNFG_CAL_VALS	VALS, const MAX30003_CNFG_CAL_MASKS		MASKS);
void ecg_set_cnfg_emux	(const MAX30003_CNFG_EMUX_VALS	VALS, const MAX30003_CNFG_EMUX_MASKS	MASKS);
void ecg_set_cnfg_ecg	(const MAX30003_CNFG_ECG_VALS	VALS, const MAX30003_CNFG_ECG_MASKS		MASKS);
void ecg_set_cnfg_rtor1	(const MAX30003_CNFG_RTOR1_VALS VALS, const MAX30003_CNFG_RTOR1_MASKS	MASKS);
void ecg_set_cnfg_rtor2	(const MAX30003_CNFG_RTOR2_VALS VALS, const MAX30003_CNFG_RTOR2_MASKS	MASKS);

/* MAX30003 register DECODE functions *********************************************************************
 *	internal register functions for shifting and masking values out of words and updating value structs
 *  INPUTS: (use enumerated types)
 *		*vals	= pointer to a value struct to populate with the decoded data
 *		DATA	= 32-bits of data received from the ECG device
 *	OUTPUTS:
 *		*vals	= updated with current register values
 *********************************************************************************************************/
void ecg_decode_status		(MAX30003_STATUS_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_en_int		(MAX30003_EN_INT_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_mngr_int	(MAX30003_MNGR_INT_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_mngr_dyn	(MAX30003_MNGR_DYN_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_info		(MAX30003_INFO_VALS			*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_gen	(MAX30003_CNFG_GEN_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_cal	(MAX30003_CNFG_CAL_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_emux	(MAX30003_CNFG_EMUX_VALS	*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_ecg	(MAX30003_CNFG_ECG_VALS		*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_rtor1	(MAX30003_CNFG_RTOR1_VALS	*vals, const MAX30003_DATA_t DATA);
void ecg_decode_cnfg_rtor2	(MAX30003_CNFG_RTOR2_VALS	*vals, const MAX30003_DATA_t DATA);
void ecg_decode_ecg_fifo	(MAX30003_FIFO_VALS			*vals, const MAX30003_DATA_t DATA);
void ecg_decode_rtor		(MAX30003_RTOR_VALS			*vals, const MAX30003_DATA_t DATA);

/* MAX30003 register ENCODE functions *********************************************************************
 *	internal register functions for shifting and masking values into words from value structs
 *  INPUTS: (use enumerated types)
 *		VALS	= structure of values to mask into a 32-bit data word
 *		*data	= 32-bit data word representing values to send to the ECG device
 *	OUTPUTS:
 *		*data	= data word updated with order bits (MSB -> LSB)
 *********************************************************************************************************/
void ecg_encode_en_int		(const MAX30003_EN_INT_VALS		VALS, MAX30003_DATA_t *data);
void ecg_encode_mngr_int	(const MAX30003_MNGR_INT_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_mngr_dyn	(const MAX30003_MNGR_DYN_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_gen	(const MAX30003_CNFG_GEN_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_cal	(const MAX30003_CNFG_CAL_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_emux	(const MAX30003_CNFG_EMUX_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_ecg	(const MAX30003_CNFG_ECG_VALS	VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_rtor1	(const MAX30003_CNFG_RTOR1_VALS VALS, MAX30003_DATA_t *data);
void ecg_encode_cnfg_rtor2	(const MAX30003_CNFG_RTOR2_VALS	VALS, MAX30003_DATA_t *data);

/* internal helper functions */
void ecg_clear_ibuf();
void ecg_clear_obuf();
void ecg_clear_iobuf();
/* ecg_mask ***********************************************************************************************
 *	Endian safe operation that builds a data word by combining old register values with values to update
 *	INPUTS: (use enumerated types)
 *		*new_vals	= the register values to include in the data word
 *		OLD_VALS	= constant register values currently programmed to the device
 *		MASKS		= bitwise OR of the values that should be updated
 *	OUTPUTS:
 *		*new_vals	= updated data word with the old values, overwritten with new values where requested
 **********************************************************************************************************/
void ecg_mask(MAX30003_DATA_t *new_vals, const MAX30003_DATA_t OLD_VALS, const uint32_t MASKS);

uint8_t ecg_spi_read(MAX30003_MSG *msg);
uint8_t ecg_spi_write(MAX30003_MSG *msg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003_H */
