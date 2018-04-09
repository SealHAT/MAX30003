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

typedef enum {
    LDOFF_NL    = 0x000001,
    LDOFF_NH    = 0x000002,
    LDOFF_PL    = 0x000004,
    LDOFF_PH    = 0x000008,
    PLLINT      = 0x000100,
    SAMP        = 0x000200,
    RRINT       = 0x000400,
    LONINT      = 0x000800,
    DCLOFFINT   = 0x100000,
    FSTINT      = 0x200000,
    EOVF        = 0x400000,
    EINT        = 0x800000,
    RESERVED    = 0x0FF0F0,
} MAX30003_STATUS_MASKS;

/***
 * EN_INT register's masks and values
 ***/
typedef enum {
    INTB_TYPE   = 0x000003,
    EN_PLLINT   = 0x000100,
    EN_SAMP     = 0x000200,
    EN_RRINT    = 0x000400,
    EN_LONINT   = 0x000800,
    EN_DCLOFFINT= 0x100000,
    EN_FSTINT   = 0x200000,
    EN_EOVF     = 0x400000,
    EN_EINT     = 0x800000
} MAX30003_EN_INT_MASKS;

typedef enum {
    DISABLED    = 0,
    CMOS_DRIVER = 1,
    NMOS_DRIVER = 2,
    NMOS_WITH_PU= 3
} MAX30003_EN_INT_INTB_VAL;

// TODO add ENABLE,DISABLE enums for the EN_* fields

/***
 * MNG_INT register's masks and values
 ***/
typedef enum {
    SAMP_IT     = 0x000003,
    CLR_SAMP    = 0x000004,
    CLR_RRINT   = 0x000030,
    CLR_FAST    = 0x000040,
    EFIT        = 0xF80000,
    RESERVED    = 0x07FF88
} MAX30003_MNGR_INT_MASKS;

typedef enum {
    EVERY_INST  = 0,
    EVERY_2ND   = 1,
    EVERY_4TH   = 2,
    EVERY_16TH  = 3
} MAX30003_MNGR_INT_SAMP_IT_VAL;

typedef enum {
    CLEAR_ON_READ   = 0,
    SELF_CLEAR      = 1
} MAX30003_MNGR_INT_CLR_SAMP_VAL;

typedef enum {
    CLEAR_ON_STATUS = 0,
    CLEAR_ON_RTOR   = 1,
    SELF_CLEAR      = 2,
    RESERVED        = 3
} MAX30003_MNGR_INT_CLR_RRINT_VAL;

typedef enum {
    CLEAR_ON_FAST   = 0,
    CLEAR_ON_STATUS = 1
} MAX30003_MNGR_INT_CLR_FAST_VAL;

// TODO enum for 0000 = 1 to 1111 = 32 to enforce "off-by-one" behaviour
typedef uint32_t MAX30003_MNGR_INT_EFIT_VAL;

/***
 * MNG_DYN register's masks and values
 ***/
typedef enum {
    FAST        = 0xC00000,
    FAST_TH     = 0x3F0000,
    RESERVED    = 0x00FFFF
} MAX30003_MNGR_DYN_MASKS;

typedef enum {
    NORMAL_MODE = 0,
    MANUAL_FAST = 1,
    AUTO_FAST   = 2,
    RESERVED    = 3
} MAX30003_MNGR_DYN_FAST_VAL;

//TODO SW_RST, SYNCH, FIFO_RST

/***
 * INFO register's masks and values
 ***/
typedef enum {
    REV_ID      = 0x0F0000,
    RESERVED    = 0x00CFFF,
    REQUIRED    = 0x503000
} MAX30003_INFO_MASKS;

/***
 * CNFG_GEN register's masks and values
 ***/
typedef enum {
    RBIASN      = 0x000001,
    RBIASP      = 0x000002,
    RBIASV      = 0x00000C,
    EN_RBIAS    = 0x000030,
    VTH         = 0x0000C0,
    IMAG        = 0x000700,
    IPOL        = 0x000800,
    EN_DCLOFF   = 0x003000,
    EN_ECG      = 0x080000,
    FMSTR       = 0x300000,
    EN_ULP_LON  = 0xC00000,
    RESERVED    = 0x07C000
} MAX30003_CNFG_GEN_MASKS;

#ifdef __cplusplus
}
#endif
