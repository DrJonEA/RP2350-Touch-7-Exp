#ifndef __BSP_RS485_H
#define __BSP_RS485_H

#include <stdio.h>
#include "pico/stdlib.h"


#ifdef __cplusplus
extern "C" {
#endif

void bsp_rs485_init(uint baudrate);
void on_uart_rx(void);

#ifdef __cplusplus
}
#endif

#endif