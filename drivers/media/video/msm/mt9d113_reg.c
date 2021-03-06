
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "mt9d113.h"
#define mt9d113_ARRAY_SIZE_2(x) (sizeof(x) / sizeof(x[0]))

struct mt9d113_i2c_reg_conf mt9d113_init_reg_config_byd_settings_2[] =
{
    {0x098C, 0x2719}, // MCU_ADDRESS [MODE_SENSOR_FINE_CORRECTION_A]
    {0x0990, 0x005A}, // MCU_DATA_0
    {0x098C, 0x271B}, // MCU_ADDRESS [MODE_SENSOR_FINE_IT_MIN_A]
    {0x0990, 0x01BE}, // MCU_DATA_0
    {0x098C, 0x271D}, // MCU_ADDRESS [MODE_SENSOR_FINE_IT_MAX_MARGIN_A]
    {0x0990, 0x0131}, // MCU_DATA_0
    {0x098C, 0x271F}, // MCU_ADDRESS [MODE_SENSOR_FRAME_LENGTH_A]
    {0x0990, 0x02BB}, // MCU_DATA_0
    {0x098C, 0x2721}, // MCU_ADDRESS [MODE_SENSOR_LINE_LENGTH_PCK_A]
    {0x0990, 0x0888}, // MCU_DATA_0
    {0x098C, 0x272F}, // MCU_ADDRESS [MODE_SENSOR_FINE_CORRECTION_B]
    {0x0990, 0x003A}, // MCU_DATA_0
    {0x098C, 0x2731}, // MCU_ADDRESS [MODE_SENSOR_FINE_IT_MIN_B]
    {0x0990, 0x00F6}, // MCU_DATA_0
    {0x098C, 0x2733}, // MCU_ADDRESS [MODE_SENSOR_FINE_IT_MAX_MARGIN_B]
    {0x0990, 0x008B}, // MCU_DATA_0
    {0x098C, 0x2735}, // MCU_ADDRESS [MODE_SENSOR_FRAME_LENGTH_B]
    {0x0990, 0x0521}, // MCU_DATA_0
    {0x098C, 0x2737}, // MCU_ADDRESS [MODE_SENSOR_LINE_LENGTH_PCK_B]
    {0x0990, 0x0898},   // MCU_DATA_0
    {0x098C, 0x275F}, // MCU_ADDRESS [MODE_COMMONMODESETTINGS_BRIGHT_COLOR_KILL]
    {0x0990, 0x0194}, // MCU_DATA_0
    {0x098C, 0x2761}, // MCU_ADDRESS [MODE_COMMONMODESETTINGS_DARK_COLOR_KILL]
    {0x0990, 0x0014}, // MCU_DATA_0
    {0x098C, 0xA765}, // MCU_ADDRESS [MODE_COMMONMODESETTINGS_FILTER_MODE]
    {0x0990, 0x0044}, // MCU_DATA_0
    {0x098C, 0xA24F}, // MCU_ADDRESS [AE_BASETARGET]
    {0x0990, 0x0038}, // MCU_DATA_0
    {0x098C, 0xA20E}, // MCU_ADDRESS [AE_MAX_VIRTGAIN]
    {0x0990, 0x00A0}, // MCU_DATA_0
    {0x098C, 0xA20C}, // MCU_ADDRESS [AE_MAX_INDEX]
    {0x0990, 0x000E}, // MCU_DATA_0
    {0x098C, 0x2222}, // MCU_ADDRESS [AE_R9]
    {0x0990, 0x00A0}, // MCU_DATA_0
    {0x098C, 0x2212},     // MCU_ADDRESS [AE_MAX_DGAIN_AE1]
    {0x0990, 0x0080},     // MCU_DATA_0
    {0x098C, 0x221F},     // MCU_ADDRESS [AE_DGAIN_AE1]
    {0x0990, 0x0080},     // MCU_DATA_0    
    {0x098C, 0xA408}, // MCU_ADDRESS [FD_SEARCH_F1_50]
    {0x0990, 0x0026}, // MCU_DATA_0
    {0x098C, 0xA409}, // MCU_ADDRESS [FD_SEARCH_F2_50]
    {0x0990, 0x0029}, // MCU_DATA_0
    {0x098C, 0xA40A}, // MCU_ADDRESS [FD_SEARCH_F1_60]
    {0x0990, 0x002E}, // MCU_DATA_0
    {0x098C, 0xA40B}, // MCU_ADDRESS [FD_SEARCH_F2_60]
    {0x0990, 0x0031}, // MCU_DATA_0
    {0x098C, 0x2411}, // MCU_ADDRESS [FD_R9_STEP_F60_A]
    {0x0990, 0x00A0}, // MCU_DATA_0
    {0x098C, 0x2413}, // MCU_ADDRESS [FD_R9_STEP_F50_A]
    {0x0990, 0x00C0}, // MCU_DATA_0
    {0x098C, 0x2415}, // MCU_ADDRESS [FD_R9_STEP_F60_B]
    {0x0990, 0x00A0}, // MCU_DATA_0
    {0x098C, 0x2417}, // MCU_ADDRESS [FD_R9_STEP_F50_B]
    {0x0990, 0x00C0}, // MCU_DATA_0
    {0x3084, 0x240C},
    {0x3092, 0x0A4C},
    {0x3094, 0x4C4C},
    {0x3096, 0x4C54},
    {0x3210, 0x01B8},
    {0x098C, 0x2B28}, // MCU_ADDRESS [HG_LL_BRIGHTNESSSTART]
    {0x0990, 0x35E8}, // MCU_DATA_0
    {0x098C, 0x2B2A}, // MCU_ADDRESS [HG_LL_BRIGHTNESSSTOP]
    {0x0990, 0xB3B0}, // MCU_DATA_0
    {0x098C, 0xAB20}, // MCU_ADDRESS [HG_LL_SAT1]
    {0x0990, 0x004B}, // MCU_DATA_0
    {0x098C, 0xAB24}, // MCU_ADDRESS [HG_LL_SAT2]
    {0x0990, 0x0000}, // MCU_DATA_0
    {0x098C, 0xAB25}, // MCU_ADDRESS [HG_LL_INTERPTHRESH2]
    {0x0990, 0x00FF}, // MCU_DATA_0
    {0x098C, 0xAB30}, // MCU_ADDRESS [HG_NR_STOP_R]
    {0x0990, 0x00FF}, // MCU_DATA_0
    {0x098C, 0xAB31}, // MCU_ADDRESS [HG_NR_STOP_G]
    {0x0990, 0x00FF}, // MCU_DATA_0
    {0x098C, 0xAB32}, // MCU_ADDRESS [HG_NR_STOP_B]
    {0x0990, 0x00FF}, // MCU_DATA_0
    {0x098C, 0xAB33}, // MCU_ADDRESS [HG_NR_STOP_OL]
    {0x0990, 0x0057}, // MCU_DATA_0
    {0x098C, 0xAB34}, // MCU_ADDRESS [HG_NR_GAINSTART]
    {0x0990, 0x0080}, // MCU_DATA_0
    {0x098C, 0xAB35}, // MCU_ADDRESS [HG_NR_GAINSTOP]
    {0x0990, 0x00FF}, // MCU_DATA_0
    {0x098C, 0xAB36}, // MCU_ADDRESS [HG_CLUSTERDC_TH]
    {0x0990, 0x0014}, // MCU_DATA_0
    {0x098C, 0xAB37}, // MCU_ADDRESS [HG_GAMMA_MORPH_CTRL]
    {0x0990, 0x0003}, // MCU_DATA_0
    {0x098C, 0x2B38}, // MCU_ADDRESS [HG_GAMMASTARTMORPH]
    {0x0990, 0x32C8}, // MCU_DATA_0
    {0x098C, 0x2B3A}, // MCU_ADDRESS [HG_GAMMASTOPMORPH]
    {0x0990, 0x7918}, // MCU_DATA_0
    {0x098C, 0x2B62}, // MCU_ADDRESS [HG_FTB_START_BM]
    {0x0990, 0xFFFE}, // MCU_DATA_0
    {0x098C, 0x2B64}, // MCU_ADDRESS [HG_FTB_STOP_BM]
    {0x0990, 0xFFFF}, // MCU_DATA_0
    
    {0x098C, 0x2306},     // MCU_ADDRESS [AWB_CCM_L_0]
    {0x0990, 0x0132},     // MCU_DATA_0
    {0x098C, 0x231C},     // MCU_ADDRESS [AWB_CCM_RL_0]
    {0x0990, 0x0169},     // MCU_DATA_0
    {0x098C, 0x2308},     // MCU_ADDRESS [AWB_CCM_L_1]
    {0x0990, 0xFF68},     // MCU_DATA_0
    {0x098C, 0x231E},     // MCU_ADDRESS [AWB_CCM_RL_1]
    {0x0990, 0xFF19},     // MCU_DATA_0
    {0x098C, 0x230A},     // MCU_ADDRESS [AWB_CCM_L_2]
    {0x0990, 0x0066},     // MCU_DATA_0
    {0x098C, 0x2320},     // MCU_ADDRESS [AWB_CCM_RL_2]
    {0x0990, 0x001F},     // MCU_DATA_0
    {0x098C, 0x230C},     // MCU_ADDRESS [AWB_CCM_L_3]
    {0x0990, 0xFFA1},     // MCU_DATA_0
    {0x098C, 0x2322},     // MCU_ADDRESS [AWB_CCM_RL_3]
    {0x0990, 0x000A},     // MCU_DATA_0
    {0x098C, 0x230E},     // MCU_ADDRESS [AWB_CCM_L_4]
    {0x0990, 0x0144},     // MCU_DATA_0
    {0x098C, 0x2324},     // MCU_ADDRESS [AWB_CCM_RL_4]
    {0x0990, 0x0012},     // MCU_DATA_0
    {0x098C, 0x2310},     // MCU_ADDRESS [AWB_CCM_L_5]
    {0x0990, 0xFFFA},     // MCU_DATA_0
    {0x098C, 0x2326},     // MCU_ADDRESS [AWB_CCM_RL_5]
    {0x0990, 0xFFA6},     // MCU_DATA_0
    {0x098C, 0x2312},     // MCU_ADDRESS [AWB_CCM_L_6]
    {0x0990, 0xFFED},     // MCU_DATA_0
    {0x098C, 0x2328},     // MCU_ADDRESS [AWB_CCM_RL_6]
    {0x0990, 0x002A},     // MCU_DATA_0
    {0x098C, 0x2314},     // MCU_ADDRESS [AWB_CCM_L_7]
    {0x0990, 0xFF41},     // MCU_DATA_0
    {0x098C, 0x232A},     // MCU_ADDRESS [AWB_CCM_RL_7]
    {0x0990, 0xFFFC},     // MCU_DATA_0
    {0x098C, 0x2316},     // MCU_ADDRESS [AWB_CCM_L_8]
    {0x0990, 0x0139},     // MCU_DATA_0
    {0x098C, 0x232C},     // MCU_ADDRESS [AWB_CCM_RL_8]
    {0x0990, 0xFFD2},     // MCU_DATA_0
    
    {0x098C, 0x2318}, // MCU_ADDRESS [AWB_CCM_L_9]
    {0x0990, 0x0020}, // MCU_DATA_0
    {0x098C, 0x231A}, // MCU_ADDRESS [AWB_CCM_L_10]
    {0x0990, 0x0033}, // MCU_DATA_0
    {0x098C, 0x232E}, // MCU_ADDRESS [AWB_CCM_RL_9]
    {0x0990, 0x0008}, // MCU_DATA_0
    {0x098C, 0x2330}, // MCU_ADDRESS [AWB_CCM_RL_10]
    {0x0990, 0xFFF7}, // MCU_DATA_0
    
    {0x098C, 0xA363}, // MCU_ADDRESS [AWB_TG_MIN0]
    {0x0990, 0x00D2}, // MCU_DATA_0
    {0x098C, 0xA364}, // MCU_ADDRESS [AWB_TG_MAX0]
    {0x0990, 0x00EE}, // MCU_DATA_0
    
    {0x3244, 0x0328},
    {0x323E, 0xC22C},
    {0x098C, 0x0415},
    {0x0990, 0xF601},
    {0x0992, 0x42C1},
    {0x0994, 0x0326},
    {0x0996, 0x11F6},
    {0x0998, 0x0143},
    {0x099A, 0xC104},
    {0x099C, 0x260A},
    {0x099E, 0xCC04},
    {0x098C, 0x0425},
    {0x0990, 0x33BD},
    {0x0992, 0xA362},
    {0x0994, 0xBD04},
    {0x0996, 0x3339},
    {0x0998, 0xC6FF},
    {0x099A, 0xF701},
    {0x099C, 0x6439},
    {0x099E, 0xDE5D},
    {0x098C, 0x0435},
    {0x0990, 0x18CE},
    {0x0992, 0x0325},
    {0x0994, 0xCC00},
    {0x0996, 0x27BD},
    {0x0998, 0xC2B8},
    {0x099A, 0xCC04},
    {0x099C, 0xBDFD},
    {0x099E, 0x033B},
    {0x098C, 0x0445},
    {0x0990, 0xCC06},
    {0x0992, 0x6BFD},
    {0x0994, 0x032F},
    {0x0996, 0xCC03},
    {0x0998, 0x25DD},
    {0x099A, 0x5DC6},
    {0x099C, 0x1ED7},
    {0x099E, 0x6CD7},
    {0x098C, 0x0455},
    {0x0990, 0x6D5F},
    {0x0992, 0xD76E},
    {0x0994, 0xD78D},
    {0x0996, 0x8620},
    {0x0998, 0x977A},
    {0x099A, 0xD77B},
    {0x099C, 0x979A},
    {0x099E, 0xC621},
    {0x098C, 0x0465},
    {0x0990, 0xD79B},
    {0x0992, 0xFE01},
    {0x0994, 0x6918},
    {0x0996, 0xCE03},
    {0x0998, 0x4DCC},
    {0x099A, 0x0013},
    {0x099C, 0xBDC2},
    {0x099E, 0xB8CC},
    {0x098C, 0x0475},
    {0x0990, 0x05E9},
    {0x0992, 0xFD03},
    {0x0994, 0x4FCC},
    {0x0996, 0x034D},
    {0x0998, 0xFD01},
    {0x099A, 0x69FE},
    {0x099C, 0x02BD},
    {0x099E, 0x18CE},
    {0x098C, 0x0485},
    {0x0990, 0x0361},
    {0x0992, 0xCC00},
    {0x0994, 0x11BD},
    {0x0996, 0xC2B8},
    {0x0998, 0xCC06},
    {0x099A, 0x28FD},
    {0x099C, 0x036F},
    {0x099E, 0xCC03},
    {0x098C, 0x0495},
    {0x0990, 0x61FD},
    {0x0992, 0x02BD},
    {0x0994, 0xDE00},
    {0x0996, 0x18CE},
    {0x0998, 0x00C2},
    {0x099A, 0xCC00},
    {0x099C, 0x37BD},
    {0x099E, 0xC2B8},
    {0x098C, 0x04A5},
    {0x0990, 0xCC06},
    {0x0992, 0x4FDD},
    {0x0994, 0xE6CC},
    {0x0996, 0x00C2},
    {0x0998, 0xDD00},
    {0x099A, 0xC601},
    {0x099C, 0xF701},
    {0x099E, 0x64C6},
    {0x098C, 0x04B5},
    {0x0990, 0x05F7},
    {0x0992, 0x0165},
    {0x0994, 0x7F01},
    {0x0996, 0x6639},
    {0x0998, 0x373C},
    {0x099A, 0x3C3C},
    {0x099C, 0x3C3C},
    {0x099E, 0x30EC},
    {0x098C, 0x04C5},
    {0x0990, 0x11ED},
    {0x0992, 0x02EC},
    {0x0994, 0x0FED},
    {0x0996, 0x008F},
    {0x0998, 0x30ED},
    {0x099A, 0x04EC},
    {0x099C, 0x0DEE},
    {0x099E, 0x04BD},
    {0x098C, 0x04D5},
    {0x0990, 0xA406},
    {0x0992, 0x30EC},
    {0x0994, 0x02ED},
    {0x0996, 0x06FC},
    {0x0998, 0x10C0},
    {0x099A, 0x2705},
    {0x099C, 0xCCFF},
    {0x099E, 0xFFED},
    {0x098C, 0x04E5},
    {0x0990, 0x06F6},
    {0x0992, 0x0256},
    {0x0994, 0x8616},
    {0x0996, 0x3DC3},
    {0x0998, 0x0261},
    {0x099A, 0x8FE6},
    {0x099C, 0x09C4},
    {0x099E, 0x07C1},
    {0x098C, 0x04F5},
    {0x0990, 0x0226},
    {0x0992, 0x1DFC},
    {0x0994, 0x10C2},
    {0x0996, 0x30ED},
    {0x0998, 0x02FC},
    {0x099A, 0x10C0},
    {0x099C, 0xED00},
    {0x099E, 0xC602},
    {0x098C, 0x0505},
    {0x0990, 0xBDC2},
    {0x0992, 0x5330},
    {0x0994, 0xEC00},
    {0x0996, 0xFD10},
    {0x0998, 0xC0EC},
    {0x099A, 0x02FD},
    {0x099C, 0x10C2},
    {0x099E, 0x201B},
    {0x098C, 0x0515},
    {0x0990, 0xFC10},
    {0x0992, 0xC230},
    {0x0994, 0xED02},
    {0x0996, 0xFC10},
    {0x0998, 0xC0ED},
    {0x099A, 0x00C6},
    {0x099C, 0x01BD},
    {0x099E, 0xC253},
    {0x098C, 0x0525},
    {0x0990, 0x30EC},
    {0x0992, 0x00FD},
    {0x0994, 0x10C0},
    {0x0996, 0xEC02},
    {0x0998, 0xFD10},
    {0x099A, 0xC2C6},
    {0x099C, 0x80D7},
    {0x099E, 0x85C6},
    {0x098C, 0x0535},
    {0x0990, 0x40F7},
    {0x0992, 0x10C4},
    {0x0994, 0xF602},
    {0x0996, 0x5686},
    {0x0998, 0x163D},
    {0x099A, 0xC302},
    {0x099C, 0x618F},
    {0x099E, 0xEC14},
    {0x098C, 0x0545},
    {0x0990, 0xFD10},
    {0x0992, 0xC501},
    {0x0994, 0x0101},
    {0x0996, 0x0101},
    {0x0998, 0xFC10},
    {0x099A, 0xC2DD},
    {0x099C, 0x7FFC},
    {0x099E, 0x10C7},
    {0x098C, 0x0555},
    {0x0990, 0xDD76},
    {0x0992, 0xF602},
    {0x0994, 0x5686},
    {0x0996, 0x163D},
    {0x0998, 0xC302},
    {0x099A, 0x618F},
    {0x099C, 0xEC14},
    {0x099E, 0x939F},
    {0x098C, 0x0565},
    {0x0990, 0x30ED},
    {0x0992, 0x08DC},
    {0x0994, 0x7693},
    {0x0996, 0x9D25},
    {0x0998, 0x08F6},
    {0x099A, 0x02BC},
    {0x099C, 0x4F93},
    {0x099E, 0x7F23},
    {0x098C, 0x0575},
    {0x0990, 0x3DF6},
    {0x0992, 0x02BC},
    {0x0994, 0x4F93},
    {0x0996, 0x7F23},
    {0x0998, 0x06F6},
    {0x099A, 0x02BC},
    {0x099C, 0x4FDD},
    {0x099E, 0x7FDC},
    {0x098C, 0x0585},
    {0x0990, 0x9DDD},
    {0x0992, 0x76F6},
    {0x0994, 0x02BC},
    {0x0996, 0x4F93},
    {0x0998, 0x7F26},
    {0x099A, 0x0FE6},
    {0x099C, 0x0AC1},
    {0x099E, 0x0226},
    {0x098C, 0x0595},
    {0x0990, 0x09D6},
    {0x0992, 0x85C1},
    {0x0994, 0x8026},
    {0x0996, 0x0314},
    {0x0998, 0x7401},
    {0x099A, 0xF602},
    {0x099C, 0xBC4F},
    {0x099E, 0x937F},
    {0x098C, 0x05A5},
    {0x0990, 0x2416},
    {0x0992, 0xDE7F},
    {0x0994, 0x09DF},
    {0x0996, 0x7F30},
    {0x0998, 0xEC08},
    {0x099A, 0xDD76},
    {0x099C, 0x200A},
    {0x099E, 0xDC76},
    {0x098C, 0x05B5},
    {0x0990, 0xA308},
    {0x0992, 0x2304},
    {0x0994, 0xEC08},
    {0x0996, 0xDD76},
    {0x0998, 0x1274},
    {0x099A, 0x0122},
    {0x099C, 0xDE5D},
    {0x099E, 0xEE14},
    {0x098C, 0x05C5},
    {0x0990, 0xAD00},
    {0x0992, 0x30ED},
    {0x0994, 0x11EC},
    {0x0996, 0x06ED},
    {0x0998, 0x02CC},
    {0x099A, 0x0080},
    {0x099C, 0xED00},
    {0x099E, 0x8F30},
    {0x098C, 0x05D5},
    {0x0990, 0xED04},
    {0x0992, 0xEC11},
    {0x0994, 0xEE04},
    {0x0996, 0xBDA4},
    {0x0998, 0x0630},
    {0x099A, 0xE603},
    {0x099C, 0xD785},
    {0x099E, 0x30C6},
    {0x098C, 0x05E5},
    {0x0990, 0x0B3A},
    {0x0992, 0x3539},
    {0x0994, 0x3C3C},
    {0x0996, 0x3C34},
    {0x0998, 0xCC32},
    {0x099A, 0x3EBD},
    {0x099C, 0xA558},
    {0x099E, 0x30ED},
    {0x098C, 0x05F5},
    {0x0990, 0x04BD},
    {0x0992, 0xB2D7},
    {0x0994, 0x30E7},
    {0x0996, 0x06CC},
    {0x0998, 0x323E},
    {0x099A, 0xED00},
    {0x099C, 0xEC04},
    {0x099E, 0xBDA5},
    {0x098C, 0x0605},
    {0x0990, 0x44CC},
    {0x0992, 0x3244},
    {0x0994, 0xBDA5},
    {0x0996, 0x585F},
    {0x0998, 0x30ED},
    {0x099A, 0x02CC},
    {0x099C, 0x3244},
    {0x099E, 0xED00},
    {0x098C, 0x0615},
    {0x0990, 0xF601},
    {0x0992, 0xD54F},
    {0x0994, 0xEA03},
    {0x0996, 0xAA02},
    {0x0998, 0xBDA5},
    {0x099A, 0x4430},
    {0x099C, 0xE606},
    {0x099E, 0x3838},
    {0x098C, 0x0625},
    {0x0990, 0x3831},
    {0x0992, 0x39BD},
    {0x0994, 0xD661},
    {0x0996, 0xF602},
    {0x0998, 0xF4C1},
    {0x099A, 0x0126},
    {0x099C, 0x0BFE},
    {0x099E, 0x02BD},
    {0x098C, 0x0635},
    {0x0990, 0xEE10},
    {0x0992, 0xFC02},
    {0x0994, 0xF5AD},
    {0x0996, 0x0039},
    {0x0998, 0xF602},
    {0x099A, 0xF4C1},
    {0x099C, 0x0226},
    {0x099E, 0x0AFE},
    {0x098C, 0x0645},
    {0x0990, 0x02BD},
    {0x0992, 0xEE10},
    {0x0994, 0xFC02},
    {0x0996, 0xF7AD},
    {0x0998, 0x0039},
    {0x099A, 0x3CBD},
    {0x099C, 0xB059},
    {0x099E, 0xCC00},
    {0x098C, 0x0655},
    {0x0990, 0x28BD},
    {0x0992, 0xA558},
    {0x0994, 0x8300},
    {0x0996, 0x0027},
    {0x0998, 0x0BCC},
    {0x099A, 0x0026},
    {0x099C, 0x30ED},
    {0x099E, 0x00C6},
    {0x098C, 0x0665},
    {0x0990, 0x03BD},
    {0x0992, 0xA544},
    {0x0994, 0x3839},
    {0x0996, 0xBDD9},
    {0x0998, 0x42D6},
    {0x099A, 0x9ACB},
    {0x099C, 0x01D7},
    {0x099E, 0x9B39},
    {0x098C, 0x2006}, // MCU_ADDRESS [MON_ARG1]
    {0x0990, 0x0415}, // MCU_DATA_0
    {0x098C, 0xA005}, // MCU_ADDRESS [MON_CMD]
    {0x0990, 0x0001}, // MCU_DATA_0
    
    {0x3210, 0x01B0},
    {0x364E, 0x05F0},
    {0x3650, 0x14C5},
    {0x3652, 0x31F2},
    {0x3654, 0xDF6D},
    {0x3656, 0xB113},
    {0x3658, 0x00B0},
    {0x365A, 0xE566},
    {0x365C, 0x4912},
    {0x365E, 0xDECE},
    {0x3660, 0xF0F2},
    {0x3662, 0x00B0},
    {0x3664, 0x7AA8},
    {0x3666, 0x13F2},
    {0x3668, 0xAFAC},
    {0x366A, 0xBDB2},
    {0x366C, 0x00B0},
    {0x366E, 0x0488},
    {0x3670, 0x2B52},
    {0x3672, 0xDF8D},
    {0x3674, 0xACF3},
    {0x3676, 0x3BCA},
    {0x3678, 0xF68E},
    {0x367A, 0x74AE},
    {0x367C, 0x0470},
    {0x367E, 0xACB2},
    {0x3680, 0x356B},
    {0x3682, 0x6CCE},
    {0x3684, 0x496D},
    {0x3686, 0x94F1},
    {0x3688, 0xC6B0},
    {0x368A, 0x54AA},
    {0x368C, 0xDF4F},
    {0x368E, 0xA4AD},
    {0x3690, 0x49F1},
    {0x3692, 0xF1EE},
    {0x3694, 0x006A},
    {0x3696, 0x3BCF},
    {0x3698, 0x0FCE},
    {0x369A, 0xB390},
    {0x369C, 0x93D2},
    {0x369E, 0x7B92},
    {0x36A0, 0xB4C9},
    {0x36A2, 0x9CF4},
    {0x36A4, 0x2BCF},
    {0x36A6, 0x4D95},
    {0x36A8, 0x0213},
    {0x36AA, 0x4B0E},
    {0x36AC, 0xBDF1},
    {0x36AE, 0x39D1},
    {0x36B0, 0x9A96},
    {0x36B2, 0x4FF2},
    {0x36B4, 0x3FB0},
    {0x36B6, 0xFF12},
    {0x36B8, 0xDE8F},
    {0x36BA, 0x7D32},
    {0x36BC, 0x06F3},
    {0x36BE, 0xC14D},
    {0x36C0, 0xA354},
    {0x36C2, 0x4CD0},
    {0x36C4, 0x24D5},
    {0x36C6, 0xB2CE},
    {0x36C8, 0x9FD2},
    {0x36CA, 0xC413},
    {0x36CC, 0x0A95},
    {0x36CE, 0x7575},
    {0x36D0, 0x952F},
    {0x36D2, 0x3672},
    {0x36D4, 0xB9F2},
    {0x36D6, 0x88F3},
    {0x36D8, 0xB674},
    {0x36DA, 0x7BAD},
    {0x36DC, 0x3392},
    {0x36DE, 0x9313},
    {0x36E0, 0xE291},
    {0x36E2, 0x31B2},
    {0x36E4, 0x786D},
    {0x36E6, 0x896F},
    {0x36E8, 0xF073},
    {0x36EA, 0x90F4},
    {0x36EC, 0x0976},
    {0x36EE, 0x8D54},
    {0x36F0, 0x082F},
    {0x36F2, 0xDF17},
    {0x36F4, 0xF1B4},
    {0x36F6, 0x1A3B},
    {0x36F8, 0xC7F1},
    {0x36FA, 0xE650},
    {0x36FC, 0xE778},
    {0x36FE, 0xFF96},
    {0x3700, 0x755B},
    {0x3702, 0x24B0},
    {0x3704, 0xE253},
    {0x3706, 0xBAB8},
    {0x3708, 0xD4D5},
    {0x370A, 0x437B},
    {0x370C, 0xA5D4},
    {0x370E, 0x4FD2},
    {0x3710, 0xD957},
    {0x3712, 0x9316},
    {0x3714, 0x1E3B},
    {0x3644, 0x0320},
    {0x3642, 0x0258},
    {0x3210, 0x01B8},    

    {0x3400, 0x7A28},
};
struct mt9d113_i2c_reg_conf mt9d113_init_reg_config_byd_settings[] =
{
    {0x0014, 0x2545}, // PLL_CONTROL was x2545
    {0x0010, 0x0115}, // PLL_DIVIDERS
    {0x0012, 0x00F5}, // PLL_P_DIVIDERS
    {0x0014, 0x2547}, // PLL_CONTROL
    {0x0014, 0x2447}, // PLL_CONTROL
    {0x0014, 0x2047}, // PLL_CONTROL
    {0x0014, 0x2046}, // PLL_CONTROL
    {0x001A, 0x0058}, // RESET_AND_MISC_CONTROL
    {0x0018, 0x4028}, // STANDBY_CONTROL
    {0x321C, 0x0000}, // OFIFO_CONTROL_STATUS

    {0x3400, 0x7820},
};
struct mt9d113_i2c_reg_conf mt9d113_init_reg_config_byd_settings_3[] =
{
    {0x098C, 0xA103}, // MCU_ADDRESS [SEQ_CMD]
    {0x0990, 0x0006}, // MCU_DATA_0
    {0x0012, 0x00F5},

    {0x0018, 0x0028},
    {0x3400, 0x7A28},
};

const static struct mt9d113_i2c_reg_conf mt9d113_init_reg_sensor_start_settings[] =
{
    {0x0014, 0x2545}, // PLL_CONTROL was x2545
    {0x0010, 0x0115}, // PLL_DIVIDERS
    {0x0012, 0x00F5}, // PLL_P_DIVIDERS
    {0x0014, 0x2547}, // PLL_CONTROL
    {0x0014, 0x2447}, // PLL_CONTROL
    {0x0014, 0x2047}, // PLL_CONTROL
    {0x0014, 0x2046}, // PLL_CONTROL
    {0x001A, 0x0058}, // RESET_AND_MISC_CONTROL
    {0x0018, 0x4028}, // STANDBY_CONTROL
    {0x321C, 0x0000}, // OFIFO_CONTROL_STATUS

    {0x3400, 0x7A28},
};

struct mt9d113_i2c_reg_conf mt9d113_effect_off_reg_config_settings[] =
{
    {0x098C, 0x2759},
    {0x0990, 0x6440},
    {0x098C, 0x275B},
    {0x0990, 0x6440},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};
struct mt9d113_i2c_reg_conf mt9d113_effect_mono_reg_config_settings[] =
{
    {0x098C, 0x2759},
    {0x0990, 0x6441},
    {0x098C, 0x275B},
    {0x0990, 0x6441},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};

struct mt9d113_i2c_reg_conf mt9d113_effect_negative_reg_config_settings[] =
{
    {0x098C, 0x2759},
    {0x0990, 0x6443},
    {0x098C, 0x275B},
    {0x0990, 0x6443},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};
#if 0
struct mt9d113_i2c_reg_conf mt9d113_effect_solarize_reg_config_settings[] =
{
    {0x098C, 0x2759},
    {0x0990, 0x3244},
    {0x098C, 0x275B},
    {0x0990, 0x3244},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};
#endif

struct mt9d113_i2c_reg_conf mt9d113_effect_sepia_reg_config_settings[] =
{
    {0x098C, 0x2763},
    {0x0990, 0xCE1A},
    {0x098C, 0x2759},    
    {0x0990, 0x6442},
    {0x098C, 0x275B},
    {0x0990, 0x6442},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};
struct mt9d113_i2c_reg_conf mt9d113_effect_aqua_reg_config_settings[] =
{
    {0x098C, 0x2763},
    {0x0990, 0xE2E2},
    {0x098C, 0x2759},    
    {0x0990, 0x6442},
    {0x098C, 0x275B},
    {0x0990, 0x6442},
    {0x098C, 0xA103},
    {0x0990, 0x0006},
};
struct mt9d113_i2c_reg_conf mt9d113_effect_whiteboard_reg_config_settings[] =
{};
struct mt9d113_i2c_reg_conf mt9d113_effect_blackboard_reg_config_settings[] =
{};

/*modify the error preview settings*/
struct mt9d113_i2c_reg_conf mt9d113_preview_reg_config_settings[] =
{
    {0x098C, 0x2739},            // MCU_ADDRESS [MODE_CROP_X0_A]
    {0x0990, 0x0000},            // MCU_DATA_0
    {0x098C, 0x273B},            // MCU_ADDRESS [MODE_CROP_X1_A]
    {0x0990, 0x031F},            // MCU_DATA_0
    {0x098C, 0x273D},            // MCU_ADDRESS [MODE_CROP_Y0_A]
    {0x0990, 0x0000},            // MCU_DATA_0
    {0x098C, 0x273F},            // MCU_ADDRESS [MODE_CROP_Y1_A]
    {0x0990, 0x0257},            // MCU_DATA_0
    {0x098C, 0x2703},            // MCU_ADDRESS [MODE_OUTPUT_WIDTH_A]
    {0x0990, 0x0320},            // MCU_DATA_0
    {0x098C, 0x2705},            // MCU_ADDRESS [MODE_OUTPUT_HEIGHT_A]
    {0x0990, 0x0258},            // MCU_DATA_0
    {0x098C, 0xA115},
    {0x0990, 0x0000},
    {0x098C, 0xA103},
    {0x0990, 0x0001},
};

struct mt9d113_i2c_reg_conf mt9d113_snapshot_reg_config_settings[] =
{
    {0x098C, 0xA115},
    {0x0990, 0x0002},
    {0x098C, 0xA103},
    {0x0990, 0x0002},
};

struct mt9d113_i2c_reg_conf mt9d113_wb_auto_reg_config_settings[] =
{
    {0x098C, 0xA11F},
    {0x0990, 0x0001},
    {0x098C, 0xA103},
    {0x0990, 0x0005},
    {0x098C, 0xA355},
    {0x0990, 0x000A},
    {0x098C, 0xA34A},
    {0x0990, 0x0059},
    {0x098C, 0xA34B},
    {0x0990, 0x00C8},
    {0x098C, 0xA34C},
    {0x0990, 0x0059},
    {0x098C, 0xA34D},
    {0x0990, 0x00A6},
};

/*INCANDESCENT*/
struct mt9d113_i2c_reg_conf mt9d113_wb_a_reg_config_settings[] =
{
    {0x098C, 0xA11F},
    {0x0990, 0x0000},
    {0x098C, 0xA103},
    {0x0990, 0x0005},
    {0x098C, 0xA353},
    {0x0990, 0x0000},
    {0x098C, 0xA34E},
    {0x0990, 0x0086},
    {0x098C, 0xA34F},
    {0x0990, 0x0080},
    {0x098C, 0xA350},
    {0x0990, 0x0092},
    {0x098C, 0xA34A},
    {0x0990, 0x0072},
    {0x098C, 0xA34B},
    {0x0990, 0x0072},
    {0x098C, 0xA34C},
    {0x0990, 0x00A0},
    {0x098C, 0xA34D},
    {0x0990, 0x00A0},
};

/*FLUORESCENT*/
struct mt9d113_i2c_reg_conf mt9d113_wb_tl84_reg_config_settings[] =
{
    {0x098C, 0xA11F},
    {0x0990, 0x0000},
    {0x098C, 0xA103},
    {0x0990, 0x0005},
    {0x098C, 0xA353},
    {0x0990, 0x0032},
    {0x098C, 0xA34E},
    {0x0990, 0x008C},
    {0x098C, 0xA34F},
    {0x0990, 0x0080},
    {0x098C, 0xA350},
    {0x0990, 0x0080},
    {0x098C, 0xA34A},
    {0x0990, 0x008C},
    {0x098C, 0xA34B},
    {0x0990, 0x008C},
    {0x098C, 0xA34C},
    {0x0990, 0x0080},
    {0x098C, 0xA34D},
    {0x0990, 0x0080},
};

struct mt9d113_i2c_reg_conf mt9d113_wb_f_reg_config_settings[] =
{};


/*CLOUDY_DAYLIGHT*/
struct mt9d113_i2c_reg_conf mt9d113_wb_d65_reg_config_settings[] =
{
    {0x098C, 0xA11F},
    {0x0990, 0x0000},
    {0x098C, 0xA103},
    {0x0990, 0x0005},
    {0x098C, 0xA353},
    {0x0990, 0x007F},
    {0x098C, 0xA34E},// MCU_ADDRESS [AWB_GAIN_R]
    {0x0990, 0x00AF},// MCU_DATA_0 93
    {0x098C, 0xA34F},// MCU_ADDRESS [AWB_GAIN_G]
    {0x0990, 0x0081},// MCU_DATA_0
    {0x098C, 0xA350},// MCU_ADDRESS [AWB_GAIN_B]
    {0x0990, 0x0064},// MCU_DATA_0
    {0x098C, 0xA34A},
    {0x0990, 0x0080},
    {0x098C, 0xA34B},
    {0x0990, 0x0080},
    {0x098C, 0xA34C},
    {0x0990, 0x006E},
    {0x098C, 0xA34D},
    {0x0990, 0x006E},
};

/*DAYLIGHT*/
struct mt9d113_i2c_reg_conf mt9d113_wb_d50_reg_config_settings[] =
{

    {0x098E, 0xA11F},
    {0x0990, 0x0000},
    {0x098C, 0xA103},
    {0x0990, 0x0005},
    {0x098C, 0xA353},
    {0x0990, 0x007F},
    {0x098C, 0xA34E},// MCU_ADDRESS [AWB_GAIN_R]
    {0x0990, 0x009A},// MCU_DATA_0
    {0x098C, 0xA34F},// MCU_ADDRESS [AWB_GAIN_G]
    {0x0990, 0x0080},// MCU_DATA_0
    {0x098C, 0xA350},// MCU_ADDRESS [AWB_GAIN_B]
    {0x0990, 0x007A},// MCU_DATA_0
    {0x098C, 0xA34A},
    {0x0990, 0x007D},
    {0x098C, 0xA34B},
    {0x0990, 0x007D},
    {0x098C, 0xA34C},
    {0x0990, 0x0078},
    {0x098C, 0xA34D},
    {0x0990, 0x0078},
};

struct mt9d113_reg mt9d113_regs =
{
    .mt9d113_init_reg_config_byd               = mt9d113_init_reg_config_byd_settings,
    .mt9d113_init_reg_config_byd_size          = mt9d113_ARRAY_SIZE_2(mt9d113_init_reg_config_byd_settings),
    .mt9d113_init_reg_config_byd_2             = mt9d113_init_reg_config_byd_settings_2,
    .mt9d113_init_reg_config_byd_2_size        = mt9d113_ARRAY_SIZE_2(mt9d113_init_reg_config_byd_settings_2),
    .mt9d113_init_reg_config_byd_3             = mt9d113_init_reg_config_byd_settings_3,
    .mt9d113_init_reg_config_byd_3_size        = mt9d113_ARRAY_SIZE_2(mt9d113_init_reg_config_byd_settings_3),
    .mt9d113_init_reg_sensor_start             = mt9d113_init_reg_sensor_start_settings,
    .mt9d113_init_reg_sensor_start_size        = mt9d113_ARRAY_SIZE_2(mt9d113_init_reg_sensor_start_settings),
    .mt9d113_effect_off_reg_config             = mt9d113_effect_off_reg_config_settings,
    .mt9d113_effect_off_reg_config_size        = mt9d113_ARRAY_SIZE_2(mt9d113_effect_off_reg_config_settings),
    .mt9d113_effect_mono_reg_config            = mt9d113_effect_mono_reg_config_settings,
    .mt9d113_effect_mono_reg_config_size       = mt9d113_ARRAY_SIZE_2(mt9d113_effect_mono_reg_config_settings),
    .mt9d113_effect_negative_reg_config        = mt9d113_effect_negative_reg_config_settings,
    .mt9d113_effect_negative_reg_config_size   = mt9d113_ARRAY_SIZE_2(mt9d113_effect_negative_reg_config_settings),
    .mt9d113_effect_sepia_reg_config           = mt9d113_effect_sepia_reg_config_settings,
    .mt9d113_effect_sepia_reg_config_size      = mt9d113_ARRAY_SIZE_2(mt9d113_effect_sepia_reg_config_settings),
    .mt9d113_effect_aqua_reg_config            = mt9d113_effect_aqua_reg_config_settings,
    .mt9d113_effect_aqua_reg_config_size       = mt9d113_ARRAY_SIZE_2(mt9d113_effect_aqua_reg_config_settings),
    .mt9d113_effect_whiteboard_reg_config      = mt9d113_effect_whiteboard_reg_config_settings,
    .mt9d113_effect_whiteboard_reg_config_size = mt9d113_ARRAY_SIZE_2(mt9d113_effect_whiteboard_reg_config_settings),
    .mt9d113_effect_blackboard_reg_config      = mt9d113_effect_blackboard_reg_config_settings,
    .mt9d113_effect_blackboard_reg_config_size = mt9d113_ARRAY_SIZE_2(mt9d113_effect_blackboard_reg_config_settings),
    .mt9d113_preview_reg_config                = mt9d113_preview_reg_config_settings,
    .mt9d113_preview_reg_config_size           = mt9d113_ARRAY_SIZE_2(mt9d113_preview_reg_config_settings),
    .mt9d113_snapshot_reg_config               = mt9d113_snapshot_reg_config_settings,
    .mt9d113_snapshot_reg_config_size          = mt9d113_ARRAY_SIZE_2(mt9d113_snapshot_reg_config_settings),
    .mt9d113_wb_auto_reg_config                = mt9d113_wb_auto_reg_config_settings,
    .mt9d113_wb_auto_reg_config_size           = mt9d113_ARRAY_SIZE_2(mt9d113_wb_auto_reg_config_settings),
    .mt9d113_wb_a_reg_config                   = mt9d113_wb_a_reg_config_settings,
    .mt9d113_wb_a_reg_config_size              = mt9d113_ARRAY_SIZE_2(mt9d113_wb_a_reg_config_settings),
    .mt9d113_wb_tl84_reg_config                = mt9d113_wb_tl84_reg_config_settings,
    .mt9d113_wb_tl84_reg_config_size           = mt9d113_ARRAY_SIZE_2(mt9d113_wb_tl84_reg_config_settings),
    .mt9d113_wb_f_reg_config                   = mt9d113_wb_f_reg_config_settings,
    .mt9d113_wb_f_reg_config_size              = mt9d113_ARRAY_SIZE_2(mt9d113_wb_f_reg_config_settings),
    .mt9d113_wb_d65_reg_config                 = mt9d113_wb_d65_reg_config_settings,
    .mt9d113_wb_d65_reg_config_size            = mt9d113_ARRAY_SIZE_2(mt9d113_wb_d65_reg_config_settings),
    .mt9d113_wb_d50_reg_config                 = mt9d113_wb_d50_reg_config_settings,
    .mt9d113_wb_d50_reg_config_size            = mt9d113_ARRAY_SIZE_2(mt9d113_wb_d50_reg_config_settings),
};

