/*
 * Created by zhuangjf, 2015/4/3
 * All Rights Reserved
 */

#include <types.h>

#define SDIO_TransferDir_ToCard             ((uint32_t)0x00000000)
#define SDIO_TransferDir_ToSDIO             ((uint32_t)0x00000002)

/*
 * SDIO specific constants
 */
typedef enum
{
    SDIO_CMD_0  =  0,
    SDIO_CMD_3  =  3,
    SDIO_CMD_5  =  5,
    SDIO_CMD_7  =  7,
    SDIO_CMD_52 = 52,
    SDIO_CMD_53 = 53,
    __MAX_VAL   = 64
} sdio_command_t;

typedef enum
{
    SDIO_BLOCK_MODE = ( 0 << 2 ), /* These are STM32 implementation specific */
    SDIO_BYTE_MODE  = ( 1 << 2 )  /* These are STM32 implementation specific */
} sdio_transfer_mode_t;

typedef enum
{
    SDIO_1B_BLOCK    =  1,
    SDIO_2B_BLOCK    =  2,
    SDIO_4B_BLOCK    =  4,
    SDIO_8B_BLOCK    =  8,
    SDIO_16B_BLOCK   =  16,
    SDIO_32B_BLOCK   =  32,
    SDIO_64B_BLOCK   =  64,
    SDIO_128B_BLOCK  =  128,
    SDIO_256B_BLOCK  =  256,
    SDIO_512B_BLOCK  =  512,
    SDIO_1024B_BLOCK = 1024,
    SDIO_2048B_BLOCK = 2048
} sdio_block_size_t;

typedef enum
{
    RESPONSE_NEEDED,
    NO_RESPONSE
} sdio_response_needed_t;

/**
 * Transfer direction for the mico platform bus interface
 */
typedef enum
{
    /* If updating this enum, the bus_direction_mapping variable will also need to be updated */
    BUS_READ,
    BUS_WRITE
} bus_transfer_direction_t;

uint32_t  app_stack_size = 6 * 1024;
uint32_t mico_tick_rate_hz = 100000000;
uint32_t mico_cpu_clock_hz = 100000000;
uint32_t mico_nmode_enable = true;

bool host_platform_is_in_interrupt_context(void)
{
	return true;
}

/* config power and reset IO */
int host_platform_init(void)
{
    return 0;
}

int host_platform_deinit(void)
{
    return 0;
}

int host_platform_bus_init(void)
{
    return 0;
}

int host_platform_init_wlan_powersave_clock(void)
{
    return 0;
}

int host_platform_deinit_wlan_powersave_clock(void)
{
    return 0;
}

int host_platform_sdio_transfer( bus_transfer_direction_t direction, sdio_command_t command, sdio_transfer_mode_t mode, sdio_block_size_t block_size, uint32_t argument, /*@null@*/ uint32_t* data, uint16_t data_size, sdio_response_needed_t response_expected, /*@out@*/ /*@null@*/ uint32_t* response )
{
    return 0;
}

void host_platform_power_wifi(bool power_enable)
{
	/* IO low / high */
}

void host_platform_reset_wifi(bool reset)
{
	/* */
}

int host_platform_sdio_enumerate(void)
{
	return 0;
}

void host_platform_enable_high_speed_sdio(void)
{

}

uint8_t host_platform_get_oob_interrupt_pin(void)
{
    return 0;
}

int host_enable_oob_interrupt(void)
{
    return 0;
}

uint32_t platform_get_wifi_image_size(void)
{
    return 0;
}

uint32_t platform_get_wifi_image(uint8_t *buffer, uint32_t size, uint32_t offset)
{
    return 0;
}
