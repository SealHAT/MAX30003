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

#include <stdbool.h>
#include <stdint.h>

#include "max30003types.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplu


typedef struct MAX30003_DATA_t { char byte[3]; } MAX30003_DATA_t;
typedef char MAX30003_ADDR_t;

typedef struct MAX30003_MSG
{
    uint8_t command;
    uint8_t data[3];
} MAX30003_MSG;

void ecg_init_spi( int32_t(*spi_xfer_function)(void *, void *), void *ecg_spi_desc);
void ecg_init_csb( void(*csb_pin_level_function)(const uint8_t , const bool), const uint8_t ecg_csb_pin);

uint8_t ecg_write(MAX30003_MSG msg);


MAX30003_DATA_t ecg_set_cnfg_gen(MAX30003_CNFG_GEN_VALS vals);

void ecg_read_cnfg_gen(MAX30003_CNFG_GEN_VALS *vals);

void ecg_write_cnfg_gen(MAX30003_CNFG_GEN_MASKS MASKS, const MAX30003_CNFG_GEN_VALS VALS);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MAX30003_H */
