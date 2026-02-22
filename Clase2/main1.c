#include <stdio.h>
#include <stdint.h>
//Punteros
//estructuras
//enumeaciones
//punteros a funciones y estructuras
//creacion de librerias

unsigned char x = 58;
char y = -1;
short int z = 4660;

//printf("address of x = %p\n", &x);   he apuntado a la direccion de x
void app_main(void)
{
    ///////////////////////////////////////////////////////////////////////////////////
    //  Ejemplo 1
    ///////////////////////////////////////////////////////////////////////////////////

    printf("x = %d\n", x);
    printf("address of x = %p\n", &x);


    ///////////////////////////////////////////////////////////////////////////////////
    //  Ejemplo 2
    ///////////////////////////////////////////////////////////////////////////////////

    uint8_t  dato  = 200;
    uint8_t *ptr = &dato;


    printf("Valor = %u\n", dato);
    printf("Direccion de dato = %p\n", &dato);
    printf("Contenido apuntado = %u\n", *ptr);


    ///////////////////////////////////////////////////////////////////////////////////
    //  Ejemplo 3
    ///////////////////////////////////////////////////////////////////////////////////

    // ARRAY DE CARACTERES
    // char arreglo[4] = {'a', 'b', 'c', 'd'};
    //  abcd 
    // char *msj = "ESP32";
    // esp32\0
    char *msj = "ESP32";

    char send[6] = "ESP32";//CADENAS DE CARACTERES modificar sin problemas
    char *send2 = "ESP32";//string no se recomienda modificar

    //0x3fc98450 -> E
    //0x3fc98451 -> S
    //0x3fc98452 -> P
    //0x3fc98453 -> 3
    //0x3fc98454 -> 2
    //0x3fc98455 -> \0
    printf("Primer caracter = %c\n", *msj);
    printf("Segundo caracter = %c\n", *(msj+1));

    printf("String completo = %s\n", msj);

}
