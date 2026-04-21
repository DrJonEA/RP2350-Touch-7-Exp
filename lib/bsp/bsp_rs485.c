#include "bsp_rs485.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <string.h>

#define BSP_RS485_UART_ID uart1
#define BSP_RS485_UART_TX_PIN 8
#define BSP_RS485_UART_RX_PIN 9

const uint8_t tx_buffer[8] = {0x12,0x34,0x56,0x78,0x87,0x65,0x43,0x21};
static uint8_t rx_buffer[8];

void on_uart_rx(void)
{
    uint8_t cnt = 0;
    for (cnt = 0; uart_is_readable(BSP_RS485_UART_ID); cnt++)
    {
        if(cnt == 8)
        {
            printf("Please send data with a length not exceeding 8 bytes for testing.\n");
            break;
        }
        char get = uart_getc(BSP_RS485_UART_ID);
        rx_buffer[cnt] = get;
    }
    if (cnt > 0)
    {
        printf("UART1 Receive success\r\n");
    }
    else
    {
        printf("UART1 Receive failure\r\n");
    }
    for (size_t i = 0; i < sizeof(rx_buffer); i++)
    {
        printf("%x ",rx_buffer[i]);
    }
    printf("\n");
    memset(rx_buffer, 0, sizeof(rx_buffer));
    sleep_ms(50);
    uart_write_blocking(BSP_RS485_UART_ID, tx_buffer, sizeof(tx_buffer));
    sleep_ms(50);
}

void bsp_rs485_init(uint baudrate)
{
    // Initialize UART
    uart_init(BSP_RS485_UART_ID, baudrate);
    
    // Set GPIO function
    gpio_set_function(BSP_RS485_UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(BSP_RS485_UART_RX_PIN, GPIO_FUNC_UART);
}
