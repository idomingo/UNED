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
* Cabecera 'Procedimientos.h'. Declara
* los procedimientos principales y los
* vectores donde se almacenarán los
* vuelos.
**************************************/

#pragma once
#include "vuelos.h"


/*========================================================================================*/
/*============================= DEFINICIÓN DE VARIABLES GLOBALES =========================*/
/*========================================================================================*/

/*========================================================================================
    Variable global 'numeroVuelos'.
  Funciona como un contador que se va incrementando cada vez que se registra un nuevo vuelo
  en el sistema. En 'procedimientos.cpp' se inicializa con valor = 0.
  ========================================================================================*/
extern int numeroVuelos;

/*========================================================================================
    Capacidad de almacenamiento del programa: 24 meses, con 50 vuelos por mes.
  ========================================================================================*/
const int MAX_VUELOS_MES=50;
const int MAX_MESES=24;
const int capacidad = MAX_VUELOS_MES * MAX_MESES;

/*========================================================================================
    Vector del TAD TipoVuelo 'ListaVuelos' donde se almacenan todos los vuelos.
  El vector se inicializa en 'procedimientos.cpp'.
 =========================================================================================*/
typedef TipoVuelo VectorGlobal[capacidad];


/*========================================================================================
    Vector auxiliar del TAD TipoVuelo donde se almacenan los vuelos que pasan los filtros
  de las búsquedas. Las búsquedas se reducen a mes/año o dia/mes/año, por lo que el tamaño
  máximo que puede almacenar en un determinado momento es de 'MAX_VUELOS_MES', en este
  caso = 50. Este vector es creado y destruido en cada procedimiento cuando se necesita.
  ========================================================================================*/
typedef TipoVuelo VectorLocal[MAX_VUELOS_MES];


/*========================================================================================*/
/*============================== DECLARACIÓN DE SUB-PROGRAMAS ============================*/
/*========================================================================================*/


bool HayVuelo(int dia,VectorLocal ListaAux,int lista);   /*Indica si hay vuelo cierto día.*/
bool ValidarHueco(TipoVuelo aux);  /*Comprueba si hay hueco para almacenar un nuevo vuelo.*/
bool CompararFechaPosterior(TipoVuelo uno, TipoVuelo dos);            /*Compara dos fechas*/
bool CompararCodigo(int dia, int mes, int anno, char codigo[]); /*Evita vuelos duplicados.*/

void OrdenarFechas ();                                      /*Ordena por fechas un vector.*/
void AltaNuevoVuelo();                            /*Registra un nuevo vuelo en la memoria.*/
void OfertasDelMes ();                           /*Lista los 5 vuelos más baratos del mes.*/
void ComprarPlazas();                            /*Taquilla para comprar pasajes de avión.*/
void VuelosDelMes ();                       /*Imprime el calendario de los vuelos del mes.*/



