#include <stdio.h>
#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Library.h"

//puntero a una variable apunta a la direccion de memoria de esa variable
//puntero a una funcion apunta a la direccion de memoria de esa funcion
//puntero a una estructura apunta a la direccion de memoria de esa estructura*

int *ptr;//puntero a una variable
void (*func)(void);//puntero a una funcion
int (*operacion)(int, int);//puntero a una funcion

void func1(void)  {
    printf("LED ON\n");
}

void func2(void)  {
    printf("LED OFF\n");
}


void ejecutar(void (*func)(void)) {
    func();
}

int suma(int a, int b) {
    return a + b;
}


struct LedDriver
{
    void (*init)(void);
    void (*on)(void);
    void (*off)(void);  
};

void led_init(void) {
    printf("LED INIT\n");
}

void led_on(void) {
    printf("LED ON\n");
}

void led_off(void) {
    printf("LED OFF\n");
}


struct LedDriver led  = {
    .init = led_init,
    .on = led_on,
    .off = led_off
};


struct sensor
{
    uint8_t id;
    float temperatura;
    float presion;
};

struct sensor sensor1= {1, 400, 432};
struct sensor *ptr1 = &sensor1;

void app_main(void)
{

    ejecutar(func2);
    ejecutar(func1);
    operacion = suma;
    int resultado = operacion(10, 20);
    printf("Resultado = %d\n", resultado);


    led.init();
    led.on();
    led.off();

    ptr1->id = 1;
    ptr1->temperatura = 400;
    ptr1->presion = 432;
    printf("ID = %d\n", ptr1->id);
    printf("Temperatura = %f\n", ptr1->temperatura);    
    printf("Presion = %f\n", ptr1->presion);

    sendSMS();
    sendEmail();
    sendCall();

}
