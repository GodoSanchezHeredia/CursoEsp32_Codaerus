#include <stdio.h>
#include <stdint.h>
//Punteros
//estructuras
//enumeaciones
//punteros a funciones y estructuras
//creacion de librerias


struct volquete
{
    char *ID ;
    float TemperaturaMotor;
    float PresionSuspension;
    float Velocidad;
    float Tonalaje;
    int16_t RPM;

};

struct pala
{
    char *ID ;
    float InclinometroBucket;
    float InclinotroCabina;
    float Energia;
    int8_t TiempoCarguio;

};


struct drill
{
    char *ID ;
    float Energia;
    float Temperatura;
    uint16_t Profundidad;
};

typedef struct
{
    char *ID ;
    float Energia;
    float Temperatura;
    uint16_t Palada;
    struct main
    {
        /* data */
    };
    
}Scoop;


Scoop ScoopBrocal;
Scoop Yunpag;



void app_main(void)
{
  struct volquete CV113;
  struct volquete CV114;
  struct volquete CV115;
  struct volquete CV116;

   CV113.ID = "CV113";
   CV113.TemperaturaMotor = 120;
   CV113.PresionSuspension = 105;
   CV113.Velocidad = 50;
   CV113.Tonalaje = 400;
   CV113.RPM = 400; 


    struct drill CD1;
    struct drill CD2;

    CD1.ID = "CD1";
    CD1.Energia = 100;
    CD1.Temperatura = 100;
    CD1.Profundidad = 100;

    struct pala CP1;
    struct pala CP2;

    CP1.ID = "CP1";
    CP1.InclinometroBucket = 100;
    CP1.InclinotroCabina = 100;
    CP1.Energia = 100;
    CP1.TiempoCarguio = 100;


    
    printf("ID CV113 = %s\n", CV113.ID);
    printf("Temperatura CV113 = %f\n", CV113.TemperaturaMotor); 
    printf("RPM CV113 = %d\n", CV113.RPM);

    printf("ID CD1 = %s\n", CD1.ID);
    printf("Energia CD1 = %f\n", CD1.Energia);
    printf("Profundidad CD1 = %d\n", CD1.Profundidad);
    
    printf("ID CP1 = %s\n", CP1.ID);
    printf("Energia CP1 = %f\n", CP1.Energia);  

}
