#include <stdio.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
uint8_t cx = 0;

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    while (1)
    {
        /* code */
        if (scanf("%c", &cx)>0)
        {
          if (cx == 'A')
          {
            gpio_set_level(GPIO_NUM_2, 1);
          }
          if (cx == 'B')
          {
            /* code */
            gpio_set_level(GPIO_NUM_2, 0);
          }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);

    }
    

    printf("Hello World!\n");

}
