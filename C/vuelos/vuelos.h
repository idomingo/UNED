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
* la informaci�n relativa a cada vuelo.
**************************************/

#pragma once
#include "calendario.h"


/*========================================================================================*/
/*=================================== DEFINICI�N DE TIPOS ================================*/
/*========================================================================================*/

/*========================================================================================
    Vector tipo cadena de caracteres para delimitar el C�digo del vuelo.
  ========================================================================================*/
const int longitud_codigo_vuelo=7;
typedef char TipoCodigo[longitud_codigo_vuelo+1];


/*========================================================================================*/
/*=========================================== TAD ========================================*/
/*========================================================================================*/

/*========================================================================================
    TAD TipoVuelo. Tipo abastracto de datos donde se almacena toda la informaci�n relativa
a cada vuelo: fecha, plazas, precio, c�digo, adem�s de procedimientos y operaciones.
  ========================================================================================*/

typedef struct TipoVuelo {
  TipoCalendario fecha;                  /*TipoCalendario para guardar la fecha del vuelo.*/
  TipoCodigo codigo;                           						             /*C�digo del vuelo.*/
  int precio;                  										                 /*Precio (actualizado).*/
  int plazas_inicial;													                         /*Plazas iniciales.*/
  int plazas; 											                   /*Plazas disponibles (actualizado).*/
  int punteroBusqueda;   /*Variable para identificar los vuelos que pasan ciertos filtros.*/

  void AceptarNuevoVuelo();                          /*Registra un nuevo vuelo en memoria.*/
  void ActualizarPlazas();     				        /*Actualiza el n�mero de plazas disponibles.*/
  void CalcularPrecio();       /*Actualiza el precio en funci�n de las plazas disponibles.*/

  bool VueloCompleto();                             /*Comprueba si el vuelo est� completo.*/
  bool ValidarCodigo();		   /*Comprueba que el c�digo del vuelo introducido sea correcto.*/

  private:
  int p_plazas_inicial, p_precio, p_plazas, p_precio_inicial;
  TipoCodigo p_codigo;
};



