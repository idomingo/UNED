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
* Cabecera 'Calendario.h'. Incluye el
* TAD 'TipoCalendario' para trabajar
* con las fechas. Tambi�n se definen
* algunas constantes globales.
**************************************/

#pragma once

/*========================================================================================*/
/*============================ DEFINICI�N DE CONSTANTES GLOBALES =========================*/
/*========================================================================================*/

/*=========================================================================================
    Constantes para establecer los limites de operaci�n de las fechas del programa.
  Teniendo en cuenta que en el enunciado de la pr�ctica no se especifica ning�n rango de
  fechas, tan s�lo que debe abarcar 24 meses, he puesto como l�mites 2016 (Enero) y 2017
  (Diciembre).
    Una alternativa ser�a dejar que el programa calculase el margen de operaci�n al arrancar
  pidiendo al usuario el mes_actual y el anno_actual:
  limite_inferior_anno = anno_actual;
  limite_inferior_mes = mes_actual;
  if (mes_actual==1) {
    limite_superior_anno = limite_inferior_anno + 1;
    limite_superior_mes = 12;
  } else {
    limite_superior_anno = limite_inferior_anno + 2;
    limite_superior_mes = limite_inferior_mes - 1;
  }
    Por �ltimo, en el m�dulo 'Calendario.cpp' en el procedimiento 'ValidarMes' se sustituye
  el if en el que compara a�o y mes por el siguiente:
  if (anno==limite_inferior_anno&&mes<limite_inferior_mes ||
      anno==limite_superior_anno&&mes>limite_superior_mes ||
      anno<limite_inferior_anno||anno>limite_superior_anno
      mes<=0 || mes >=0)
  ========================================================================================*/
const int limite_inferior_anno=2016;
const int limite_superior_anno=2017;

/*=========================================================================================
  Constante para delimitar los vectores que almacenan el nombre y el n�mero de d�as del mes.
  ========================================================================================*/
const int numero_meses = 13;
const int longitud_nombre_mes = 11;

/*========================================================================================*/
/*=================================== DEFINICI�N DE TIPOS ================================*/
/*========================================================================================*/

/*=========================================================================================
  Vectores para almacenar el nombre de los meses, completos y abreviados.
  ========================================================================================*/

typedef char TipoNombreMes[longitud_nombre_mes];
typedef TipoNombreMes listaMeses[numero_meses];

const listaMeses listaM = {"***","Enero","Febrero","Marzo","Abril",
                                 "Mayo","Junio","Julio","Agosto","Septiembre",
                                 "Octubre","Noviembre","Diciembre"};

const listaMeses listaMcorta = {"***","ENE","FEB","MAR","ABR","MAY","JUN",
                                      "JUL","AGO","SEP","OCT","NOV","DIC"};

/*=========================================================================================
  Vector para almacenar el n�mero de d�as que tiene un mes.
  ========================================================================================*/
typedef int TipoDiaMes[numero_meses];
const TipoDiaMes dias_meses = {0,31,28,31,30,31,30,31,31,30,31,30,31};

/*=========================================================================================
  Variable tipo enumerado para los d�as de la semana.
  ========================================================================================*/
typedef enum TipoDia {Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo};

/*========================================================================================*/
/*========================================== TAD =========================================*/
/*========================================================================================*/

/*=========================================================================================
    TAD TipoCalendario. Almacena fechas y realiza operaciones entre fechas.
  Cada vuelo tiene su propio TAD TipoCalendario 'fecha' con la informaci�n correspondiente.
  ========================================================================================*/

typedef struct TipoCalendario {
  int dia, mes, anno, hora, minuto;     				       /*Variables para almacenar la fecha*/
  bool ValidarMes();       			       /*Comprueba que la combinaci�n mes-a�o sea correcta*/
  bool ValidarDiaMes();            /*Comprueba que la combinaci�n dia-mes-a�o sea correcta*/
  bool ValidarDiaMesHora();              /*Comprueba que la fecha introducida sea correcta*/
  bool esBisiesto();                             /*Comprueba si un a�o es o no es bisiesto*/
  TipoDia DiaSemana(int mes, int anno);                   /*Calcula el primer d�a del mes.*/
};
