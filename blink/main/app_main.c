#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "sdkconfig.h"
#include "output_dev.h"
#include "input_dev.h"

// task, soft timer, event group, event loop, queue
EventGroupHandle_t xCreatedEventGroup;

#define BUTTON_PRESS_BIT	( 1 << 0 )
#define BUTTON_RELEASE_BIT	( 1 << 1 )
#define SENSOR_READED_BIT	( 1 << 2 )

void button_cb(int pin)
{
    // xEventGroupSetBits(xCreatedEventGroup, BUTTON_PRESS_BIT);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Set bit 0 and bit 4 in xEventGroup. */
    xEventGroupSetBitsFromISR(
                                xCreatedEventGroup,   /* The event group being updated. */
                                BUTTON_PRESS_BIT, /* The bits being set. */
                                &xHigherPriorityTaskWoken );  

    if(xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR( );
    }
}

void vTaskCode( void * pvParameters )
{
    for( ;; )
    {
        EventBits_t  uxBits = xEventGroupWaitBits(
                                                    xCreatedEventGroup,   /* The event group being tested. */
                                                    BUTTON_PRESS_BIT | BUTTON_RELEASE_BIT | SENSOR_READED_BIT, /* The bits within the event group to wait for. */
                                                    pdTRUE,        /* BIT_0 & BIT_4 should be cleared before returning. */
                                                    pdFALSE,       /* Don't wait for both bits, either bit will do. */
                                                    3000/portTICK_PERIOD_MS );/* Wait a maximum of 100ms for either bit to be set. */
        if(uxBits & BUTTON_PRESS_BIT)
        {
            printf("Button Pressed\n");
        }
    }
}

void app_main(void)
{
    output_create(2);
    input_create(0, HI_TO_LO);
    input_set_callback(button_cb);
    xCreatedEventGroup = xEventGroupCreate();
    xTaskCreate(
                    vTaskCode,       /* Function that implements the task. */
                    "vTaskCode",          /* Text name for the task. */
                    2048,      /* Stack size in words, not bytes. */
                    NULL,    /* Parameter passed into the task. */
                    4,/* Priority at which the task is created. */
                    NULL );

}
