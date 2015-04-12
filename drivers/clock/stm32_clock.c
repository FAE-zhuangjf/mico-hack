/*
 * Created by zhuangjf, 2015/4/2
 * All Rights Reserved
 */

#include <mico/init.h>
#include <mico/platform_device.h>

int stm32_clock_probe(struct platform_device *dev)
{
    (void)dev;
}

static struct platform_driver clock_driver =
{
	.probe = stm32_clock_probe,
};

static int stm32_clock_init(void)
{
	return 0;
}

module_init(stm32_clock_init);
