/******************************************
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
* Módulo 'Vuelos.cpp'. Define las funciones
* y procedimientos declarados en la
* cabecera 'vuelos.h'.
*******************************************/

#include <stdio.h>
#include <string.h>

#include "vuelos.h"

/*========================================================================================*/
/*=============================== DEFINICIÓN DE SUB-PROGRAMAS ============================*/
/*========================================================================================*/

/*========================================================================================
    Procedimiento: Actualiza el precio de un vuelo tras comprar un billete.
  ========================================================================================*/
void TipoVuelo::CalcularPrecio() {

  if (p_plazas>=p_plazas_inicial*50/100) {
    p_precio=p_precio_inicial;
  } else if (p_plazas>=p_plazas_inicial*20/100) {
    p_precio=p_precio_inicial*2;
  } else if (p_plazas>=p_plazas_inicial*5/100) {
    p_precio=p_precio_inicial*3;
  } else if (p_plazas<p_plazas_inicial*5/100) {
    p_precio=p_precio_inicial*5;
  }
  precio = p_precio;
}

/*========================================================================================
    Procedimiento: Actualiza el número de plazas disponibles tras comprar un billete.
  ========================================================================================*/
void TipoVuelo::ActualizarPlazas() {
  plazas--;
  p_plazas = plazas;
}

/*========================================================================================
    Tipo Bool. Comprueba si el vuelo está completo.
  ========================================================================================*/
bool TipoVuelo::VueloCompleto() {
  if (plazas>0) {
    return false;
  } else {
    return true;
  }
}

/*========================================================================================
    Tipo Bool. Comprueba si la longitud del código del vuelo introducida es correcta.
  ========================================================================================*/
bool TipoVuelo::ValidarCodigo() {
  if (strlen(codigo)>7) {
    return false;
  } else {
    return true;
  }
}

/*========================================================================================
    Procedimiento: Incorpora un nuevo vuelo al TAD tras pasar las validaciones.
  ========================================================================================*/
void TipoVuelo::AceptarNuevoVuelo () {
    p_plazas_inicial=plazas_inicial;
    p_plazas=plazas_inicial;
    plazas=plazas_inicial;
    p_precio_inicial=precio;
    p_precio=precio;
    strcpy(p_codigo,codigo);
}



