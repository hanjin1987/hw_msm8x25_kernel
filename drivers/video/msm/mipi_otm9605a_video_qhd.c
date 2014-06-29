/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
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

#define LCD_DEVICE_NAME "mipi_video_otm9605a_qhd"

static lcd_panel_type lcd_panel_qhd = LCD_NONE;

static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
	/* DSI Bit Clock at 478 MHz, 2 lane, RGB888 */
	/* regulator */
	{0x03, 0x01, 0x01, 0x00, 0x00},
	/* timing */
	{0x86, 0x32, 0x13, 0x00, 0x43, 0x48, 0x17, 0x35,
	0x17, 0x3, 0x04, 0x00},
	/* phy ctrl */
	{0x7F, 0x00, 0x00, 0x00},
	/* strength */
	{0xBB, 0x02, 0x06, 0x00},
	/* pll control */
	{0x01, 0xD8, 0x31, 0xD2, 0x00, 0x40, 0x37, 0x62,
	0x01, 0x0F, 0x07,
	0x05, 0x14, 0x03, 0x0, 0x0, 0x0, 0x20, 0x0, 0x02, 0x0},
};

static struct dsi_buf otm9605a_tx_buf;
static struct sequence *otm9605a_lcd_init_table_debug = NULL;

static struct sequence otm9605a_cabc_enable_table[] =
{
	{0x00051,MIPI_DCS_COMMAND,0},
	{0x000ff,TYPE_PARAMETER,0},
	{0x00000,MIPI_TYPE_END,0},  // end flag
};

/* TIANMA OTM9605A LCD init code */
static struct sequence otm9605a_tianma_lcd_init_table[] =
{
	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000FF,MIPI_GEN_COMMAND,0},
	{0x00096,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000FF,MIPI_GEN_COMMAND,0},
	{0x00096,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,1},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000A0,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B4,TYPE_PARAMETER,0},
	{0x000C0,MIPI_GEN_COMMAND,0},
	{0x00050,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000C1,MIPI_GEN_COMMAND,0},
	{0x00036,TYPE_PARAMETER,0},
	{0x00066,TYPE_PARAMETER,0}, // 77 --> 66

	/* Modify the paramete of gamma for TM otm9605a  */
	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00089,TYPE_PARAMETER,0},
	{0x000C0,MIPI_GEN_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000C4,MIPI_GEN_COMMAND,0},
	{0x0009C,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000C1,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x000C5,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C5,TYPE_PARAMETER,0},
	{0x000B0,MIPI_GEN_COMMAND,0},
	{0x00003,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00090,TYPE_PARAMETER,0},
	{0x000C5,MIPI_GEN_COMMAND,0},
	{0x00096,TYPE_PARAMETER,0},
	{0x00019,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00079,TYPE_PARAMETER,0},
	{0x00033,TYPE_PARAMETER,0},
	{0x00033,TYPE_PARAMETER,0},
	{0x00034,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000C5,MIPI_GEN_COMMAND,0},
	{0x00096,TYPE_PARAMETER,0},
	{0x00016,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00079,TYPE_PARAMETER,0},
	{0x00033,TYPE_PARAMETER,0},
	{0x00033,TYPE_PARAMETER,0},
	{0x00034,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000D8,MIPI_GEN_COMMAND,0},
	{0x0005F,TYPE_PARAMETER,0},
	{0x0005F,TYPE_PARAMETER,0},
	/* delete VCOM voltage setting */

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B0,TYPE_PARAMETER,0},
	{0x000C5,MIPI_GEN_COMMAND,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000E1,MIPI_GEN_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x0000D,TYPE_PARAMETER,0},
	{0x00014,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00007,TYPE_PARAMETER,0},
	{0x00013,TYPE_PARAMETER,0},
	{0x0000B,TYPE_PARAMETER,0},
	{0x0000A,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00006,TYPE_PARAMETER,0},
	{0x00008,TYPE_PARAMETER,0},
	{0x00008,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00012,TYPE_PARAMETER,0},
	{0x0000f,TYPE_PARAMETER,0},
	{0x0000B,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000E2,MIPI_GEN_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x0000D,TYPE_PARAMETER,0},
	{0x00014,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00007,TYPE_PARAMETER,0},
	{0x00013,TYPE_PARAMETER,0},
	{0x0000B,TYPE_PARAMETER,0},
	{0x0000A,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00006,TYPE_PARAMETER,0},
	{0x00008,TYPE_PARAMETER,0},
	{0x00008,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00012,TYPE_PARAMETER,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x0000B,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00090,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000D0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00055,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000E0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x000CB,MIPI_GEN_COMMAND,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000CC,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000CC,TYPE_PARAMETER,0},
	{0x000C3,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x00025,TYPE_PARAMETER,0},
	{0x00026,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000C,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000A,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00090,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00006,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00025,TYPE_PARAMETER,0},
	{0x00026,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x0000B,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00009,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000D,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B0,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x00026,TYPE_PARAMETER,0},
	{0x00025,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000D,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00009,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000B,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00026,TYPE_PARAMETER,0},
	{0x00025,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000D0,TYPE_PARAMETER,0},
	{0x000CC,MIPI_GEN_COMMAND,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000A,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x0000C,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00006,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x0008B,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00027,TYPE_PARAMETER,0},
	{0x0008A,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00089,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00027,TYPE_PARAMETER,0},
	{0x00088,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00090,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x00039,TYPE_PARAMETER,0},
	{0x0000F,TYPE_PARAMETER,0},
	{0x00027,TYPE_PARAMETER,0},
	{0x00039,TYPE_PARAMETER,0},
	{0x0000E,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00007,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00006,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C1,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B0,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00005,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C2,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00004,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C3,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C4,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C5,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000D0,TYPE_PARAMETER,0},
	{0x000CE,MIPI_GEN_COMMAND,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C6,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00038,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00003,TYPE_PARAMETER,0},
	{0x000C7,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00028,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00080,TYPE_PARAMETER,0},
	{0x000CF,MIPI_GEN_COMMAND,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x00090,TYPE_PARAMETER,0},
	{0x000CF,MIPI_GEN_COMMAND,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000A0,TYPE_PARAMETER,0},
	{0x000CF,MIPI_GEN_COMMAND,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B0,TYPE_PARAMETER,0},
	{0x000CF,MIPI_GEN_COMMAND,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x000F0,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00010,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000C0,TYPE_PARAMETER,0},
	{0x000CF,MIPI_GEN_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00020,TYPE_PARAMETER,0},
	{0x00020,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00002,TYPE_PARAMETER,0},
	{0x00001,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},
	{0x00000,TYPE_PARAMETER,0},

	/* Modify the paramete of gamma for TM otm9605a  */
	{0x00000,MIPI_DCS_COMMAND,0},
	{0x000B1,TYPE_PARAMETER,0},
	{0x000C6,MIPI_GEN_COMMAND,0},
	{0x00005,TYPE_PARAMETER,0},  // set pwm freq more than 45KHz
	/* Modify the paramete of gamma for TM otm9605a  */
	{0x00000,MIPI_DCS_COMMAND,10},
	{0x00000,TYPE_PARAMETER,0},
	{0x000FF,MIPI_GEN_COMMAND,0},
	{0x000FF,TYPE_PARAMETER,0},
	{0x000FF,TYPE_PARAMETER,0},
	{0x000FF,TYPE_PARAMETER,0},

	{0x00051,MIPI_DCS_COMMAND,0}, // write display brightness
	{0x00000,TYPE_PARAMETER,0},   // set to zero

	{0x00053,MIPI_DCS_COMMAND,0}, // ctrldisplay1
	{0x00024,TYPE_PARAMETER,0},

	{0x00055,MIPI_DCS_COMMAND,0}, // ctrldisplay2
	{0x00001,TYPE_PARAMETER,0},

	{0x00011,MIPI_DCS_COMMAND,0},
	{0x00029,MIPI_DCS_COMMAND,120},
	{0x00000,MIPI_TYPE_END,20}, //end flag
};

/*lcd resume function*/
static int mipi_otm9605a_qhd_lcd_on(struct platform_device *pdev)
{
	boolean para_debug_flag = FALSE;
	uint32 para_num = 0;
	struct msm_fb_data_type *mfd = NULL;
	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	para_debug_flag = lcd_debug_malloc_get_para( "otm9605a_lcd_init_table_debug",
			(void**)&otm9605a_lcd_init_table_debug,&para_num);

	lcd_reset();
	mipi_set_tx_power_mode(1);  // low power mode
	if( (TRUE == para_debug_flag) && (NULL != otm9605a_lcd_init_table_debug))
	{
		process_mipi_table(mfd,&otm9605a_tx_buf,otm9605a_lcd_init_table_debug,
			para_num, lcd_panel_qhd);
	}
	else
	{
		process_mipi_table(mfd,&otm9605a_tx_buf,(struct sequence*)&otm9605a_tianma_lcd_init_table,
			ARRAY_SIZE(otm9605a_tianma_lcd_init_table), lcd_panel_qhd);
	}
	mipi_set_tx_power_mode(0);  // high speed mode

	if((TRUE == para_debug_flag)&&(NULL != otm9605a_lcd_init_table_debug))
	{
		lcd_debug_free_para((void *)otm9605a_lcd_init_table_debug);
	}
	
	if (!mfd->cont_splash_done) 
	{
		mfd->cont_splash_done = 1;

		otm9605a_cabc_enable_table[1].reg = 0x00064;
		process_mipi_table(mfd,&otm9605a_tx_buf,(struct sequence*)&otm9605a_cabc_enable_table,
			ARRAY_SIZE(otm9605a_cabc_enable_table), lcd_panel_qhd);

		LCD_DEBUG("%s: cont_splash_done.\n", __func__);
	}
	
	LCD_DEBUG("leave %s.\n", __func__);
	return 0;
}

/*lcd suspend function*/
static int mipi_otm9605a_qhd_lcd_off(struct platform_device *pdev)
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
static struct sequence otm9605a_qhd_auto_cabc_set_table[] =
{
	{0x00053,MIPI_DCS_COMMAND,0},
	{0x00024,TYPE_PARAMETER,0},

	{0x00055,MIPI_DCS_COMMAND,0},
	{0x00001,TYPE_PARAMETER,0},

	{0x00000,MIPI_TYPE_END,0}, /* the end flag,it don't sent to driver IC */
};

/***************************************************************
Function: otm9605a_qhd_config_auto_cabc
Description: Set CABC configuration
Parameters:
	struct msmfb_cabc_config cabc_cfg: CABC configuration struct
Return:
	0: success
***************************************************************/
static int otm9605a_qhd_config_auto_cabc(struct msmfb_cabc_config cabc_cfg, struct msm_fb_data_type *mfd)
{
	int ret = 0;

	switch(cabc_cfg.mode)
	{
		case CABC_MODE_UI:
			otm9605a_qhd_auto_cabc_set_table[1].reg=0x00024;
			otm9605a_qhd_auto_cabc_set_table[3].reg=0x00001;
			break;
		case CABC_MODE_MOVING:
		case CABC_MODE_STILL:
			otm9605a_qhd_auto_cabc_set_table[1].reg=0x0002C;
			otm9605a_qhd_auto_cabc_set_table[3].reg=0x00003;
			break;
		default:
			LCD_DEBUG("%s: invalid cabc mode: %d\n", __func__, cabc_cfg.mode);
			ret = -EINVAL;
			break;
	}

	if(likely(0 == ret))
	{
		process_mipi_table(mfd,&otm9605a_tx_buf,(struct sequence*)&otm9605a_qhd_auto_cabc_set_table,
			ARRAY_SIZE(otm9605a_qhd_auto_cabc_set_table), lcd_panel_qhd);
	}

	LCD_DEBUG("%s: change cabc mode to %d\n", __func__, cabc_cfg.mode);
	return ret;
}
#endif /* CONFIG_FB_AUTO_CABC */


static int __devinit mipi_otm9605a_lcd_probe(struct platform_device *pdev)
{
	msm_fb_add_device(pdev);

	return 0;
}


void otm9605a_set_cabc_backlight(struct msm_fb_data_type *mfd,uint32 bl_level)
{
	otm9605a_cabc_enable_table[1].reg = bl_level;

	process_mipi_table(mfd,&otm9605a_tx_buf,(struct sequence*)&otm9605a_cabc_enable_table,
		ARRAY_SIZE(otm9605a_cabc_enable_table), lcd_panel_qhd);
}

static struct platform_driver this_driver = {
	.probe  = mipi_otm9605a_lcd_probe,
	.driver = {
		.name   = LCD_DEVICE_NAME,
	},
};

static struct msm_fb_panel_data otm9605a_panel_data = {
	.on					= mipi_otm9605a_qhd_lcd_on,
	.off				= mipi_otm9605a_qhd_lcd_off,
	.set_backlight 		= pwm_set_backlight,
	/* add cabc control backlight */
	.set_cabc_brightness 	= otm9605a_set_cabc_backlight,
	#ifdef CONFIG_FB_AUTO_CABC
	.config_cabc = otm9605a_qhd_config_auto_cabc,
	#endif
};

static struct platform_device this_device = {
	.name   = LCD_DEVICE_NAME,
	.id	= 0,
	.dev	= {
		.platform_data = &otm9605a_panel_data,
	}
};

static __init int mipi_video_otm9605a_qhd_init(void)
{
	int ret = 0;
	struct msm_panel_info *pinfo = NULL;

	lcd_panel_qhd = get_lcd_panel_type();

	if (MIPI_VIDEO_OTM9605A_TIANMA_QHD != lcd_panel_qhd)
	{
		return 0;
	}

	LCD_DEBUG("enter %s.\n", __func__);
	mipi_dsi_buf_alloc(&otm9605a_tx_buf, DSI_BUF_SIZE);

	ret = platform_driver_register(&this_driver);
	if (!ret)
	{
		pinfo = &otm9605a_panel_data.panel_info;
		pinfo->xres = 540;
		pinfo->yres = 960;
		pinfo->type = MIPI_VIDEO_PANEL;
		pinfo->pdest = DISPLAY_1;
		pinfo->wait_cycle = 0;
		pinfo->bpp = 24;
		pinfo->lcdc.h_back_porch = 63;
		pinfo->lcdc.h_front_porch = 63;
		pinfo->lcdc.h_pulse_width = 4;
		pinfo->lcdc.v_back_porch = 16;
		pinfo->lcdc.v_front_porch = 15;
		pinfo->lcdc.v_pulse_width = 1;
		pinfo->lcdc.border_clr = 0;	/* blk */
		pinfo->lcdc.underflow_clr = 0xff;	/* blue */
		/* number of dot_clk cycles HSYNC active edge is
		delayed from VSYNC active edge */
		pinfo->lcdc.hsync_skew = 0;
		pinfo->bl_max = 255;
		pinfo->bl_min = 30;
		pinfo->fb_num = 3;
		pinfo->clk_rate = 478000000;  // 478

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

module_init(mipi_video_otm9605a_qhd_init);

