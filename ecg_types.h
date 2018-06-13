/*
 * ecg_types.h
 *
 * Created: 10-Jun-18 00:19:54
 *  Author: Ethan
 */


#ifndef ECG_TYPES_H_
#define ECG_TYPES_H_

/* ECG_SAMPLE type
 *	struct for storing a bit-mapped ECG sample in a 32-bit number
 *	packing and bit order is ignored as the total struct size is 32-bits
 */
typedef struct __attribute__((__packed__)) {
	int32_t	tag  : 3;	/* ETAG data from the ECG_FIFO	*/
	int32_t	step : 11;	/* time step of the sample		*/
    int32_t	data : 18;	/* voltage of the sample		*/
} ECG_SAMPLE_t;

typedef enum {
    ECG_LP_BYPASS	= 0,
    ECG_LP_40_HZ	= 1,
    ECG_LP_100_HZ	= 2,
    ECG_LP_150_HZ	= 3
} ECG_LOW_PASS_t;

typedef enum {
    ECG_GAIN_20_V	= 0,
    ECG_GAIN_40_V	= 1,
    ECG_GAIN_80_V	= 2,
    ECG_GAIN_160_V	= 3
} ECG_GAIN_t;

typedef enum {
    ECG_RATE_MAX_SPS	= 0,
    ECG_RATE_MED_SPS	= 1,
    ECG_RATE_MIN_SPS	= 2,
    ECG_RATE_RESERVED	= 3
} ECG_SAMPLE_RATE_t;

#endif /* ECG_TYPES_H_ */