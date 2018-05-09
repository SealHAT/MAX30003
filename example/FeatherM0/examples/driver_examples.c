/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using analog_in to generate waveform.
 */
void analog_in_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&analog_in, 0);

	while (1) {
		adc_sync_read_channel(&analog_in, 0, buffer, 2);
	}
}

/* CRC Data in flash */
COMPILER_ALIGNED(4)
static const uint32_t crc_datas[] = {0x00000000,
                                     0x11111111,
                                     0x22222222,
                                     0x33333333,
                                     0x44444444,
                                     0x55555555,
                                     0x66666666,
                                     0x77777777,
                                     0x88888888,
                                     0x99999999};

/**
 * Example of using hash_chk to Calculate CRC32 for a buffer.
 */
void hash_chk_example(void)
{
	/* The initial value used for the CRC32 calculation usually be 0xFFFFFFFF,
	 * but can be, for example, the result of a previous CRC32 calculation if
	 * generating a common CRC32 of separate memory blocks.
	 */
	uint32_t crc = 0xFFFFFFFF;
	uint32_t crc2;
	uint32_t ind;

	crc_sync_enable(&hash_chk);
	crc_sync_crc32(&hash_chk, (uint32_t *)crc_datas, 10, &crc);

	/* The read value must be complemented to match standard CRC32
	 * implementations or kept non-inverted if used as starting point for
	 * subsequent CRC32 calculations.
	 */
	crc ^= 0xFFFFFFFF;

	/* Calculate the same data with subsequent CRC32 calculations, the result
	 * should be same as previous way.
	 */
	crc2 = 0xFFFFFFFF;
	for (ind = 0; ind < 10; ind++) {
		crc_sync_crc32(&hash_chk, (uint32_t *)&crc_datas[ind], 1, &crc2);
	}
	crc2 ^= 0xFFFFFFFF;

	/* The calculate result should be same. */
	while (crc != crc2)
		;
}

void wire_example(void)
{
	struct io_descriptor *wire_io;

	i2c_m_sync_get_io_descriptor(&wire, &wire_io);
	i2c_m_sync_enable(&wire);
	i2c_m_sync_set_slaveaddr(&wire, 0x12, I2C_M_SEVEN);
	io_write(wire_io, (uint8_t *)"Hello World!", 12);
}

/**
 * Example of using ECG_SPI_DEV_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_ECG_SPI_DEV_0[12] = "Hello World!";

void ECG_SPI_DEV_0_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&ECG_SPI_DEV_0, &io);

	spi_m_sync_enable(&ECG_SPI_DEV_0);
	io_write(io, example_ECG_SPI_DEV_0, 12);
}

void delay_example(void)
{
	delay_ms(5000);
}

static struct timer_task TIMER_0_task1, TIMER_0_task2;

/**
 * Example of using TIMER_0.
 */
static void TIMER_0_task1_cb(const struct timer_task *const timer_task)
{
}

static void TIMER_0_task2_cb(const struct timer_task *const timer_task)
{
}

void TIMER_0_example(void)
{
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	TIMER_0_task2.interval = 200;
	TIMER_0_task2.cb       = TIMER_0_task2_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
}
