#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>
#include <driver/uart.h>
#include <driver/adc.h>

#define buffer_size 1024
char buffer[20];
int index = 0;
uint8_t data = 0;
int duty = 0;

void app_main(void)
{

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0,buffer_size,0,0,NULL,0);


    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 100,
        .duty_resolution = LEDC_TIMER_12_BIT
    };
    ledc_timer_config(&timer_conf);

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



    adc1_config_width(ADC_WIDTH_BIT_12) ;
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    while(1){
        
        uint16_t potenciometro = adc1_get_raw(ADC1_CHANNEL_6);
        printf("Potenciometro: %u\n",potenciometro);
        
        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,potenciometro);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
        vTaskDelay(100 / portTICK_PERIOD_MS);   
    }
}