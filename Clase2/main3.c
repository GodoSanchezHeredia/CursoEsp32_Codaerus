#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
//Punteros
//estructuras
//enumeaciones
//punteros a funciones y estructuras
//creacion de librerias


enum EstadosSistema
{
    INICIAL=9,
    CONFIGURADO,
    RUNNING,
    ERROR
};

enum EstadosSistema state = INICIAL;

void app_main(void)
{

for (;;)
{
    switch (state)
    {
    case  INICIAL:
        printf("Estado inicial\n");
        state = CONFIGURADO;
        break;
    case  CONFIGURADO:

        printf("Estado configurado\n");
        state = RUNNING;
        break;
    case  RUNNING:
        printf("Estado ejecutando\n");
        state = ERROR;
        break;  
    case  ERROR:
        /* code */
        printf("Estado error\n");
        break;  

    default:
        break;
    }
vTaskDelay(1000 / portTICK_PERIOD_MS);
}


}
