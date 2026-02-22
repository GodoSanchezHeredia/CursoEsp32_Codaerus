#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>

//maquino estado , contador binario

#define LED1 16
#define LED2 5
#define LED3 4
#define LED4 18

gpio_num_t leds[] = {LED1,LED2,LED3,LED4};

typedef void (*state_function)(void);

void state_init(void);
void state_adelante(void);
void state_atras(void);
void state_pause(void);

state_function state;


void state_init(void){

  for(int i=0;i<4;i++){
    gpio_set_direction(leds[i],GPIO_MODE_OUTPUT);
  }
  state = state_adelante;
}

void state_adelante(void){

 for(int i=0;i<4;i++){
    gpio_set_level(leds[i],1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(leds[i],0);
  }
  state = state_atras;
}


void state_atras(void){
 for(int i=3;i>=0;i--){
    gpio_set_level(leds[i],1);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(leds[i],0);
  }
  state = state_pause;

}


void state_pause(void){
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  state = state_adelante;

}



void app_main() {
  printf("Clase GPIO OUTPUT!\n");


  state = state_init;

  while (true) {

    state();
    
  }
}
