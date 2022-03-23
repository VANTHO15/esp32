#include "input_dev.h"
#include "driver/gpio.h"

input_int_handle_t input_int_handle = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    input_int_handle(gpio_num);
}

void input_create(int pin, input_int_type_t type)
{
    gpio_config_t io_conf;
    //interrupt of rising edge
    io_conf.intr_type = type;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = (1ULL<<pin);
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;

    gpio_config(&io_conf);    

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(pin, gpio_isr_handler, (void*) pin);    
}

void input_set_callback(void *cb)
{
    if(cb){
        input_int_handle = cb;
    }
}