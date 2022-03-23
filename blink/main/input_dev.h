#ifndef __INPUT_DEV_H
#define __INPUT_DEV_H

typedef enum {
    LO_TO_HI = 1,
    HI_TO_LO = 2,
    ANY_EDGE = 3 
}   input_int_type_t;

typedef void (*input_int_handle_t) (int pin);
void input_create(int pin, input_int_type_t type);
void input_set_callback(void *cb);

#endif