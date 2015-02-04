#include "main.h"
#include "cn_current.h"
#include "cn_adc.h"
#include "cn_pwm.h"

uword cn_motor_current_lookup[] = {
0x0000, 0x0003, 0x0006, 0x000A, 0x000D, 0x0010, 0x0014, 0x0017, 0x001A,
0x001E, 0x0021, 0x0024, 0x0028, 0x002B, 0x002E, 0x0032, 0x0035, 0x0038,
0x003C, 0x003F, 0x0042, 0x0046, 0x0049, 0x004C, 0x0050, 0x0053, 0x0056,
0x005A, 0x005D, 0x0060, 0x0064, 0x0067, 0x006A, 0x006E, 0x0071, 0x0074,
0x0078, 0x007B, 0x007E, 0x0082, 0x0085, 0x0088, 0x008C, 0x008F, 0x0092,
0x0096, 0x0099, 0x009C, 0x00A0, 0x00A3, 0x00A6, 0x00AA, 0x00AD, 0x00B0,
0x00B4, 0x00B7, 0x00BA, 0x00BE, 0x00C1, 0x00C4, 0x00C8, 0x00CB, 0x00CE,
0x00D2, 0x00D5, 0x00D8, 0x00DC, 0x00DF, 0x00E2, 0x00E6, 0x00E9, 0x00EC,
0x00F0, 0x00F3, 0x00F6, 0x00FA, 0x00FD, 0x0100, 0x0104, 0x0107, 0x010A,
0x010E, 0x0111, 0x0114, 0x0118, 0x011B, 0x011E, 0x0122, 0x0125, 0x0128,
0x012C, 0x012F, 0x0132, 0x0136, 0x0139, 0x013C, 0x0140, 0x0143, 0x0146,
0x014A, 0x014D, 0x0150, 0x0154, 0x0157, 0x015A, 0x015E, 0x0161, 0x0164,
0x0168, 0x016B, 0x016E, 0x0172, 0x0175, 0x0178, 0x017C, 0x017F, 0x0182,
0x0186, 0x0189, 0x018C, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190,
0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x0190, 0x018E, 0x018C,
0x018A, 0x0188, 0x0186, 0x0185, 0x0183, 0x0181, 0x017F, 0x017D, 0x017B,
0x0179, 0x0178, 0x0176, 0x0174, 0x0172, 0x0170, 0x016F, 0x016D, 0x016B,
0x016A, 0x0168, 0x0167, 0x0165, 0x0163, 0x0162, 0x0160, 0x015F, 0x015D,
0x015C, 0x015A, 0x0159, 0x0157, 0x0156, 0x0154, 0x0153, 0x0151, 0x0150,
0x014F, 0x014D, 0x014C, 0x014A, 0x0149, 0x0148, 0x0146, 0x0145, 0x0144,
0x0143, 0x0141, 0x0140, 0x013F, 0x013E, 0x013C, 0x013B, 0x013A, 0x0139,
0x0138, 0x0136, 0x0135, 0x0134, 0x0133, 0x0132, 0x0131, 0x0130, 0x012E,
0x012D, 0x012C, 0x012B, 0x012A, 0x0129, 0x0128, 0x0127, 0x0126, 0x0125,
0x0124, 0x0123, 0x0122, 0x0121, 0x0120, 0x011F, 0x011E, 0x011D, 0x011C,
0x011B, 0x011A, 0x0119, 0x0118, 0x0117, 0x0116, 0x0115, 0x0115, 0x0114,
0x0113, 0x0112, 0x0111, 0x0110, 0x010F, 0x010E, 0x010E, 0x010D, 0x010C,
0x010B, 0x010A, 0x0109, 0x0109, 0x0108, 0x0107, 0x0106, 0x0105, 0x0105,
0x0104, 0x0103, 0x0102, 0x0101, 0x0101, 0x0100, 0x00FF, 0x00FE, 0x00FE,
0x00FD, 0x00FC, 0x00FC, 0x00FB, 0x00FA, 0x00F9, 0x00F9, 0x00F8, 0x00F7,
0x00F7, 0x00F6, 0x00F5, 0x00F5, 0x00F4, 0x00F3, 0x00F3, 0x00F2, 0x00F1,
0x00F1, 0x00F0, 0x00EF, 0x00EF, 0x00EE, 0x00ED, 0x00ED, 0x00EC, 0x00EC,
0x00EB, 0x00EA, 0x00EA, 0x00E9, 0x00E8, 0x00E8, 0x00E7, 0x00E7, 0x00E6,
0x00E5, 0x00E5, 0x00E4, 0x00E4, 0x00E3, 0x00E3, 0x00E2, 0x00E2, 0x00E1,
0x00E0, 0x00E0, 0x00DF, 0x00DF, 0x00DE, 0x00DE, 0x00DD, 0x00DD, 0x00DC,
0x00DC, 0x00DB, 0x00DB, 0x00DA, 0x00D9, 0x00D9, 0x00D8, 0x00D8, 0x00D7,
0x00D7, 0x00D6, 0x00D6, 0x00D5, 0x00D5, 0x00D4, 0x00D4, 0x00D4, 0x00D3,
0x00D3, 0x00D2, 0x00D2, 0x00D1, 0x00D1, 0x00D0, 0x00D0, 0x00CF, 0x00CF,
0x00CE, 0x00CE, 0x00CE, 0x00CD, 0x00CD, 0x00CC, 0x00CC, 0x00CB, 0x00CB,
0x00CA, 0x00CA, 0x00CA, 0x00C9, 0x00C9, 0x00C8, 0x00C8, 0x00C7, 0x00C7,
0x00C7, 0x00C6, 0x00C6, 0x00C5, 0x00C5, 0x00C5, 0x00C4, 0x00C4, 0x00C3,
0x00C3, 0x00C3, 0x00C2, 0x00C2, 0x00C1, 0x00C1, 0x00C1, 0x00C0, 0x00C0,
0x00C0, 0x00BF, 0x00BF, 0x00BE, 0x00BE, 0x00BE, 0x00BD, 0x00BD, 0x00BD,
0x00BC, 0x00BC, 0x00BC, 0x00BB, 0x00BB, 0x00BA, 0x00BA, 0x00BA, 0x00B9,
0x00B9, 0x00B9, 0x00B8, 0x00B8, 0x00B8, 0x00B7, 0x00B7, 0x00B7, 0x00B6,
0x00B6, 0x00B6, 0x00B5, 0x00B5, 0x00B5, 0x00B4, 0x00B4, 0x00B4, 0x00B3,
0x00B3, 0x00B3, 0x00B2, 0x00B2, 0x00B2, 0x00B1, 0x00B1, 0x00B1, 0x00B1,
0x00B0, 0x00B0, 0x00B0, 0x00AF, 0x00AF, 0x00AF, 0x00AE, 0x00AE, 0x00AE,
0x00AE, 0x00AD, 0x00AD, 0x00AD, 0x00AC, 0x00AC, 0x00AC, 0x00AC, 0x00AB,
0x00AB, 0x00AB, 0x00AA, 0x00AA, 0x00AA, 0x00AA, 0x00A9, 0x00A9, 0x00A9,
0x00A8, 0x00A8, 0x00A8, 0x00A8, 0x00A7, 0x00A7, 0x00A7, 0x00A7, 0x00A6,
0x00A6, 0x00A6, 0x00A5, 0x00A5, 0x00A5, 0x00A5, 0x00A4, 0x00A4, 0x00A4,
0x00A4, 0x00A3, 0x00A3, 0x00A3, 0x00A3, 0x00A2, 0x00A2, 0x00A2, 0x00A2,
0x00A1, 0x00A1, 0x00A1, 0x00A1, 0x00A0, 0x00A0, 0x00A0, 0x00A0, 0x009F,
0x009F, 0x009F, 0x009F, 0x009F, 0x009E, 0x009E, 0x009E, 0x009E, 0x009D,
0x009D, 0x009D, 0x009D, 0x009C, 0x009C, 0x009C, 0x009C, 0x009C, 0x009B,
0x009B, 0x009B, 0x009B, 0x009A, 0x009A, 0x009A, 0x009A, 0x009A, 0x0099,
0x0099, 0x0099, 0x0099, 0x0099, 0x0098, 0x0098, 0x0098, 0x0098, 0x0097,
0x0097, 0x0097, 0x0097, 0x0097, 0x0096, 0x0096, 0x0096, 0x0096, 0x0096,
0x0095, 0x0095, 0x0095, 0x0095, 0x0095, 0x0094, 0x0094, 0x0094, 0x0094,
0x0094, 0x0093, 0x0093, 0x0093, 0x0093, 0x0093, 0x0092, 0x0092, 0x0092,
0x0092, 0x0092, 0x0092, 0x0091, 0x0091, 0x0091, 0x0091, 0x0091, 0x0090,
0x0090, 0x0090, 0x0090, 0x0090, 0x0090, 0x008F, 0x008F, 0x008F, 0x008F,
0x008F, 0x008E, 0x008E, 0x008E, 0x008E, 0x008E, 0x008E, 0x008D, 0x008D,
0x008D, 0x008D, 0x008D, 0x008D, 0x008C, 0x008C, 0x008C, 0x008C, 0x008C,
0x008C, 0x008B, 0x008B, 0x008B, 0x008B, 0x008B, 0x008B, 0x008A, 0x008A,
0x008A, 0x008A, 0x008A, 0x008A, 0x0089, 0x0089, 0x0089, 0x0089, 0x0089,
0x0089, 0x0088, 0x0088, 0x0088, 0x0088, 0x0088, 0x0088, 0x0088, 0x0087,
0x0087, 0x0087, 0x0087, 0x0087, 0x0087, 0x0086, 0x0086, 0x0086, 0x0086,
0x0086, 0x0086, 0x0086, 0x0085, 0x0085, 0x0085, 0x0085, 0x0085, 0x0085,
0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0083, 0x0083,
0x0083, 0x0083, 0x0083, 0x0083, 0x0083, 0x0083, 0x0082, 0x0082, 0x0082,
0x0082, 0x0082, 0x0082, 0x0082, 0x0081, 0x0081, 0x0081, 0x0081, 0x0081,
0x0081, 0x0081, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080,
0x0080, 0x007F, 0x007F, 0x007F, 0x007F, 0x007F, 0x007F, 0x007F, 0x007E,
0x007E, 0x007E, 0x007E, 0x007E, 0x007E, 0x007E, 0x007E, 0x007D, 0x007D,
0x007D, 0x007D, 0x007D, 0x007D, 0x007D, 0x007D, 0x007C, 0x007C, 0x007C,
0x007C, 0x007C, 0x007C, 0x007C, 0x007C, 0x007C, 0x007B, 0x007B, 0x007B,
0x007B, 0x007B, 0x007B, 0x007B, 0x007B, 0x007A, 0x007A, 0x007A, 0x007A,
0x007A, 0x007A, 0x007A, 0x007A, 0x007A, 0x0079, 0x0079, 0x0079, 0x0079,
0x0079, 0x0079, 0x0079, 0x0079, 0x0079, 0x0078, 0x0078, 0x0078, 0x0078,
0x0078, 0x0078, 0x0078, 0x0078, 0x0078, 0x0077, 0x0077, 0x0077, 0x0077,
0x0077, 0x0077, 0x0077, 0x0077, 0x0077, 0x0076, 0x0076, 0x0076, 0x0076,
0x0076, 0x0076, 0x0076, 0x0076, 0x0076, 0x0075, 0x0075, 0x0075, 0x0075,
0x0075, 0x0075, 0x0075, 0x0075, 0x0075, 0x0075, 0x0074, 0x0074, 0x0074,
0x0074, 0x0074, 0x0074, 0x0074, 0x0074, 0x0074, 0x0074, 0x0073, 0x0073,
0x0073, 0x0073, 0x0073, 0x0073, 0x0073, 0x0073, 0x0073, 0x0073, 0x0072,
0x0072, 0x0072, 0x0072, 0x0072, 0x0072, 0x0072, 0x0072, 0x0072, 0x0072,
0x0072, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071,
0x0071, 0x0071, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x0070,
0x0070, 0x0070, 0x0070, 0x0070, 0x0070, 0x006F, 0x006F, 0x006F, 0x006F,
0x006F, 0x006F, 0x006F, 0x006F, 0x006F, 0x006F, 0x006F, 0x006E, 0x006E,
0x006E, 0x006E, 0x006E, 0x006E, 0x006E, 0x006E, 0x006E, 0x006E, 0x006E,
0x006D, 0x006D, 0x006D, 0x006D, 0x006D, 0x006D, 0x006D, 0x006D, 0x006D,
0x006D, 0x006D, 0x006D, 0x006C, 0x006C, 0x006C, 0x006C, 0x006C, 0x006C,
0x006C, 0x006C, 0x006C, 0x006C, 0x006C, 0x006C, 0x006C, 0x006B, 0x006B,
0x006B, 0x006B, 0x006B, 0x006B, 0x006B, 0x006B, 0x006B, 0x006B, 0x006B,
0x006B, 0x006A, 0x006A, 0x006A, 0x006A, 0x006A, 0x006A, 0x006A, 0x006A,
0x006A, 0x006A, 0x006A, 0x006A, 0x006A, 0x0069, 0x0069, 0x0069, 0x0069,
0x0069, 0x0069, 0x0069, 0x0069, 0x0069, 0x0069, 0x0069, 0x0069, 0x0069,
0x0069, 0x0068, 0x0068, 0x0068, 0x0068, 0x0068, 0x0068, 0x0068, 0x0068,
0x0068, 0x0068, 0x0068, 0x0068, 0x0068, 0x0068, 0x0067, 0x0067, 0x0067,
0x0067, 0x0067, 0x0067, 0x0067, 0x0067, 0x0067, 0x0067, 0x0067, 0x0067,
0x0067, 0x0067, 0x0066, 0x0066, 0x0066, 0x0066, 0x0066, 0x0066, 0x0066,
0x0066, 0x0066, 0x0066, 0x0066, 0x0066, 0x0066, 0x0066, 0x0065, 0x0065,
0x0065, 0x0065, 0x0065, 0x0065, 0x0065, 0x0065, 0x0065, 0x0065, 0x0065,
0x0065, 0x0065, 0x0065, 0x0065, 0x0064, 0x0064, 0x0064, 0x0064, 0x0064,
0x0064, 0x0064, 0x0064, 0x0064, 0x0064, 0x0064, 0x0064, 0x0064, 0x0064,
0x0064, 0x0064, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063,
0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063, 0x0063,
};

uword motor_current[3] = {0, 0, 0};

void init_current() {
	
}

uword getMotorCurrent(ubyte motor) {

	uword voltage;
#ifdef TMC
	uword pwm;
#endif
	udword current;
	uword i;
  
	// find index for results
	// TODO: maybe do this in adc_init for all
	for(i = 0; i < CN_ADC_CHAN_COUNT; ++i) {
		if(cn_adc_motors[i] == motor) break;
	}
  
	// TODO better error signaling
	if(cn_adc_motors[i] != motor) return 0xFFFF;

#ifdef TMC  
	pwm     = cn_adc_results[i].pwm;
	// TODO better error signaling
	if(pwm > MAX_PWM) return 0xFFFF;
#endif

	voltage = cn_adc_results[i].voltage;

#ifdef TMC
	current  = ((udword) voltage) * ((udword) cn_motor_current_lookup[pwm]);
	current /= 100l; // value is not more accurate anyway
#endif
#ifdef VMC
	//current = voltage;
	//current  = (uword)((((((float) voltage)*5)/1023)/0.56) * 1000);
	//current /= 10;
	//current = ((((((udword) voltage)*50000l)/1023)/56));
	current = (((((udword) voltage)*50000l)/57288l));
#endif

	return (uword) current;
}