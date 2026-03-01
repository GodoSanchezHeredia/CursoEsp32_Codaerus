#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

void app_main(void)
{
    adc1_config_width(ADC_WIDTH_BIT_12); //CONFIGURAMOS A 12 BITS
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12); //CONFIGURAMOS EL CANAL 6 CON ATTENUACION 11 DB
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12); //CONFIGURAMOS EL CANAL 4 CON ATTENUACION 11 DB
    while(1)
    {
        uint16_t pot1 = adc1_get_raw(ADC1_CHANNEL_6); 
        uint16_t pot2 = adc1_get_raw(ADC1_CHANNEL_4);

        printf("Pot 1: %u - Pot 2: %u\n", pot1, pot2);
        float volt1 = (float)pot1 * 3.3 / 4095;
        float volt2 = (float)pot2 * 3.3 / 4095;

        printf("Voltaje 1: %.2f V\n", volt1);
        printf("Voltaje 2: %.2f V\n", volt2);
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}
