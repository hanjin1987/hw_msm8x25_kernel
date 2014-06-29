/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "msm_fb.h"
#include "mipi_dsi.h"
#include "hw_lcd_common.h"

#define LCD_DEVICE_NAME "mipi_video_nt35517_5inch_qhd"

static lcd_panel_type lcd_panel_qhd = LCD_NONE;

static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* DSI Bit Clock at 474 MHz, 2 lane, RGB888 */
	/* regulator */
	{0x03, 0x01, 0x01, 0x00, 0x00},
	/* timing */
	{0x85, 0x31, 0x13, 0x00, 0x42, 0x48, 0x17, 0x35,
	0x17, 0x3, 0x04, 0x00},
	/* phy ctrl */
	{0x7F, 0x00, 0x00, 0x00},
	/* strength */
	{0xBB, 0x02, 0x06, 0x00},
	/* pll control */
	{0x01, 0xD4, 0x31, 0xD2, 0x00, 0x40, 0x37, 0x62,
	0x01, 0x0F, 0x07,
	0x05, 0x14, 0x03, 0x0, 0x0, 0x0, 0x20, 0x0, 0x02, 0x0},
};

static struct dsi_buf nt35517_tx_buf;
static struct sequence *nt35517_lcd_init_table_debug = NULL;

static struct sequence nt35517_cabc_enable_table[] =
{
	{0x00051,MIPI_DCS_COMMAND,0},
	{0x000ff,TYPE_PARAMETER,0},
	{0x00000,MIPI_TYPE_END,0},  // end flag
};

/* BOE NT35517 5INCH QHD LCD init code */
static struct sequence nt35517_boe_lcd_init_table[] =
{
	//Page 0
	{0xF0,MIPI_GEN_COMMAND,0},
	{0x55,TYPE_PARAMETER,0},
	{0xAA,TYPE_PARAMETER,0},
	{0x52,TYPE_PARAMETER,0},
	{0x08,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	{0xBC,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},

	{0xCC,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	{0xB0,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x0C,TYPE_PARAMETER,0},
	{0x40,TYPE_PARAMETER,0},
	{0x3C,TYPE_PARAMETER,0},
	{0x3C,TYPE_PARAMETER,0},

	{0xB1,MIPI_GEN_COMMAND,0},
	{0xFC,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	{0xB6,MIPI_GEN_COMMAND,0},
	{0x08,TYPE_PARAMETER,0},

	{0xB7,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	{0xBA,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},

	{0xBD,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x41,TYPE_PARAMETER,0},
	{0x10,TYPE_PARAMETER,0},
	{0x37,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},

	{0xE0,MIPI_GEN_COMMAND,0}, //PWM 54.68KHZ
	{0x01,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},

	//Page 1
	{0xF0,MIPI_GEN_COMMAND,0},
	{0x55,TYPE_PARAMETER,0},
	{0xAA,TYPE_PARAMETER,0},
	{0x52,TYPE_PARAMETER,0},
	{0x08,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},

	{0xB0,MIPI_GEN_COMMAND,0}, //AVDD:5.5V
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},

	{0xB6,MIPI_GEN_COMMAND,0}, //AVDD:3.0*
	{0x44,TYPE_PARAMETER,0},
	{0x44,TYPE_PARAMETER,0},
	{0x44,TYPE_PARAMETER,0},

	{0xB1,MIPI_GEN_COMMAND,0}, //AVEE:-5.5V
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},

	{0xB7,MIPI_GEN_COMMAND,0}, //AVEE:-2.0*
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},

	{0xB2,MIPI_GEN_COMMAND,0}, //VCL:-4.0V
	{0x03,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},

	{0xB8,MIPI_GEN_COMMAND,0}, //VCL:-2.0* 30->33
	{0x33,TYPE_PARAMETER,0},
	{0x33,TYPE_PARAMETER,0},
	{0x33,TYPE_PARAMETER,0},

	{0xB3,MIPI_GEN_COMMAND,0}, //VGH:13.5V
	{0x0D,TYPE_PARAMETER,0},
	{0x0D,TYPE_PARAMETER,0},
	{0x0D,TYPE_PARAMETER,0},

	{0xB9,MIPI_GEN_COMMAND,0}, //VGH:AVDD-AVEE+VDDB
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},

	{0xB4,MIPI_GEN_COMMAND,0}, //VGLX:-12V/0A
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},
	{0x0A,TYPE_PARAMETER,0},

	{0xBA,MIPI_GEN_COMMAND,0}, //VGLX:AVEE+VCL-AVDD0
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},
	{0x24,TYPE_PARAMETER,0},

	{0xB5,MIPI_GEN_COMMAND,0},
	{0x07,TYPE_PARAMETER,0},
	{0x07,TYPE_PARAMETER,0},
	{0x07,TYPE_PARAMETER,0},

	{0xBC,MIPI_GEN_COMMAND,0}, //VGMP:5.0V,VGSP:0.3V 00 78 00
	{0x00,TYPE_PARAMETER,0},
	{0x78,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	{0xBD,MIPI_GEN_COMMAND,0}, //VGMN:-5.0V,VGSN:-0.3V
	{0x00,TYPE_PARAMETER,0},
	{0x78,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},

	//Gamma2.2 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	{0xD1,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xD2,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xD3,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xD4,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0xD5,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xD6,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xD7,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xD8,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0xD9,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xDD,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xDE,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xDF,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0xE0,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xE1,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xE2,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xE3,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0xE4,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xE5,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xE6,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xE7,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0xE8,MIPI_GEN_COMMAND,0},
	{0x00,TYPE_PARAMETER,0},
	{0x43,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x6E,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0x9A,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xBA,TYPE_PARAMETER,0},
	{0x00,TYPE_PARAMETER,0},
	{0xD5,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},

	{0xE9,MIPI_GEN_COMMAND,0},
	{0x01,TYPE_PARAMETER,0},
	{0x27,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x61,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0x90,TYPE_PARAMETER,0},
	{0x01,TYPE_PARAMETER,0},
	{0xDA,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x16,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x18,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x4D,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0x85,TYPE_PARAMETER,0},

	{0xEA,MIPI_GEN_COMMAND,0},
	{0x02,TYPE_PARAMETER,0},
	{0xA9,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xDB,TYPE_PARAMETER,0},
	{0x02,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x2F,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x53,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x7B,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0x98,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xC1,TYPE_PARAMETER,0},

	{0xEB,MIPI_GEN_COMMAND,0},
	{0x03,TYPE_PARAMETER,0},
	{0xF9,TYPE_PARAMETER,0},
	{0x03,TYPE_PARAMETER,0},
	{0xFF,TYPE_PARAMETER,0},

	{0x51,MIPI_DCS_COMMAND,10}, // write display brightness
	{0x00,TYPE_PARAMETER,0},   // set to zero

	{0x53,MIPI_DCS_COMMAND,0}, // ctrldisplay1
	{0x24,TYPE_PARAMETER,0},

	{0x55,MIPI_DCS_COMMAND,0}, // ctrldisplay2
	{0x01,TYPE_PARAMETER,0},

	{0x11,MIPI_DCS_COMMAND,10},
	{0x29,MIPI_DCS_COMMAND,120},

	{0x00,MIPI_TYPE_END,10}, //end flag
};

/*lcd resume function*/
static int mipi_nt35517_qhd_lcd_on(struct platform_device *pdev)
{
	boolean para_debug_flag = FALSE;
	uint32 para_num = 0;
	struct msm_fb_data_type *mfd = NULL;
	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	para_debug_flag = lcd_debug_malloc_get_para( "nt35517_lcd_init_table_debug",
			(void**)&nt35517_lcd_init_table_debug,&para_num);

	lcd_reset();
	mipi_set_tx_power_mode(1);  // low power mode
	if( (TRUE == para_debug_flag) && (NULL != nt35517_lcd_init_table_debug))
	{
		process_mipi_table(mfd,&nt35517_tx_buf,nt35517_lcd_init_table_debug,
			para_num, lcd_panel_qhd);
	}
	else
	{
		process_mipi_table(mfd,&nt35517_tx_buf,(struct sequence*)&nt35517_boe_lcd_init_table,
			ARRAY_SIZE(nt35517_boe_lcd_init_table), lcd_panel_qhd);
	}
	mipi_set_tx_power_mode(0);  // high speed mode

	if((TRUE == para_debug_flag)&&(NULL != nt35517_lcd_init_table_debug))
	{
		lcd_debug_free_para((void *)nt35517_lcd_init_table_debug);
	}

	if (!mfd->cont_splash_done)
	{
		mfd->cont_splash_done = 1;

		nt35517_cabc_enable_table[1].reg = 0x00064;
		process_mipi_table(mfd,&nt35517_tx_buf,(struct sequence*)&nt35517_cabc_enable_table,
			ARRAY_SIZE(nt35517_cabc_enable_table), lcd_panel_qhd);

		LCD_DEBUG("%s: cont_splash_done.\n", __func__);
	}

	LCD_DEBUG("leave %s.\n", __func__);
	return 0;
}

/*lcd suspend function*/
static int mipi_nt35517_qhd_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	lcd_reset();

	LCD_DEBUG("leave %s.\n", __func__);
	return 0;
}


#ifdef CONFIG_FB_AUTO_CABC
static struct sequence nt35517_qhd_auto_cabc_set_table[] =
{
	{0x00053,MIPI_DCS_COMMAND,0},
	{0x00024,TYPE_PARAMETER,0},

	{0x00055,MIPI_DCS_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},

	{0x00000,MIPI_TYPE_END,10}, /* the end flag,it don't sent to driver IC */
};

/***************************************************************
Function: nt35517_qhd_config_auto_cabc
Description: Set CABC configuration
Parameters:
	struct msmfb_cabc_config cabc_cfg: CABC configuration struct
Return:
	0: success
***************************************************************/
static int nt35517_qhd_config_auto_cabc(struct msmfb_cabc_config cabc_cfg, struct msm_fb_data_type *mfd)
{
	int ret = 0;

	switch(cabc_cfg.mode)
	{
		case CABC_MODE_UI:
			nt35517_qhd_auto_cabc_set_table[1].reg=0x00024;
			nt35517_qhd_auto_cabc_set_table[3].reg=0x00001;
			break;
		case CABC_MODE_MOVING:
		case CABC_MODE_STILL:
			nt35517_qhd_auto_cabc_set_table[1].reg=0x0002C;
			nt35517_qhd_auto_cabc_set_table[3].reg=0x00003;
			break;
		default:
			LCD_DEBUG("%s: invalid cabc mode: %d\n", __func__, cabc_cfg.mode);
			ret = -EINVAL;
			break;
	}

	if(likely(0 == ret))
	{
		process_mipi_table(mfd,&nt35517_tx_buf,(struct sequence*)&nt35517_qhd_auto_cabc_set_table,
			ARRAY_SIZE(nt35517_qhd_auto_cabc_set_table), lcd_panel_qhd);
	}

	LCD_DEBUG("%s: change cabc mode to %d\n", __func__, cabc_cfg.mode);
	return ret;
}
#endif /* CONFIG_FB_AUTO_CABC */


static int __devinit mipi_nt35517_lcd_probe(struct platform_device *pdev)
{
	msm_fb_add_device(pdev);

	return 0;
}


static void nt35517_set_cabc_backlight(struct msm_fb_data_type *mfd,uint32 bl_level)
{
	nt35517_cabc_enable_table[1].reg = bl_level;

	process_mipi_table(mfd,&nt35517_tx_buf,(struct sequence*)&nt35517_cabc_enable_table,
		ARRAY_SIZE(nt35517_cabc_enable_table), lcd_panel_qhd);
}

static struct platform_driver this_driver = {
	.probe  = mipi_nt35517_lcd_probe,
	.driver = {
		.name   = LCD_DEVICE_NAME,
	},
};

static struct msm_fb_panel_data nt35517_panel_data = {
	.on					= mipi_nt35517_qhd_lcd_on,
	.off				= mipi_nt35517_qhd_lcd_off,
	.set_backlight 		= pwm_set_backlight,
	/* add cabc control backlight */
	.set_cabc_brightness 	= nt35517_set_cabc_backlight,
	#ifdef CONFIG_FB_AUTO_CABC
	.config_cabc = nt35517_qhd_config_auto_cabc,
	#endif
};

static struct platform_device this_device = {
	.name   = LCD_DEVICE_NAME,
	.id	= 0,
	.dev	= {
		.platform_data = &nt35517_panel_data,
	}
};

static __init int mipi_video_nt35517_qhd_init(void)
{
	int ret = 0;
	struct msm_panel_info *pinfo = NULL;

	lcd_panel_qhd = get_lcd_panel_type();

	if (MIPI_VIDEO_NT35517_BOE_5INCH_QHD != lcd_panel_qhd)
	{
		return 0;
	}

	LCD_DEBUG("enter %s.\n", __func__);
	mipi_dsi_buf_alloc(&nt35517_tx_buf, DSI_BUF_SIZE);

	ret = platform_driver_register(&this_driver);
	if (!ret)
	{
		pinfo = &nt35517_panel_data.panel_info;
		pinfo->xres = 540;
		pinfo->yres = 960;
		pinfo->type = MIPI_VIDEO_PANEL;
		pinfo->pdest = DISPLAY_1;
		pinfo->wait_cycle = 0;
		pinfo->bpp = 24;
		pinfo->lcdc.h_back_porch = 60;
		pinfo->lcdc.h_front_porch = 60;
		pinfo->lcdc.h_pulse_width = 8;
		pinfo->lcdc.v_back_porch = 15;
		pinfo->lcdc.v_front_porch = 7;
		pinfo->lcdc.v_pulse_width = 5;
		pinfo->lcdc.border_clr = 0;    /* blk */
		pinfo->lcdc.underflow_clr = 0xff;    /* blue */
		/* number of dot_clk cycles HSYNC active edge is
		delayed from VSYNC active edge */
		pinfo->lcdc.hsync_skew = 0;
		pinfo->bl_max = 255;
		pinfo->bl_min = 30;
		pinfo->fb_num = 3;
		pinfo->clk_rate = 474000000;  // 474M

		pinfo->mipi.mode = DSI_VIDEO_MODE;
		pinfo->mipi.pulse_mode_hsa_he = TRUE;
		pinfo->mipi.hfp_power_stop = TRUE; /* LP-11 during the HFP period */
		pinfo->mipi.hbp_power_stop = TRUE; /* LP-11 during the HBP period */
		pinfo->mipi.hsa_power_stop = TRUE; /* LP-11 during the HSA period */
		/* LP-11 or let Command Mode Engine send packets in
		HS or LP mode for the BLLP of the last line of a frame */
		pinfo->mipi.eof_bllp_power_stop = TRUE;
		/* LP-11 or let Command Mode Engine send packets in
		HS or LP mode for packets sent during BLLP period */
		pinfo->mipi.bllp_power_stop = TRUE;

		pinfo->mipi.traffic_mode = DSI_BURST_MODE;
		pinfo->mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
		pinfo->mipi.vc = 0;
		pinfo->mipi.rgb_swap = DSI_RGB_SWAP_RGB;
		pinfo->mipi.data_lane0 = TRUE;
		pinfo->mipi.data_lane1 = TRUE;
		pinfo->mipi.t_clk_post = 0x7f;
		pinfo->mipi.t_clk_pre = 0x2f;
		pinfo->mipi.stream = 0; /* dma_p */
		pinfo->mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
		pinfo->mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
		pinfo->mipi.frame_rate = 60; /* FIXME */

		pinfo->mipi.dsi_phy_db = &dsi_video_mode_phy_db;
		pinfo->mipi.tx_eot_append = 0x01;

		//pinfo->mipi.dlane_swap = 0x1;

		ret = platform_device_register(&this_device);
		if (ret)
			LCD_DEBUG("%s: failed to register device!\n", __func__);
	}

	return ret;
}

module_init(mipi_video_nt35517_qhd_init);

