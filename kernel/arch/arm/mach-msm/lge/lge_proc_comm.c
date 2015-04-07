/* 
 * arch/arm/mach-msm/lge/lge_proc_comm.c
 *
 * Copyright (C) 2010 LGE, Inc
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <mach/board_lge.h>
#include "../proc_comm.h"

/* LGE_CHANGE_S, [20120712][youngbae.choi@lge.com]
 * For HW reset dectected enable/disable */
static int hw_reset_detect = 0;
/* LGE_CHANGE_E, [20120712][youngbae.choi@lge.com]*/

#if 1 //#if defined(CONFIG_LGE_DETECT_PIF_PATCH)
unsigned lge_get_pif_info(void)
{
	int err;
	unsigned pif_value = -1;
	unsigned cmd_pif = 8;

	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &pif_value, &cmd_pif);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed\n",
		       __func__);
		return err;
	}
	
	return pif_value;
}
EXPORT_SYMBOL(lge_get_pif_info);

unsigned lge_get_lpm_info(void)
{
	int err;
	unsigned low_power_mode = 0;
	unsigned cmd_lpm = 7;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &low_power_mode, &cmd_lpm);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed\n",
		       __func__);
		return err;
	}

	return low_power_mode;
}
EXPORT_SYMBOL(lge_get_lpm_info);
#endif

#ifdef CONFIG_MACH_LGE
unsigned lge_get_batt_volt(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x3;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_batt_volt);

unsigned lge_get_chg_therm(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x9;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_chg_therm);

unsigned lge_get_pcb_version(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xA;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_pcb_version);

unsigned lge_get_chg_curr_volt(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xB;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_chg_curr_volt);

unsigned lge_get_batt_therm(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xC;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_batt_therm);

unsigned lge_get_batt_volt_raw(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xD;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_batt_volt_raw);

#if 1 //#ifdef CONFIG_MACH_MSM7X27_GELATO
unsigned lge_get_chg_stat_reg(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xE;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_chg_stat_reg);

unsigned lge_get_chg_en_reg(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0xF;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_chg_en_reg);


unsigned lge_set_elt_test(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x10;

	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_set_elt_test);

unsigned lge_clear_elt_test(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x11;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_clear_elt_test);


#endif
unsigned lge_get_is_miniOS(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x12;

	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_is_miniOS);

//LGE_CHANGE_S, [hyo.park@lge.com] , 2011-10-10
unsigned lge_get_batt_id(void)
{
	int err;
	unsigned ret = 0;
	unsigned cmd = 0x4;
	
	err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
	if (err < 0) {
		pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
		       __func__, cmd);
		return err;
	}

	return ret;
}
EXPORT_SYMBOL(lge_get_batt_id);
//LGE_CHANGE_E, [hyo.park@lge.com] , 2011-10-10

//LGE_CHANGE_S, [myunghwan.kim@lge.com], 2011-10-27
unsigned lge_get_cable_info(void)
{
    int err;
    unsigned ret = 0;
    unsigned cmd = 0x13;

    err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
    if (err < 0) {
        pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
               __func__, cmd);
        return err;
    }

    return ret;
}
EXPORT_SYMBOL(lge_get_cable_info);
//LGE_CHANGE_E, [myunghwan.kim@lge.com], 2011-10-27

// LGE_CHANGE_E [peter.jung@lge.com], 2012-05-29 [start]
// update a charging status for hidden menu properly
unsigned lge_get_batt_is_charging(void)
{
    int err;
    unsigned ret = 0;
    unsigned cmd = 0x6; /* defined on pmapp_pcil.c at modem */

    err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
    if (err < 0) {
        pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
               __func__, cmd);
        return err;
    }

    return ret;
}
EXPORT_SYMBOL(lge_get_batt_is_charging);
// LGE_CHANGE_E [peter.jung@lge.com], 2012-05-29 [end]

/* LGE_CHANGE_S, [20120712][youngbae.choi@lge.com]
 * For HW reset dectected enable/disable */
#if 1//def CONFIG_LGE_SILENCE_RESET
unsigned lge_hw_reset_enable_disable(int val)
{
    int err;
    unsigned ret = val;
    unsigned cmd = 0x16;

	if(hw_reset_detect == ret)
		return 0;

	hw_reset_detect = ret;	
    err = msm_proc_comm(PCOM_CUSTOMER_CMD2, &ret, &cmd);
    if (err < 0) {
        pr_err("%s: msm_proc_comm(PCOM_CUSTOMER_CMD2) failed. cmd(%d)\n",
               __func__, cmd);
        return err;
    }

    return ret;
}
EXPORT_SYMBOL(lge_hw_reset_enable_disable);
#endif
/* LGE_CHANGE_E, [20120712][youngbae.choi@lge.com]*/
#endif
