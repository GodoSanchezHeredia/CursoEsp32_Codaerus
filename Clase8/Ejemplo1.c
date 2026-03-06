#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/uart.h"
#include "string.h"
#include <esp_adc/adc_oneshot.h>
#include <driver/gpio.h>

void app_main(void)
{
    /************************* ADC *****************/
    adc_oneshot_unit_handle_t adc;
    adc_oneshot_unit_init_cfg_t init = {
        .unit_id = ADC_UNIT_1
    };
    adc_oneshot_new_unit(&init,&adc);
    adc_oneshot_chan_cfg_t cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12  //0-4095
    };
    adc_oneshot_config_channel(adc,ADC_CHANNEL_6,&cfg); //GPIO34 
    adc_oneshot_config_channel(adc,ADC_CHANNEL_4,&cfg); //GPIO32
    uint16_t pot1, pot2;
    /***********************************************/

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_driver_install(UART_NUM_0,256,256,0,NULL,0);
    uart_param_config(UART_NUM_0, &uart_config);


    ledc_channel_config_t channel_conf = {
            .gpio_num = 2, //GPIO2
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel = LEDC_CHANNEL_0, //CANAL0 del PWM
            .duty = 0,
            .timer_sel = LEDC_TIMER_0
        };
        ledc_channel_config(&channel_conf);

        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);





    char msg[30];
    uint8_t data;

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    while(1){

        if (uart_read_bytes(UART_NUM_0, &data, 1, 100 / portTICK_PERIOD_MS) )
        {
            if(data == 'a'){ 
                gpio_set_level(GPIO_NUM_2, 1);
            }
            if(data == 'b'){
                gpio_set_level(GPIO_NUM_2, 0);
            }
        }
        
        adc_oneshot_read(adc,ADC_CHANNEL_6,&pot1); //GPIO34 
        adc_oneshot_read(adc,ADC_CHANNEL_4,&pot2); //GPIO32
        snprintf(msg,30,"%d,%d\n",pot1,pot2); // "100,30"
        uart_write_bytes(UART_NUM_0, msg, strlen(msg));
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}