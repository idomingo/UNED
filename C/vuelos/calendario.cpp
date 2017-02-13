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
* M�dulo 'Calendario.cpp'. Define las
* funciones declaradas en el TAD
* 'TipoCalendario'.
**************************************/

#include <stdio.h>
#include "calendario.h"


/*=========================================================================================*/
/*=============================== DEFINICI�N DE SUB-PROGRAMAS =============================*/
/*=========================================================================================*/


/*=========================================================================================
    Tipo Bool. Comprueba si el a�o almacenado en el TAD es bisiesto.
  ========================================================================================*/
bool TipoCalendario::esBisiesto() {
    if (anno%4==0&&!(anno%100==0&&anno%400!=0)) {
    return true;
  } else {
    return false;
  }
}

/*=========================================================================================
    Tipo Bool. Comprueba si la combinaci�n mes/a�o introducida por el usuario es correcta.
  ========================================================================================*/
bool TipoCalendario::ValidarMes() {
  if (anno<limite_inferior_anno||anno>limite_superior_anno||mes<=0||mes>12) {
    return false;
  } else {
    return true;
  }

}

/*=========================================================================================
    Tipo Bool. Comprueba si la combinaci�n d�a/mes/a�o es correcta.
  ========================================================================================*/
bool TipoCalendario::ValidarDiaMes() {

  int dia_meses = dias_meses[mes];

  if (!ValidarMes()) {
    return false;
  }
  if (mes==2&&esBisiesto()) {
    dia_meses=29;
  }
  if (dia<=0||dia>dia_meses) {
    return false;
  } else {
    return true;
  }
}

/*=========================================================================================
    Tipo Bool. Comprueba si la combinaci�n d�a/mes/a�o/hora/minuto es correcta.
  ========================================================================================*/
bool TipoCalendario::ValidarDiaMesHora () {

  if (!ValidarDiaMes()) {
    return false;
  }
  if (hora<0||hora>23||minuto<0||minuto>59) {
    return false;
  } else {
    return true;
  }
}



/*=========================================================================================
    Funci�n basada en el algoritmo de Zeller para calcular el primer d�a de cada mes.
  Esta funci�n tiene en cuenta los a�os bisiestos.
  ========================================================================================*/
TipoDia TipoCalendario::DiaSemana(int mes, int anno) {
  int dia, i, j, k;
  i = (14-mes)/12;
  j = anno-i;
  k = mes+(12*i)-2;
  dia = (1+j+(j/4)-(j/100)+(j/400)+(31*k)/12)%7;
  if (dia == 0) {
    dia = 7;
  }
  return TipoDia(dia);
}
