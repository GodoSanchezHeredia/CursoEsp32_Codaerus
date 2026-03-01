//revision 
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"


uint16_t pot1=0;
uint16_t pot2=0;
void app_main(void)
{
    adc_oneshot_unit_handle_t adc;

    adc_oneshot_unit_init_cfg_t init = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init, &adc);

    adc_oneshot_chan_cfg_t config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12
    };

    adc_oneshot_config_channel(adc, ADC_CHANNEL_6, &config);
    adc_oneshot_config_channel(adc, ADC_CHANNEL_7, &config);
    while(1)
    {
       
        adc_oneshot_read(adc,ADC_CHANNEL_6,&pot1);
        adc_oneshot_read(adc,ADC_CHANNEL_7,&pot2);

        printf("ADC1: %u ADC2: %u\n",pot1,pot2);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }

}
