#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>
#include <driver/uart.h>


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
        .duty_resolution = LEDC_TIMER_10_BIT
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
    printf("Valor invalido\n");
    while(1){
     

        if(uart_read_bytes(UART_NUM_0,&data,1,1000)){


            if (data == '*')
            {
                /* code */
                buffer[index] = '\0';
                duty = atoi(buffer);
                if (duty >=0 && duty <=1023){
                    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,(uint32_t)duty);
                    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
                    printf("Duty Recibido: %d\n",duty);

                }else{
                    printf("Valor invalido\n");
                }

                index = 0;
                    
            }else{
                buffer[index++] = data;
            }
       
        }

          
    }
}