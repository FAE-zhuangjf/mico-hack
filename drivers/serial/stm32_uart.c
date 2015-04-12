/*
 * Created by zhuangjf, 2015/4/2
 * All Rights Reserved
 */

#include <mico/init.h>

#include <types.h>

static int uart_send(uint8_t *buffer, uint32_t length)
{
	return length;
}

static int uart_recv(uint8_t *buffer, uint32_t length)
{
	return length;
}

static int uart_ioctrl(uint8_t type, void *arg)
{
	return 0;
}

static int stm32_uart_init(void)
{
	return 0;
}

module_init(stm32_uart_init);