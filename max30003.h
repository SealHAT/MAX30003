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
#endif
// TODO check endianness

/**
 * REG addresses for the MAX30003 biopotential AFE
 **/
typedef enum {
    NO_OP          = 0x00,  /* RW - no internal effect. DOUT = 0 during R, W ignored */
    STATUS         = 0x01,  /* R  - */
    EN_INT         = 0x02,  /* RW - */
    EN_INT2        = 0x03,  /* RW - */
    MNGR_INT       = 0x04,  /* RW - */
    MNGR_DYN       = 0x05,  /* RW - */
    SW_RST         = 0x08,  /* W  - */
    SYNCH          = 0x09,  /* W  - */
    FIFO_RST       = 0x0A,  /* W  - */
    INFO           = 0x0F,  /* R  - */
    CNFG_GEN       = 0x10,  /* RW - */
    CNFG_CAL       = 0x12,  /* RW - */
    CNFG_EMUX      = 0x14,  /* RW - */
    CNFG_ECG       = 0x15,  /* RW - */
    CNFG_RTOR1     = 0x1D,  /* RW - */
    CNFG_RTOR2     = 0x1E,  /* RW - */
    ECG_FIFO_BURST = 0x20,  /* R+ - */
    ECG_FIFO       = 0x21,  /* R  - */
    RTOR           = 0x25,  /* R  - */
    NO_OP2         = 0x7F   /* RW - no internal effect. DOUT = 0 during R, W ignored */
} MAX30003_REG;

/**
 * REG_STATUS data structure of configurable bits
 **/
typedef struct {
    uint32_t ldoff_nl   : 1;
    uint32_t ldoff_nh   : 1;
    uint32_t ldoff_pl   : 1;
    uint32_t ldoff_ph   : 1;
    uint32_t reserved1  : 8;
    uint32_t dcloffint  : 1;
    uint32_t fstint     : 1;
    uint32_t eovf       : 1;
    uint32_t eint       : 1;
} MAX30003_REG_STATUS;

/**
 * DATA word to an SPI message for the MAX30003
 **/
typedef union {
    MAX30003_REG_STATUS REG_STATUS;
} MAX30003_DATA_WORD;

#ifdef __cplusplus
}
#endif
