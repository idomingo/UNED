/*************************************
* NOMBRE: #Iker#
* PRIMER APELLIDO: #Domingo#
* SEGUNDO APELLIDO: #Perez#
* DNI: #71126454N#
* EMAIL: #ikerdomingoperez@gmail.com#
*
* * * * * * * * PRACTICA 4 * * * * * *
*
* * * * * * PROGRAMA: VUELOS * * * * *
*
* Gestión de los vuelos de un aeropuerto
*
* Opciones disponibles:
* - Registrar el alta de un nuevo vuelo
* - Buscar los vuelos más baratos del mes
* - Comprar pasajes de avión
* - Calendario mensual de vuelos
*
* Este es el módulo 'Principal'.
* Incluye el menú de opciones
*
**************************************/

#include <stdio.h>
#include <conio.h>   /*getch()*/
#include <ctype.h>   /*tolower()*/
#include <string.h>  /*strcpy(),strlen(),strcmp(),%s*/
#include <stdlib.h>  /*system("pause"),system("cls")*/

#include "procedimientos.h"




/*========================================================================================*/
/*========================================== MENU ========================================*/
/*========================================================================================*/

void Separador() {      /*Dibuja una línea de asteriscos en diferentes partes del programa*/
  for (int i=0;i<=63;i++) {
    printf("*");
  }
  printf("\n");
}

void Menu() {      /*Estructura del menú. Muestra el porcentaje de ocupación de la memoria*/
  Separador();
  printf("*   Saludos, operador                            ____________  *\n");
  printf("*                        .        --)-----------|____________| *\n");
  printf("*              .                                ,'       ,'    *\n");
  printf("*         .       -)------========            ,'  ____ ,'      *\n");
  printf("*                          `.    `.         ,'  ,'__ ,'    .   *\n");
  printf("*  .                         `.    `.     ,'       ,'   .      *\n");
  printf("*                       .      `.    `._,'_______,'__          *\n");
  printf("*             .                  [._ _| ^--      || |          *\n");
  printf("*                        ____,...-----|__________ll_|\\   .     *\n");
  printf("*       ,.,..-------'''''     '----'                 ||        *\n");
  printf("*   .-''  |=========================== ______________ |        *\n");
  printf("*    '-...l_______________________    |  |'      || |_]    .   *\n");
  printf("*                                 [`-.|__________ll_|          *\n");
  printf("*               .               ,'    ,' `.        `.   .      *\n");
  printf("*   .                         ,'    ,'     `.    ____`.        *\n");
  printf("*                 -)---------========     .  `.  `.____`.    . *\n");
  printf("*       .                                      `.        `.    *\n");
  printf("*                        .              .        `.________`.  *\n");
  printf("*  .             .               --)-------------|___________| *\n");
  printf("*                                                              *\n");
  printf("*  .   Le doy la bienvenida al nuevo sistema inteligente   .   *\n");
  printf("*        para la gesti%cn de su propia base rebelde.            *\n",162);
  printf("*   .                    .                                     *\n");
  printf("*                                                     .        *\n");
  printf("* Vuelos Registrados: %4d            .                        *\n",numeroVuelos);
  printf("*                                    Memoria Disponible: %3d%c  *\n",
          (capacidad-numeroVuelos)*100/capacidad,37);
  printf("*                                                              *\n");
  printf("* Por favor, seleccione una de las siguientes opciones:        *\n");
  printf("*                                                              *\n");
  printf("*    Alta Nuevo Vuelo                           (Pulsar A)     *\n");
  printf("*    Ofertas del Mes                            (Pulsar O)     *\n");
  printf("*    Comprar Plazas                             (Pulsar C)     *\n");
  printf("*    Vuelos del Mes                             (Pulsar V)     *\n");
  printf("*    Salir                                      (Pulsar S)     *\n");
  printf("*                                                              *\n");
  Separador();
}

void AvancePantalla(char texto[]) {    /*Sistema utilizado para pasar a una nueva pantalla*/
  system("cls");
  printf("\n%48s\n\n", texto);
  Separador();
}

/*========================================================================================*/
/*=================================== PROGRAMA PRINCIPAL =================================*/
/*========================================================================================*/

int main() {
  bool salir;                                        /*Tipo bool para terminar el programa*/
  bool error;                                           /*Tipo bool para el bucle del menú*/
  char tecla;
  salir=false;
  while (!salir) {         /*Muestra el menú de opciones mientras no se seleccione 'Salir'*/
    Menu();
    do {
      error=false;
      tecla=tolower(char(getch()));                /*Captura la tecla pulsada directamente*/

      switch (tecla) {
        case 'a':
        AvancePantalla("          ALTA NUEVO VUELO");
        AltaNuevoVuelo();
        break;
        case 'o':
        AvancePantalla("       BUSCADOR DE OFERTAS");
        OfertasDelMes();
        break;
        case 'c':
        AvancePantalla("                  TAQUILLA");
        ComprarPlazas();
        break;
        case 'v':
        AvancePantalla("  AGENDA MENSUAL DE VUELOS");
        VuelosDelMes();
        break;
        case 's':
        printf("\n                                  QUE LA FUERZA TE ACOMPA%cE\n",165);
        Separador();
        salir=true;
        break;
        default:
        error=true;
      }
    } while (error);
  }
  system("pause");
}
