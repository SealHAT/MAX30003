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

#ifndef MAX30003TYPES_H
#define MAX30003TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX30003_W_INDICATOR    (0)
#define MAX30003_R_INDICATOR    (1)

// TODO check endianness
// TODO macro for WRITE/READ on ADDRESSES ie:(REG << 1 | R)
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
    INTBTYPE_DISABLED    = 0,   /* Disabled (three-state) */
    INTBTYPE_CMOS_DRIVER = 1,   /* CMOS Driver */
    INTBTYPE_NMOS_DRIVER = 2,   /* Open-Drain NMOS Driver */
    INTBTYPE_NMOS_WITH_PU= 3    /* Open-Drain NMOS Driver w/ Internal 125k Pullup */
} MAX30003_ENINT_INTBTYPE_VAL;

typedef enum {
    ENPLLINT_DISABLED   = 0,
    ENPLLINT_ENABLED    = 1
} MAX30003_ENINT_ENPLLINT_VAL;

typedef enum {
    ENSAMP_DISABLED = 0,
    ENSAMP_ENABLED  = 1
} MAX30003_ENINT_ENSAMP_VAL;

typedef enum {
    ENRRINT_DISABLED    = 0,
    ENRRINT_ENABLED     = 1
} MAX30003_ENINT_ENRRINT_VAL;

typedef enum {
    ENLONINT_DISABLED   = 0,
    ENLONINT_ENABLED    = 1
} MAX30003_ENINT_ENLONINT_VAL;

typedef enum {
    ENDCLOFFINT_DISABLED    = 0,
    ENDCLOFFINT_ENABLED     = 1
} MAX30003_ENINT_ENDCLOFFINT_VAL;

typedef enum {
    ENFSTINT_DISABLED   = 0,
    ENFSTINT_ENABLED    = 1
} MAX30003_ENINT_ENFSTINT_VAL;

typedef enum {
    ENEOVF_DISABLED = 0,
    ENEOVF_ENABLED  = 1
} MAX30003_ENINT_ENEOVF_VAL;

typedef enum {
    ENINT_DISABLED  = 0,
    ENINT_ENABLED   = 1
} MAX30003_ENINT_ENINT_VAL;

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
    SAMPIT_EVERY_INST   = 0,
    SAMPIT_EVERY_2ND    = 1,
    SAMPIT_EVERY_4TH    = 2,
    SAMPIT_EVERY_16TH   = 3
} MAX30003_MNGRINT_SAMPIT_VAL;

typedef enum {
    CLRSAMP_ON_READ = 0,
    CLRSAMP_SELF    = 1
} MAX30003_MNGRINT_CLRSAMP_VAL;

typedef enum {
    CLRRINT_ON_STATUS = 0,
    CLRRINT_ON_RTOR   = 1,
    CLRRINT_SELF      = 2,
    _CLRRINT_RESERVED = 3
} MAX30003_MNGRINT_CLRRRINT_VAL;

typedef enum {
    CLRFAST_ON_FAST   = 0,
    CLRFAST_ON_STATUS = 1
} MAX30003_MNGRINT_CLRFAST_VAL;

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

// TODO do something about 
typedef uint8_t MAX30003_MNGR_DYN_FASTTH_VAL;

typedef enum {
    FAST_NORMAL     = 0,
    FAST_MANUAL     = 1,
    FAST_AUTO       = 2,
    _FAST_RESERVED  = 3
} MAX30003_MNGRDYN_FAST_VAL;

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

typedef enum {
    RBIASN_NOT_CONNECTED    = 0,
    RBIASN_CONNECTED        = 1
} MAX30003_CNFG_GEN_RBIASN_VAL;

typedef enum {
    RBIASP_NOT_CONNECTED    = 0,
    RBIASP_CONNECTED        = 1
} MAX30003_CNFG_GEN_RBIASP_VAL;

typedef enum {
    RBIAS_50_MOHM   = 0,
    RBIAS_100_MOHM  = 1,
    RBIAS_200_MOHM  = 2,
    RESERVED       = 3
} MAX30003_CNFG_GEN_RBIASV_VAL;

typedef enum {
    BIAS_DISABLED   = 0,
    BIAS_ENABLED    = 1,
    RESERVED1       = 2,
    RESERVED2       = 3
} MAX30003_CNFG_GEN_EN_RBIAS_VAL;

typedef enum {
    VMID_300_mV     = 0,
    VMID_400_mV     = 1,
    VMID_450_mV     = 2,
    VMID_500_mV     = 3
} MAX30003_CNFG_GEN_DCLOFF_VTH_VAL;

typedef enum {
    CURRENT_0_nA    = 0,
    CURRENT_5_nA    = 1,
    CURRENT_10_nA   = 2,
    CURRENT_20_nA   = 3,
    CURRENT_50_nA   = 4,
    CURRENT_100_nA  = 5,
    RESERVED1       = 6,
    RESERVED2       = 7
} MAX30003_CNFG_GEN_DCLOFF_IMAG_VAL;

typedef enum {
    P_UP_N_DOWN     = 0,
    P_DOWN_N_UP     = 1
} MAX30003_CNFG_GEN_DCLOFF_IPOL_VAL;

typedef enum {
    LOFF_DISABLED   = 0,
    LOFF_ENABLED    = 1,
    RESERVED1       = 2,
    RESERVED2       = 3
} MAX30003_CNFG_GEN_EN_DCLOFF_VAL;

typedef enum {
    DISABLED        = 0,
    ENABLED         = 1
} MAX30003_CNFG_GEN_EN_ECG_VAL;

typedef enum {
    ECG_PROG_512_HZ = 0, /* Fmstr = 32768Hz, Tres = 15.26us */
    ECG_PROG_500_HZ = 1, /* Fmstr = 32000Hz, Tres = 15.63us */
    ECG_PROG_200_HZ = 2, /* Fmstr = 32000Hz, Tres = 15.63us */
    ECG_PROG_199_HZ = 3  /* (199.8049Hz) Fmstr = 31968.78Hz, Tres = 15.64us */
} MAX30003_CNFG_GEN_FMSTR_VAL;

typedef enum {
    DISABLED        = 0,
    ENABLED         = 1,
    RESERVED1       = 2,
    RESERVED2       = 3
} MAX30003_CNFG_GEN_EN_ULP_LON_VAL;

typedef struct MAX30003_CNFG_GEN_VALS {
    MAX30003_CNFG_GEN_RBIASNP_VAL       rbiasn;
    MAX30003_CNFG_GEN_RBIASNP_VAL       rbiasp;
    MAX30003_CNFG_GEN_RBIASV_VAL        rbiasv;
    MAX30003_CNFG_GEN_EN_RBIAS_VAL      en_rbias;
    MAX30003_CNFG_GEN_DCLOFF_VTH_VAL    vth;
    MAX30003_CNFG_GEN_DCLOFF_IMAG_VAL   imag;
    MAX30003_CNFG_GEN_DCLOFF_IPOL_VAL   ipol;
    MAX30003_CNFG_GEN_EN_DCLOFF_VAL     en_dcloff;
    MAX30003_CNFG_GEN_EN_ECG_VAL        en_ecg;
    MAX30003_CNFG_GEN_FMSTR_VAL         fmstr;
    MAX30003_CNFG_GEN_EN_ULP_LON_VAL    en_ulp_lon;
} MAX30003_CNFG_GEN_VALS;

/***
 * CNFG_CAL register's masks and values
 ***/
typedef enum {
    THIGH       = 0x0003FF,
    FIFTY       = 0x000400,
    FCAL        = 0x007800,
    VMAG        = 0x100000,
    VMODE       = 0x200000,
    EN_CAL      = 0x400000,
    RESERVED    = 0x8F8000
} MAX30003_CNFG_CAL_MASKS;

// TODO enforce 3 bytes
typedef uint32_t MAX30003_CNFG_CAL_THIGH_VAL;

typedef enum {
    USE_CAL_THIGH   = 0,
    USE_50_PERCENT  = 1
} MAX30003_CNFG_CAL_FIFTY_VAL;

typedef enum {
    CAL_FREQ_256_HZ = 0,
    CAL_FREQ_64_HZ  = 1,
    CAL_FREQ_16_HZ  = 2,
    CAL_FREQ_4_HZ   = 3,
    CAL_FREQ_1_HZ   = 4,
    CAL_FREQ_1_4_HZ = 5,
    CAL_FREQ_1_16_HZ= 6,
    CAL_FREQ_1_64_HZ= 7
} MAX30003_CNFG_CAL_FCAL_VAL;

typedef enum {
    MAG_250_uV  = 0,
    MAG_500_uV  = 1
} MAX30003_CNFG_CAL_VMAG_VAL;

typedef enum {
    UNIPOLAR    = 0,
    BIPOLAR     = 1
} MAX30003_CNFG_CAL_VMODE_VAL;

typedef enum {
    DISABLED    = 0,
    ENABLED     = 1
} MAX30003_CNFG_CAL_EN_VCAL_VAL;

/***
 * CNFG_EMUX register's masks and values
 ***/
typedef enum {
    CALN_SEL    = 0x030000,
    CALP_SEL    = 0x0C0000,
    OPENN       = 0x100000,
    OPENP       = 0x200000,
    POL         = 0x800000,
    RESERVED    = 0x40FFFF
} MAX30003_CNFG_EMUX_MASKS;

typedef enum {
    CAL_IN_NONE     = 0,
    CAL_IN_VMID     = 1,
    CAL_IN_VCALP    = 2,
    CAL_IN_VCALN    = 3
} MAX30003_CNFG_EMUX_CAL_SEL_VAL;   /* for CALN and CALP */

typedef enum {
    IN_SWITCH_CONNECTED = 0,
    IN_SWITCH_ISOLATED  = 1
} MAX30003_CNFG_EMUX_OPEN_VAL;

typedef enum {
    NON_INVERTED    = 0,
    INVERTED        = 1
} MAX30003_CNFG_EMUX_POL_VAL;

/***
 * CNFG_ECG register's masks and values
 ***/
typedef enum {
    DLPF        = 0x003000,
    DHPF        = 0x004000,
    GAIN        = 0x030000,
    RATE        = 0xC00000,
    RESERVED	= 0x3C8FFF
} MAX30003_CNFG_ECG_MASKS;

typedef enum {
    LOWPASS_BYPASS	= 0,
    LOWPASS_40_HZ	= 1,
    LOWPASS_100_HZ	= 2,
    LOWPASS_150_HZ	= 3
} MAX30003_CNFG_ECG_DLPF_VAL;

typedef enum {
        HIPASS_BYPASS	= 0,
        HIPASS_HALF_HZ	= 1
} MAX30003_CNFG_ECG_DHPF_VAL;

typedef enum {
        GAIN_20_V	= 0,
        GAIN_40_V	= 1,
        GAIN_80_V	= 2,
        GAIN_160_V	= 3
} MAX30003_CNFG_ECG_GAIN_VAL;

typedef enum {
        RESERVED1	= 0,
        RESERVED2	= 1,
        SPS_199		= 2,
        RESERVED3 	= 3
} MAX30003_CNFG_ECG_RATE_199_PROG_VAL;

typedef enum {
        RESERVED1	= 0,
        RESERVED2	= 1,
        SPS_200		= 2,
        RESERVED3 	= 3
} MAX30003_CNFG_ECG_RATE_200_PROG_VAL;

typedef enum {
        SPS_500		= 0,
        SPS_250		= 1,
        SPS_125		= 2,
        RESERVED	= 3
} MAX30003_CNFG_ECG_RATE_500_PROG_VAL;

typedef enum {
        SPS_512		= 0,
        SPS_256		= 1,
        SPS_128		= 2,
        RESERVED	= 3
} MAX30003_CNFG_ECG_RATE_512_PROG_VAL;

/***
 * CNFG_RTOR1 register's masks and values
 ***/
typedef enum {
        PTSF		= 0x000F00,
        PAVG		= 0x003000,
        EN_RTOR		= 0x008000,
        GAIN		= 0x0F0000,
        WNDW		= 0xF00000,
        RESERVED	= 0x0040FF
} MAX30003_CNFG_RTOR1_MASKS;

// TODO enforce 1 to 16 or remove
typedef uint8_t MAX30003_CNFG_RTOR1_PTSF_VAL;

typedef enum {
        WEIGHT_2	= 0,
        WEIGHT_4	= 1,
        WEIGHT_8	= 2,
        WEIGHT_16	= 3
} MAX30003_CNFG_RTOR1_PAVG_VAL;

typedef enum {
        DISABLED	= 0,
        ENABLED		= 1
} MAX30003_CNFG_RTOR1_EN_RTOR_VAL;

/***
 * CNFG_RTOR2 register's masks and values
 ***/
typedef enum {
        RHSF		= 0x000700,
        RAVG		= 0x003000,
        HOFF		= 0x3F0000,
        RESERVED	= 0xC0C8FF
} MAX30003_CNFG_RTOR2_MASKS;

// TODO enforce 0-7 size or remove
typedef uint8_t MAX30003_CNFG_RTOR2_RHSF_VAL;

typedef enum {
        WEIGHT_2	= 0,
        WEIGHT_4	= 1,
        WEIGHT_8	= 2,
        WEIGHT_16	= 3
} MAX30003_CNFG_RTOR2_RAVG_VAL;

// TODO enforce 0 to 63 or remove
typedef uint8_t MAX30003_CNFG_RTOR2_HOFF_VAL;




#ifdef __cplusplus
}
#endif