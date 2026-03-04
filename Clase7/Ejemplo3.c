#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>

int duty = 0;

void app_main(void)
{


    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 100,
        .duty_resolution = LEDC_TIMER_10_BIT
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t pwm1 = {
        .gpio_num = 2, //GPIO2
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0, //CANAL0 del PWM
        .duty = 0,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&pwm1);

        ledc_channel_config_t pwm2 = {
        .gpio_num = 4, //GPIO4
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1, //CANAL1 del PWM
        .duty = 1023,
        .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&pwm2);

    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);

    ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,1023);
    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);



    while(1){
    
        duty+=50;
        if(duty>1023){
            duty=0;
        }

        //PWM NORMAL

        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);

        //PWM COMPLEMENTARIO
        ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_1,1023-duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_1);


        printf("duty pwm1: %d\n",duty);
        printf("duty pwm2: %d\n",1023-duty);
        vTaskDelay(250/portTICK_PERIOD_MS); 
    }
}