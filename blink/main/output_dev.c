#include "output_dev.h"
#include "driver/gpio.h"

void output_create(int pin)
{
    gpio_pad_select_gpio(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT);    
}

void output_set(int pin)
{
    gpio_set_level(pin, 1);
}

void output_clear(int pin)
{
    gpio_set_level(pin, 0);
}

void output_toggle(int pin)
{
    int state = gpio_get_level(pin);
    if(state){
        gpio_set_level(pin, 0);
    }
    else{
        gpio_set_level(pin, 1);
    }
}