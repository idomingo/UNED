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
* Módulo 'Procedimientos.cpp'. Define
* los procedimientos del menú principal
* y otros auxiliares.
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "procedimientos.h"


/*=========================================================================================*/
/*=========================== INICIALIZACIÓN DE VARIABLES GLOBALES ========================*/
/*=========================================================================================*/

int numeroVuelos = 0;
VectorGlobal ListaVuelos;

/*=========================================================================================*/
/*=============================== DEFINICIÓN DE SUB-PROGRAMAS =============================*/
/*=========================================================================================*/


/*=========================================================================================
    Bool 'HayVuelo'
  Devuelve 'True' si hay algún vuelo que coincida en día con los almacenados en el vector
  auxiliar ListaAux, que previamente se ha rellenado con los vuelos que coinciden en Mes y
  Año con los datos introducidos por el usuario. La variable 'lista' hace referencia al
  índice del VectorLocal 'ListaAux'.
  =========================================================================================*/
bool HayVuelo(int dia, VectorLocal ListaAux, int lista) {
	for (int i=1;i<=lista-1;i++) {
		if (ListaAux[i].fecha.dia==dia) {
			return true;
		}
	}
	return false;
}

/*=========================================================================================
    Bool 'CompararCodigo'
  Cuando se va a registrar un nuevo vuelo comprueba si existe algún otro vuelo con el mismo
  código, día, mes y año previamente registrado en el sistema. Esto significa que ese vuelo
  ya está registrado. Pueden existir vuelos con el mismo código en diferentes días, pero
  suponemos que no en el mismo día.
  =========================================================================================*/
bool CompararCodigo(int dia, int mes, int anno, char codigo[]) {
  for (int i=0;i<=numeroVuelos-1;i++) {
    if (!strcmp(codigo,ListaVuelos[i].codigo) && ListaVuelos[i].fecha.dia==dia &&
        ListaVuelos[i].fecha.mes==mes && ListaVuelos[i].fecha.anno==anno) {
      return false;
    }
  }
  return true;
}

/*=========================================================================================
    Bool 'ValidarHueco'.
  Comprueba entre los vuelos almacenados en el TAD aquellos que coinciden en mes y en año.
  Si el número de coincidencias está por debajo del límite establecido permite almacenar un
  nuevo vuelo en la memoria.
  =========================================================================================*/
bool ValidarHueco(TipoVuelo aux) {
  int contador=0;
  for (int i=0;i<=numeroVuelos;i++) {
    if (ListaVuelos[i].fecha.anno==aux.fecha.anno && ListaVuelos[i].fecha.mes==aux.fecha.mes) {
      contador++;                        /*Por cada coincidencia se incrementa el contador.*/
    }
  }
  if (contador>=MAX_VUELOS_MES) {        /*Tras el bucle compara el contador con el límite.*/
        return false;
  } else {
    return true;
  }
}

/*=========================================================================================
    Bool 'CompararFechaPosterior'.
  Compara dos fechas. Cierto si la primera fecha es anterior a la segunda. Sólo es necesario
  comparar Día/hora/minuto ya que los propios procedimientos ya han filtrado previamente
  vuelos que coincidan en mes/año y día/mes/año.
  =========================================================================================*/
bool CompararFechaPosterior(TipoVuelo uno, TipoVuelo dos) {
  if (uno.fecha.dia != dos.fecha.dia) {
    return (uno.fecha.dia > dos.fecha.dia);
  } else if (uno.fecha.hora != dos.fecha.hora) {
    return (uno.fecha.hora > dos.fecha.hora);
  } else { return (uno.fecha.minuto > dos.fecha.minuto);
  }
}

/*=========================================================================================
    Procedimiento 'OrdenarFechas'.
  Ordena por fecha el VectorGlobal 'ListaVuelos'. Para ello utiliza el método de la burbuja
  tras comparar dos fechas con el bool 'CompararFechaPosterior'.
  =========================================================================================*/
void OrdenarFechas () {
	TipoVuelo aux;
	for (int i=0;i<numeroVuelos-1;i++) {
		for (int j=i+1;j<=numeroVuelos-1;j++) {
			if (CompararFechaPosterior(ListaVuelos[i],ListaVuelos[j])) {
				aux = ListaVuelos[j];
				ListaVuelos[j]=ListaVuelos[i];
				ListaVuelos[i]=aux;
			}
		}
	}
}


/*=========================================================================================
    Procedimiento principal 'AltaNuevoVuelo' para iniciar el alta de un nuevo vuelo.
	1.- Pide los datos.
	2.- Verifica los datos.
	3.- Introduce el vuelo en memoria si se pasan las validaciones.
	=========================================================================================*/
void AltaNuevoVuelo() {

  TipoVuelo nuevoVuelo;           /*Variable TipoVuelo para almacenar los datos de entrada.*/

  try {
    printf("                c==o\n");
    printf("              _/____\\_\n");
    printf("       _.,--'' ||^ || '`z._\n");
    printf("      /_/^ ___\\||  || _/o\\ '`-._\n");
    printf("    _/  ]. L_| || .||  \\_/_  . _`--._\n");
    printf("   /_~7  _ . ' ||. || /] \\ ]. (_)  . '`--.\n");
    printf("  |__7~.(_)_ []|+--+|/____T_____________L|\n");
    printf("  |__|  _^(_) /^   __\\____ _   _|\n");
    printf("  |__| (_){_) J ]K{__ L___ _   _]\n");
    printf("  |__| . _(_) \\v     /__________|________\n");
    printf("  l__l_ (_). []|+-+-<\\^   L  . _   - ---L|\n");
    printf("   \\__\\    __. ||^l  \\Y] /_]  (_) .  _,--'\n");
    printf("     \\~_]  L_| || .\\ .\\\\/~.    _,--''\n");
    printf("      \\_\\ . __/||  |\\  \\`-+-<''\n");
    printf("       ``---._|J__L|X o~~|[\\\\      \n");
    printf("              \\____/ \\___|[//     \n");
    printf("               `--'   `--+-'\n");
    printf("Nuevo Vuelo:\n\n");
    printf("      C%cdigo de vuelo: ",162);
    scanf("%s",&nuevoVuelo.codigo);
    if (!nuevoVuelo.ValidarCodigo()) {
      throw 0;	    	                         /*Filtro 1: Comprueba la longitud del código*/
    }
    printf("      D%ca (DD): ",161);
    scanf("%d",&nuevoVuelo.fecha.dia);
    printf("      Mes (MM): ");
    scanf("%d",&nuevoVuelo.fecha.mes);
    printf("      A%co (AAAA): ",164);
    scanf("%d",&nuevoVuelo.fecha.anno);
    printf("      Hora (HH:MM): ");
    if (!ValidarHueco(nuevoVuelo)) {
      throw 1;          /*Filtro 2: Comprueba que haya hueco para registrar un nuevo vuelo.*/
    }
    if (!CompararCodigo(nuevoVuelo.fecha.dia,nuevoVuelo.fecha.mes,
                        nuevoVuelo.fecha.anno,nuevoVuelo.codigo)) {
      throw 2;
    }
    scanf("%2d:%2d",&nuevoVuelo.fecha.hora,&nuevoVuelo.fecha.minuto);
    printf("      Plazas del vuelo: ");
    if (!nuevoVuelo.fecha.ValidarDiaMesHora()) {
      throw 3;  	              /*Filtro 3: Comprueba que la fecha introducida sea correcta*/
    }
    scanf("%d",&nuevoVuelo.plazas_inicial);
    printf("      Precio Inicial: ");
    scanf("%d",&nuevoVuelo.precio);
    if (nuevoVuelo.plazas_inicial<0 || nuevoVuelo.precio<0) {
      throw 4;  	 /*Filtro 4: Comprueba que el precio y las plazas sean valores positivos.*/
    }
                                                                /*Se acepta el nuevo vuelo.*/
    nuevoVuelo.AceptarNuevoVuelo();
    ListaVuelos[numeroVuelos] = nuevoVuelo;
    numeroVuelos++;
    printf("Vuelo registrado correctamente\n\n");
    system("pause");
    system("cls");
  }
  catch (int e) {                                                 /*Tratamiento de errores.*/
    printf("                                 * * * ERROR * * *\n\n");
    switch(e) {
      case 0:
      printf("            El c%cdigo de vuelo es demasiado largo.\n",162);
      printf("                 No puede superar los 7 caracteres\n\n");
      break;
      case 1:
      printf("        Se ha alcanzado el m%cximo n%cmero de vuelos\n",160,163);
      printf("                   permitidos para %s %d\n\n",listaM[nuevoVuelo.fecha.mes],
              nuevoVuelo.fecha.anno);
      break;
      case 2:
      printf("  El vuelo %s para %2d-%s-%4d ya est%c registrado en el sistema\n",nuevoVuelo.codigo,
              nuevoVuelo.fecha.dia,listaMcorta[nuevoVuelo.fecha.mes],nuevoVuelo.fecha.anno,160);
      break;
      case 3:
      printf("                       Fecha introducida no v%clida\n\n",160);
      break;
      case 4:
      printf("           El n%cmero de plazas y el precio inicial\n",163);
      printf("                       deben ser valores positivos\n\n");
      break;
      }
      system("pause");
      system("cls");
  }
}                                   /*Fin del procedimiento para el alta de un nuevo vuelo.*/


/*=========================================================================================
    Procedimiento principal 'OfertasDelMes' para listar los 5 vuelos más baratos del mes.
	1.- Pide los datos: Mes y año.
	2.- Verifica los datos.
	3.- Verifica que haya vuelos en esas fechas.
	4.- Ordena los vuelos por precio.
	5.- Imprime los vuelos en pantalla.
	=========================================================================================*/
void OfertasDelMes () {

  TipoVuelo temp;                 /*Variable TipoVuelo para almacenar los datos de entrada.*/
  TipoVuelo t_vuelo;                  /*Variable auxiliar TipoVuelo para ordenar un vector.*/
  VectorLocal ListaAux; 	/*Vector local donde se almacenarán algunos vuelos temporalmente.*/
  int lista=0;  		            /*Variable que sirve de índice del Vector Local 'ListaAux'.*/

  try {
  printf("         _____                     \n");
  printf("       .'/L|__`.            beep...   \n");
  printf("      / =[_]O|` \\        '      \n");
  printf("      |'+_____':|       '        beep...\n");
  printf("    __:='|____`-:__   '              \n");
  printf("   ||[] ||====| []||                  buscando ofertas...\n");
  printf("   ||[] | |=| | []||\n");
  printf("   |:||_|=|U| |_||:|\n");
  printf("   |:|||]_=_ =[_||:| \n");
  printf("   | |||] [_][]C|| |\n");
  printf("   | ||-''''''`-|| |\n");
  printf("   /|\\\\_\\_|_|_/_//|\\\n");
  printf("  |___|   /|\\   |___|   \n");
  printf("  `---'  |___|  `---'    \n");
  printf("         `---'\n\n");
  printf("Mes (MM): ");
  scanf("%d",&temp.fecha.mes);
  printf("A%co (AAAA): ",164);
  scanf("%d",&temp.fecha.anno);
  if (!temp.fecha.ValidarMes()) {
      throw 0;                 /*Filtro 1: Comprueba que la fecha introducida sea correcta.*/
  }
  for (int i=0;i<=numeroVuelos;i++) {               /*Busca la fecha en los vuelos del TAD.*/
    if (ListaVuelos[i].fecha.mes==temp.fecha.mes && ListaVuelos[i].fecha.anno==temp.fecha.anno
        && !ListaVuelos[i].VueloCompleto()) {              /*Descarta los vuelos completos.*/
      lista++;                        /*Tras una coincidencia, el índice se autoincrementa.*/
      ListaAux[lista]=ListaVuelos[i];            /*La coincidencia se almacena en ListaAux.*/
      }
  }
            /*Si tras el bucle el índice sigue siendo 0, es que no ha habido coincidencias.*/
  if (lista==0) {
      throw 1;
  }

  for (int i=1;i<=lista;i++) {   /*Se ordenan por precio utilizando el método de la burbuja*/
    for (int j=1;j<=lista;j++) {
      if (ListaAux[j].precio>ListaAux[i].precio && i!=j) {
        t_vuelo = ListaAux[j];
        ListaAux[j] = ListaAux[i];
        ListaAux[i] = t_vuelo;
      }
    }
  }                      /*Si se han encontrado más de 5 vuelos en esas fechas, ahora mismo
                           estarán los 5 más baratos en las primeras posiciones del vector.
                         Ajustamos la variable lista a 5 para imprimir por pantalla sólo 5.*/
  if (lista>5) {
    lista = 5;
    }                                             /*Se imprimen por pantalla los resultados*/
  printf("\n      Vuelos disponibles en %s %d\n\n",listaM[temp.fecha.mes],temp.fecha.anno);
  printf("  Vuelo  C%cdigo    D%ca   Hora   Precio\n",162,161);
  for (int i=1;i<=lista;i++) {
    printf("%5d   %7s     %2d  %02d:%02d   %6d\n",i,ListaAux[i].codigo,ListaAux[i].fecha.dia,
            ListaAux[i].fecha.hora,ListaAux[i].fecha.minuto,ListaAux[i].precio);
  }
  printf("\n");
  system("pause");
  system("cls");
  } catch (int e) {                                               /*Tratamiento de errores.*/
  printf("                                 * * * ERROR * * *\n\n");
    switch(e) {
      case 0:
      printf("                       Fecha introducida no v%clida\n\n",160);
      break;
      case 1:
      printf("  Lo sentimos, no se han encontrado vuelos en %s %d\n\n",listaM[temp.fecha.mes],
              temp.fecha.anno);
      break;
    }
    system("pause");
    system("cls");
  }
}                                  /*Fin del procedimiento para listar las ofertas del mes.*/

/*=========================================================================================
    Procedimiento principal 'ComprarPlazas' para comprar billetes de avión.
	1.- Pide los datos: Día, mes y año.
	2.- Verifica que la fecha introducida sea correcta.
	3.- Ordena por fecha los vuelos almacenados.
	4.- Verifica que haya vuelos en esa fecha, los que coinciden los va guardando.
	5.- Imprime todos los vuelos de esa fecha en pantalla.
	6.- Pregunta número de vuelo y cantidad de billetes que se desea comprar.
	7.- Verifica los datos, comprueba que haya asientos disponibles.
	8.- Imprime los billetes en pantalla.
	=========================================================================================*/
void ComprarPlazas() {
  int t_lista, t_plazas;                   /*Variables auxiliares para el proceso de compra*/
  TipoVuelo temp;              /*Variable auxiliar TipoVuelo para guardar datos de entrada.*/
  VectorLocal ListaAux;       /*Vector local donde se almacenarán los vuelos temporalmente.*/
  int lista = 1;                  /*Variable que sirve de índice del Vector Local ListaAux.*/

  try {
  printf("          ___            Saludos!\n");
  printf("         /---\\       '      le atiende relacciones cibern%cticas\n",130);
  printf("        | @ @:|    '               %cEn qu%c puedo ayudarle?      \n",168,130);
  printf("        |  ' :|  '                  \n");
  printf("         \\_-_/                         \n");
  printf("       _.d._.b.__                    \n");
  printf("   +'i\\  |\\_/|  /i'+\n");
  printf("   [_| \\ |   | / |_]\n");
  printf("  .' |  ):===:(  | `.\n");
  printf("  |:.'+-' | | '-+`.:|\n");
  printf("  |_| |-. |_|   | |_|\n");
  printf("  \\:\\ |-' /+\\   ! |:|\n");
  printf("   \\ \\|n._\\+/_.n| / /\n");
  printf("    \\XT::::-::::T/ /\n");
  printf("     'l-. `'' .-lXX\n");
  printf("      |: \\   / :|\n");
  printf("      |:  i-i  :|\n");
  printf("      |:  | |  :| \n");
  printf("      |:  | |  :|\n");
  printf("     \\|;_ | |__;|/\n");
  printf("      (__() ()__)      \n");
  printf("      |:  | |  :|       \n\n");
  printf("D%ca (DD): ",161);                               /*Pide los datos: Día, mes y año.*/
  scanf("%d",&temp.fecha.dia);
  printf("Mes (MM): ");
  scanf("%d",&temp.fecha.mes);
  printf("A%co (AAAA): ",164);
  scanf("%d",&temp.fecha.anno);
  if (!temp.fecha.ValidarDiaMes()) {
      throw 0;                             /*Verifica que la fecha introducida sea correcta.*/
  }
  OrdenarFechas();                                /*Ordena por fecha los vuelos almacenados.*/
  for (int i=0;i<=numeroVuelos-1;i++) {           /*Verifica que haya vuelos en esas fechas.*/
    if (ListaVuelos[i].fecha.dia==temp.fecha.dia && ListaVuelos[i].fecha.mes==temp.fecha.mes
        && ListaVuelos[i].fecha.anno==temp.fecha.anno) {

          ListaVuelos[i].punteroBusqueda = lista;    /*Cada vuelo registra su posición para
                                          ser localizado más adelante si ha sido el elegido.*/
          ListaAux[lista]=ListaVuelos[i];            /*Los que coinciden se van almacenando.*/
          lista++;
        }
  }
          /*Si el índice sigue siendo 1 tras el bucle, es que no ha encontrado coincidencias*/
  if (lista==1) {
       throw 1;
  }
                                 /*Imprime los vuelos por pantalla. Cada vuelo con su índice*/
  printf("\n      Vuelos disponibles para %d de %s de %d\n\n",temp.fecha.dia,
          listaM[temp.fecha.mes],temp.fecha.anno);
  printf("  Vuelo   C%cdigo    Hora    Plazas   Precio\n",162);
  for (int i=1;i<=lista-1;i++) {
    if (ListaAux[i].VueloCompleto()) {
                                       /*Los vuelos completos aparecen sin posición definida*/
      printf("    -    %7s   %02d:%02d    %6d   VUELO COMPLETO\n",ListaAux[i].codigo,
                ListaAux[i].fecha.hora,ListaAux[i].fecha.minuto,ListaAux[i].plazas);
    } else {
      printf("%5d    %7s   %02d:%02d    %6d    %6d\n",i,ListaAux[i].codigo,
              ListaAux[i].fecha.hora,ListaAux[i].fecha.minuto,ListaAux[i].plazas,
              ListaAux[i].precio);
    }
  }
                                    /*Se pide el número del vuelo (el índice del bucle [i]).*/
  printf("\n Si desea comprar billetes para alguno de los vuelos");
  printf("\n por favor introduzca el n%cmero del Vuelo.\n\n",163);
  printf(" Si por el contrario desea salir, introduzca 0.\n");
  printf("\n   Elegir vuelo: ");
  scanf("%d",&t_lista);
  if (t_lista==0) {
     throw 5;                     /*Dejamos que pulse 0 si no quiere comprar ningún billete.*/
  }
  printf("   N%cmero de plazas (m%cximo 5): ",163,160);
  scanf("%d",&t_plazas);                    /*Se pide el número de pasajes que va a comprar.*/
  printf("\n");
  if(t_lista>lista || t_lista<=0 || t_plazas<=0 || t_plazas>5) {
    throw 2;             /*Comprueba si se han introducido datos negativos o fuera de rango.*/
  } else if (ListaAux[t_lista].VueloCompleto()) {
    throw 3;                   /*Comprueba si se ha seleccionado un vuelo que está completo.*/
  } else if (ListaAux[t_lista].plazas - t_plazas < 0) {
    throw 4;                /*Comprueba si se ha solicitado comprar un número de plazas mayor
                                      al del número de plazas que tiene disponible el vuelo.*/
  }
  for (int i=0;i<=numeroVuelos;i++) {                   /*Imprime por pantalla los billetes.*/
    if (ListaVuelos[i].punteroBusqueda==t_lista) {                 /*Busca el vuelo elegido.*/
      for (int j=1;j<=t_plazas;j++) {               /*Para cada pasaje realiza lo siguiente:*/
        ListaVuelos[i].ActualizarPlazas();                           /*Actualiza las plazas.*/
        ListaVuelos[i].CalcularPrecio();                              /*Actualiza el precio.*/
        printf(" +----------------------------------+\n");             /*Imprime el billete.*/
        printf(" |          BILLETE %4d            |\n",j);
        printf(" | Vuelo: %7s      Precio: %4d |\n",ListaVuelos[i].codigo,
                ListaVuelos[i].precio);
        printf(" | Fecha: %2d-%3s-%4d  Hora: %02d:%02d  |\n",ListaVuelos[i].fecha.dia,
                listaMcorta[ListaVuelos[i].fecha.mes],ListaVuelos[i].fecha.anno,
                ListaVuelos[i].fecha.hora,ListaVuelos[i].fecha.minuto);
        printf(" | Asiento: %03d                     |\n",
                (ListaVuelos[i].plazas_inicial-ListaVuelos[i].plazas));
        printf(" +----------------------------------+\n\n");
      }
    }
  }
  printf("\n  Pasajes comprados correctamente.   \n\n");
  system("pause");
  system("cls");
  } catch (int e) {                                                /*Tratamiento de errores:*/
    switch(e) {
      case 0:
      printf("                                 * * * ERROR * * *\n\n");
      printf("                       Fecha introducida no v%clida\n\n",160);
      system("pause");
      system("cls");
      break;
      case 1:
      printf("                                 * * * ERROR * * *\n\n");
      printf("  Lo sentimos, no se han encontrado vuelos en %s %d\n\n",
              listaM[temp.fecha.mes],temp.fecha.anno);
      system("pause");
      system("cls");
      break;
      case 2:
      printf("                                 * * * ERROR * * *\n\n");
      printf("                     Datos introducidos no v%clidos\n\n",160);
      system("pause");
      system("cls");
      break;
      case 3:
      printf("                                 * * * ERROR * * *\n\n");
      printf("  Lo sentimos, el vuelo seleccionado est%c completo\n\n",160);
      system("pause");
      system("cls");
      break;
      case 4:
      printf("                                 * * * ERROR * * *\n\n");
      printf("                  Lo sentimos, el vuelo seleccionado\n");
      printf("                s%clo dispone de %d plazas disponibles\n\n",162,
              ListaAux[t_lista].plazas);
      system("pause");
      system("cls");
      break;
      case 5:
      system("cls");
      break;
    }
  }
}                                            /*Fin del procedimiento para comprar billetes.*/

/*=========================================================================================
    Procedimiento principal 'Calendario':
  1.- Pide los datos Mes y Año.
  2.- Verifica que los datos sean correctos.
  3.- Ordena los vuelos por fecha.
  4.- Almacena en ListaAux aquellos que coincidan en Mes y Año.
  5.- Imprime el calendario del mes por pantalla, seguido de la lista de vuelos del mes.
  =========================================================================================*/
void VuelosDelMes () {

  TipoVuelo temp;              /*Variable auxiliar TipoVuelo para guardar datos de entrada.*/
  VectorLocal ListaAux;       /*Vector local donde se almacenarán los vuelos temporalmente.*/
  TipoDia dia_inicio_semana, dia_semana;      /*Variables para la impresión del calendario.*/
  int dia_meses;                              /*Variable que apunta al vector 'dias_meses'.*/
  int lista=1;                   /*Variable que sirve de índice del VectorLocal 'ListaAux'.*/

  try {                                                         /*Pide los datos Mes y Año.*/
  printf("                                        .\n");
  printf("                              .-o\n");
  printf("                 .           /  |\n");
  printf("        .                 . /   |   .\n");
  printf("                           /    |\n");
  printf("                  .       /     |\n");
  printf("  .                      /      /         .\n");
  printf("             .          /    _./   .\n");
  printf("                   _.---~-.=:_\n");
  printf("                  (_.-=() <~`-`-.\n");
  printf("                 _/ _() ~`-==-._,>\n");
  printf("         ..--====--' `~-._.__()\n");
  printf("     o===''~~             |__()\n");
  printf("                .         \\   |             .\n");
  printf("                           \\  \\\n");
  printf("                            \\  \\     .\n");
  printf("        .                    \\  \\          \n");
  printf("                 .            \\  \\          \n");
  printf("                               \\_ \\        .\n");
  printf("                                 ~o\n");
  printf("Mes (MM): ");
  scanf("%d",&temp.fecha.mes);
  printf("A%co (AAAA): ",164);
  scanf("%d",&temp.fecha.anno);
  if (!temp.fecha.ValidarMes()) {
    throw 0;                      /*Comprueba si los datos introducidos no son correctos.*/
  }
  OrdenarFechas();                               /*Ordena por fecha los vuelos almacenados.*/
  for (int i=0;i<=numeroVuelos-1;i++) {
    if (ListaVuelos[i].fecha.mes==temp.fecha.mes && ListaVuelos[i].fecha.anno==temp.fecha.anno) {
      ListaAux[lista]=ListaVuelos[i];
      lista++;           /*Los vuelos que coinciden en mes y año se almacenan en el vector.*/
    } if (lista==1) {
      throw 1;   /*Si 'lista' sigue siendo 1 tras el bucle, no ha encontrado coincidencias.*/
    }
  }
                                                       /*Imprime la cabecera del calendario*/
  printf("\n%s%20d\n",listaM[temp.fecha.mes],temp.fecha.anno);
  printf("===========================\n");
  printf("LU  MA  MI  JU  VI | SA  DO\n");
  printf("===========================\n");

                                         /*Calcula el primer día del mes y año seleccionado*/
  dia_inicio_semana = temp.fecha.DiaSemana(temp.fecha.mes,temp.fecha.anno);

           /*Bucle para rellenar con puntos los huecos de la primera semana si los hubiese.*/
  for (int i=1;i<int(dia_inicio_semana);i++) {
      if (i==5) {
        printf(" . | ");
    } else {
        printf(" .  ");
    }
  }
  if (temp.fecha.mes==2&&temp.fecha.esBisiesto()) {
    dia_meses=29;             /*Ajusta el valor de dia_meses si es Febrero y año bisiesto.*/
  } else {
    dia_meses = dias_meses[temp.fecha.mes];
  }

               /*Bucle principal para imprimir cada día del mes. Hay 3 casos diferenciados:
                                Viernes (Imprimir ' 20 | ')
                                Domingo (Imprimir ' 20\n')
                                Otros   (Imprimir ' 20 ')
                                Para cada caso, compara si ese día (20) hay o no hay vuelo.
                Si hay vuelo, imprime el número del día (20). Si no hay vuelo, imprime '--'*/
  for (int i=1;i<=dia_meses;i++) {
    dia_semana = TipoDia(dia_inicio_semana-1);
    if (dia_semana == Domingo) {
      dia_inicio_semana = Lunes;
      if (HayVuelo(i,ListaAux,lista)) { /*Si hay vuelos ese día, imprime el número del día.*/
      printf("%2d\n", i);
      } else {
        printf("--\n");                            /*Si no hay vuelos ese día, imprime '--'*/
      }
    } else if (dia_semana == Viernes) {
      if (HayVuelo(i,ListaAux,lista)) {
        printf("%2d | ", i);
    } else {
      printf("-- | ");
    }
    } else if (HayVuelo(i,ListaAux,lista)) {
        printf("%2d  ", i);
    } else {
      printf("--  ");
    } dia_inicio_semana = TipoDia(dia_inicio_semana+1);
  }
            /*Bucle para rellenar con puntos los huecos de la última semana si los hubiese.*/
  if (dia_inicio_semana == 1) {
    printf("\n");
    } else {
      for (int i=int(TipoDia(dia_inicio_semana-1));i<=6;i++) {
        if (i==6) {
          printf(" .\n");
          } else if (i==4) {
            printf(" . | ");
          } else {
            printf(" .  ");
          }
      }
    }
    printf("\n\n");

                 /*El siguiente fragmento de código está comentado. El motivo es que en el
                 enunciado de la práctica no se pedía que se imprimiese la lista de vuelos
                  del mes tras el calendario, sin embargo me ha parecido que podía aportar
                algo positivo al programa. En cualquier caso, como digo, lo dejo comentado.*/
/*
    for (int i=1;i<=lista-1;i++) {
      if (ListaAux[i].VueloCompleto()) {
        printf("D%ca %2d - Vuelo %7s - Hora: %02d:%02d - VUELO COMPLETO\n",161,
                ListaAux[i].fecha.dia,ListaAux[i].codigo,ListaAux[i].fecha.hora,
                ListaAux[i].fecha.minuto);
        } else {
          printf("D%ca %2d - Vuelo %7s - Hora: %02d:%02d - Precio: %4d - Plazas: %3d\n",161,
                  ListaAux[i].fecha.dia,ListaAux[i].codigo,ListaAux[i].fecha.hora,
                  ListaAux[i].fecha.minuto,ListaAux[i].precio,ListaAux[i].plazas);
        }
      }
    printf("\n\n");*/
    system("pause");
    system("cls");
  } catch (int e) {                                               /*Tratamiento de errores:*/
    printf("                                 * * * ERROR * * *\n\n");
    switch (e) {
      case 0:
      printf("                       Fecha introducida no v%clida\n\n",160);
      break;
      case 1:
      printf("\n Lo sentimos, no se han encontrado vuelos en %s %d\n\n",
              listaM[temp.fecha.mes],temp.fecha.anno);
      break;
    }
    system("pause");
    system("cls");
  }
}                    /*Fin del procedimiento para imprimir el calendario de vuelos del mes.*/
