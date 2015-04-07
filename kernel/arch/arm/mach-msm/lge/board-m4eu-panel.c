#include <linux/err.h>
#include <linux/gpio.h>

#include <asm/mach-types.h>

#include <mach/msm_rpcrouter.h>
#include <mach/rpc_pmapp.h>
#include <mach/board.h>

#include "devices.h"
#include "board-m4eu.h"
#include <mach/board_lge.h>
/* LGE_CHANGE_S : lcd regulator patch
 * 2011-12-21, sinjo.mattappallil@lge.com,
 * vreg is converted to regulator framework.
 */
//#include <mach/vreg.h>
#include <linux/regulator/consumer.h>
/* LGE_CHANGE_E : lcd regulator patch */
#include <linux/fb.h>

#define GPIO_LCD_RESET_N 125

#define REGULATOR_OP(name, op, level)                        \
	do {\
		vreg = regulator_get(0, name);\
		regulator_set_voltage(vreg, level, level);\
		if (regulator_##op(vreg))\
			printk(KERN_ERR "%s: %s vreg operation failed \n",\
			(regulator_##op == regulator_enable) ? "regulator_enable"   \
			: "regulator_disable", name);\
	} while (0)


/* backlight device */
static struct gpio_i2c_pin bl_i2c_pin = {
	.sda_pin = 112,
	.scl_pin = 111,
	.reset_pin = 124,
};

static struct i2c_gpio_platform_data bl_i2c_pdata = {
	.sda_is_open_drain = 0,
	.scl_is_open_drain = 0,
	.udelay = 2,
};

static struct platform_device bl_i2c_device = {
	.name = "i2c-gpio",
	.dev.platform_data = &bl_i2c_pdata,
};

static struct lge_backlight_platform_data bu61800bl_data = {
	.gpio = 124,
	.version = 61800,
};

static struct i2c_board_info bl_i2c_bdinfo[] = {
	[0] = {
		I2C_BOARD_INFO("bu61800bl", 0x76),
		.type = "bu61800bl",
	},
};

static int ebi2_tovis_power_save(int on);
static struct msm_panel_ilitek_pdata ebi2_tovis_panel_data = {
	.gpio = GPIO_LCD_RESET_N,
	.lcd_power_save = ebi2_tovis_power_save,
	.maker_id = PANEL_ID_TOVIS,
	.initialized = 1,
};

static struct platform_device ebi2_tovis_panel_device = {
	.name	= "ebi2_tovis_qvga",
	.id	= 0,
	.dev	= {
		.platform_data = &ebi2_tovis_panel_data,
	}
};

/* input platform device */
static struct platform_device *m4eu_panel_devices[] __initdata = {
	&ebi2_tovis_panel_device,
};

static struct msm_panel_common_pdata mdp_pdata = {
	.gpio = 97,						/*LCD_VSYNC_P*/
	.mdp_rev = MDP_REV_303,
};

static char *msm_fb_vreg[] = {
	"wlan_tcx0",
	"emmc",
};

static int mddi_power_save_on;
static int ebi2_tovis_power_save(int on)
{
	struct regulator *vreg;
	int flag_on = !!on;

	printk(KERN_INFO "%s: on=%d\n", __func__, flag_on);

	if (mddi_power_save_on == flag_on)
		return 0;

	mddi_power_save_on = flag_on;

	if (on) {
		//REGULATOR_OP(msm_fb_vreg[0], enable, 1800000);
		REGULATOR_OP(msm_fb_vreg[1], enable, 2800000);
	} else{
		//REGULATOR_OP(msm_fb_vreg[0], disable, 0);
		REGULATOR_OP(msm_fb_vreg[1], disable, 2800000);
		}
	return 0;
		}

static int m4eu_fb_event_notify(struct notifier_block *self,
	unsigned long action, void *data)
{
	struct fb_event *event = data;
	struct fb_info *info = event->info;
	struct fb_var_screeninfo *var = &info->var;
	if(action == FB_EVENT_FB_REGISTERED) {
		var->width = 43;
		var->height = 58;
	}
	return 0;
}

static struct notifier_block m4eu_fb_event_notifier = {
	.notifier_call	= m4eu_fb_event_notify,
};

static void __init msm_fb_add_devices(void)
{
	msm_fb_register_device("mdp", &mdp_pdata);
	msm_fb_register_device("lcdc", 0);
	msm_fb_register_device("ebi2", 0);
}

void __init msm7x27a_m4eu_init_i2c_backlight(int bus_num)
{
	bl_i2c_device.id = bus_num;
	bl_i2c_bdinfo[0].platform_data = &bu61800bl_data;
	bl_i2c_pin.scl_pin = 111;
	bl_i2c_pin.sda_pin = 112;

	/* workaround for HDK rev_a no pullup */
	lge_init_gpio_i2c_pin_pullup(&bl_i2c_pdata, bl_i2c_pin, &bl_i2c_bdinfo[0]);
	i2c_register_board_info(bus_num, &bl_i2c_bdinfo[0], 1);
	platform_device_register(&bl_i2c_device);
}

void __init lge_add_lcd_devices(void)
{
	if(ebi2_tovis_panel_data.initialized)
		ebi2_tovis_power_save(1);

	fb_register_client(&m4eu_fb_event_notifier);

	platform_add_devices(m4eu_panel_devices, ARRAY_SIZE(m4eu_panel_devices));
	msm_fb_add_devices();
	lge_add_gpio_i2c_device(msm7x27a_m4eu_init_i2c_backlight);
}

