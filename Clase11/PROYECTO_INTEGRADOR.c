#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_wifi.h>
#include <nvs_flash.h> // manejar la memoria no volatil 
#include <esp_system.h> // propiedades generales del esp32
#include <driver/adc.h>
#include <driver/ledc.h>
#include "esp_log.h"
#include "mqtt_client.h"

//definiri los acceesos

//consiste en usar lo que hemos aprendio
// adc
// pwm
// serial
// mqtt
 
#define WIFI_SSID "MOVISTAR-WIFI6-B668"
#define WIFI_PASS "Pe4JFU3RXRPYU43PRg3U"
//#define WIFI_SSID "iPhone"
//#define WIFI_PASS "godo1234"

static const char *TAG = "wifi DHCP";
static const char *TAG1 = "MQTT";

esp_mqtt_client_handle_t client;
/*
 cmd como administrador y ejecutar:
netsh advfirewall firewall add rule name="MQTT" dir=in action=allow protocol=TCP localport=1883
*/

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        ESP_LOGI(TAG,"Conectando a la red wifi\n");
        esp_wifi_connect();

    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
      
        ESP_LOGI(TAG,"Reconectando a la red wifi\n");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "IP:" IPSTR, IP2STR(&event->ip_info.ip));
        ESP_LOGI(TAG, "MASK:" IPSTR, IP2STR(&event->ip_info.netmask));
        ESP_LOGI(TAG, "GATEWAY:" IPSTR, IP2STR(&event->ip_info.gw));

    }
}

void wifi_init_sta(void)
{
    //1. inicializar la pila de red esp32
    esp_netif_init();
    //2. inicializar el bucle de  eventos
    esp_event_loop_create_default();
    //3. inicializamos como  station
    esp_netif_create_default_wifi_sta();
    //4. configuracion inciialies del wifi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    //5. inicializamos el driver wifi
    esp_wifi_init(&cfg);
    //6. indicar los parametros de la conexion

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    //7. configuramos el modo wifi de la esp32
    esp_wifi_set_mode(WIFI_MODE_STA);
    //8. asociamos la configuracion  a la esp32
    esp_wifi_set_config(WIFI_IF_STA,&wifi_config);

    //9.inicializar el modulo wifi
    esp_wifi_start();   
    
    //10. realizamos la conexion
    esp_wifi_connect();
}

void mqtt_publish_task(void)
{       
    esp_mqtt_client_start(client);
    while(1){
        int pot1 = adc1_get_raw(ADC1_CHANNEL_6);
        int pot2 = adc1_get_raw(ADC1_CHANNEL_4);
   
        char msg[20];   
        sprintf(msg,"%d,%d\n",pot1,pot2);
        esp_mqtt_client_publish(client,"data",msg,0,0,1);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
    
}

esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event){

  return ESP_OK;
}

void mqtt_event_handler(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data){
    ESP_LOGI(TAG1,"MQTT Event handler");
    esp_mqtt_event_handle_t event = event_data;

   // mqtt_event_handler_cb(event);
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        /* code */
        ESP_LOGI(TAG1,"MQTT Connected");
        esp_mqtt_client_subscribe(client,"canaly",0);
        break;
    case MQTT_EVENT_DATA:
     
        ESP_LOGI(TAG1,"RECIBI %.*s",event->data_len,event->data);
        char data[10];
        
        int duty = atoi(event->data);
        ESP_LOGI(TAG1,"Duty %d",duty);
        if (duty >0 && duty<=256)
        {
            /* code */
            ledc_set_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0,duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);

        }
        

    default:
        break;
    }


}

void mqtt_app_start(void)
{
    ESP_LOGI(TAG1,"Inicializando MQTT");
    esp_mqtt_client_config_t mqtt_cfg = { 
            .broker.address.uri = "mqtt://192.168.1.87", 
            .broker.address.port = 1883,
        };
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client,MQTT_EVENT_ANY,mqtt_event_handler,NULL);
    xTaskCreate(mqtt_publish_task, "mqqt_task", 1024 * 4, (void*)client, 5, NULL);
}

void adc_init(void){
    adc1_config_width(ADC_WIDTH_BIT_12); //CONFIGURAMOS A 12 BITS
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12); //CONFIGURAMOS EL CANAL 6 CON ATTENUACION 11 DB
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_12); //CONFIGURAMOS EL CANAL 4 CON ATTENUACION 11 DB
}

void pwm_init(void){
  ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 100,
        .duty_resolution = LEDC_TIMER_8_BIT
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

}

void app_main(void)
{

    esp_err_t ret = nvs_flash_init();
   
    if (ret != ESP_OK)
    {
        /* code */
        return ;
    }

    wifi_init_sta();
    mqtt_app_start();
    adc_init();
    pwm_init();

}