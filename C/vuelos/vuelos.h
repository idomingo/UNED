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
* Cabecera 'Vuelos.h'. Incluye el TAD
* 'TipoVuelo' donde se almacena toda
* la información relativa a cada vuelo.
**************************************/

#pragma once
#include "calendario.h"


/*========================================================================================*/
/*=================================== DEFINICIÓN DE TIPOS ================================*/
/*========================================================================================*/

/*========================================================================================
    Vector tipo cadena de caracteres para delimitar el Código del vuelo.
  ========================================================================================*/
const int longitud_codigo_vuelo=7;
typedef char TipoCodigo[longitud_codigo_vuelo+1];


/*========================================================================================*/
/*=========================================== TAD ========================================*/
/*========================================================================================*/

/*========================================================================================
    TAD TipoVuelo. Tipo abastracto de datos donde se almacena toda la información relativa
a cada vuelo: fecha, plazas, precio, código, además de procedimientos y operaciones.
  ========================================================================================*/

typedef struct TipoVuelo {
  TipoCalendario fecha;                  /*TipoCalendario para guardar la fecha del vuelo.*/
  TipoCodigo codigo;                           						             /*Código del vuelo.*/
  int precio;                  										                 /*Precio (actualizado).*/
  int plazas_inicial;													                         /*Plazas iniciales.*/
  int plazas; 											                   /*Plazas disponibles (actualizado).*/
  int punteroBusqueda;   /*Variable para identificar los vuelos que pasan ciertos filtros.*/

  void AceptarNuevoVuelo();                          /*Registra un nuevo vuelo en memoria.*/
  void ActualizarPlazas();     				        /*Actualiza el número de plazas disponibles.*/
  void CalcularPrecio();       /*Actualiza el precio en función de las plazas disponibles.*/

  bool VueloCompleto();                             /*Comprueba si el vuelo está completo.*/
  bool ValidarCodigo();		   /*Comprueba que el código del vuelo introducido sea correcto.*/

  private:
  int p_plazas_inicial, p_precio, p_plazas, p_precio_inicial;
  TipoCodigo p_codigo;
};



