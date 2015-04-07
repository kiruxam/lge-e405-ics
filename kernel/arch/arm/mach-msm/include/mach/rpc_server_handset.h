/* Copyright (c) 2009-2010, Code Aurora Forum. All rights reserved.
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

#ifndef __ASM_ARCH_MSM_RPC_SERVER_HANDSET_H
#define __ASM_ARCH_MSM_RPC_SERVER_HANDSET_H

struct msm_handset_platform_data {
	const char *hs_name;
	uint32_t pwr_key_delay_ms; /* default 500ms */
};

void report_headset_status(bool connected);

//LGE_CHANGE_S, [youngbae.choi@lge.com] , 2011-12-08
#ifdef CONFIG_MACH_LGE
void rpc_server_hs_register_callback(void *callback_func);
#endif
//LGE_CHANGE_E, [youngbae.choi@lge.com] , 2011-12-08
#endif