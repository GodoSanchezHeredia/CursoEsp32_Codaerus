#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_wifi.h>
#include <nvs_flash.h> // manejar la memoria no volatil 
#include <esp_system.h> // propiedades generales del esp32
#include "esp_log.h"


//definiri los acceesos

#define WIFI_SSID "MOVISTAR-WIFI6-B668"
#define WIFI_PASS "Pe4JFU3RXRPYU43PRg3U"
//#define WIFI_SSID "iPhone"
//#define WIFI_PASS "godo1234"

static const char *TAG = "wifi DHCP";


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






void app_main(void)
{

    esp_err_t ret = nvs_flash_init();
   
    if (ret != ESP_OK)
    {
        /* code */
        return ;
    }

    wifi_init_sta();
    

}