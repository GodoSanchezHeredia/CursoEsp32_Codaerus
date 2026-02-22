

volatile int g_in1 = 0;
volatile int g_in2 = 0;

void TaskInputs(void *p){

  gpio_config_t io_input = {
    .pin_bit_mask = ((1ULL<<GPIO_NUM_2) |(1ULL<<GPIO_NUM_17)) ,
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .intr_type =GPIO_INTR_DISABLE
  };

  ESP_ERROR_CHECK(gpio_config(&io_input));

  while(1){
    g_in1= gpio_get_level(GPIO_NUM_2);
    g_in2= gpio_get_level(GPIO_NUM_17);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

}
void TaskOutputs(void *p){

  //SALIDAS
  gpio_config_t io_output = {
    .pin_bit_mask = ((1ULL<<GPIO_NUM_18) |(1ULL<<GPIO_NUM_4)) ,
    .mode=GPIO_MODE_OUTPUT
  };

  ESP_ERROR_CHECK(gpio_config(&io_output));


  while(1){
      if(!g_in1){
        printf("Boton1 Pulsado!\n");
        gpio_set_level(GPIO_NUM_4,1);
      }else{
        gpio_set_level(GPIO_NUM_4,0);
      }

      if(!g_in2){
        printf("Boton2 Pulsado!\n");
        gpio_set_level(GPIO_NUM_18,1);
      }else{
        gpio_set_level(GPIO_NUM_18,0);
      }
      vTaskDelay(10/ portTICK_PERIOD_MS);

  }
}

// /xTaskCreate(
//                             TaskFunction_t pvTaskCode,
//                             const char * const pcName,     /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
//                             const uint32_t usStackDepth,
//                             void * const pvParameters,
//                             UBaseType_t uxPriority,
//                             TaskHandle_t * const pxCreatedTask)

void app_main() {


  xTaskCreate(&TaskInputs,"TkInput",2048,NULL,1,NULL);
  xTaskCreate(&TaskOutputs,"TkOutput",2048,NULL,1,NULL);
  
}
