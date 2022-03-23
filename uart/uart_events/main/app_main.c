#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "dev_uart.h"
#include "output_iot.h"

static const char *TAG = "MAIN";

void uart_data_cb(uint8_t *data, uint16_t length)
{
    if(strstr((char*)data, "ON")){
        uart_put((uint8_t*)"LED ON",6);
        output_io_set_level(2, 1);
    }
    else if(strstr((char*)data, "OFF")){
        uart_put((uint8_t*)"LED OFF",7);
        output_io_set_level(2, 0);
    }
}

void app_main(void)
{
    uart_set_callback(uart_data_cb);
    uart_init();
    output_io_create(2);
}
