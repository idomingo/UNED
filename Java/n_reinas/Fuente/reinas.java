import java.util.Scanner;				// Lectura del archivo de ayuda.
import java.io.InputStream;				// Obtener recursos del archivo jar.
import java.io.File;					// Tratamiento de archivos.
import java.io.FileWriter; 				// Escritura en archivos (log y salida).
import java.io.IOException;				// Tratamiento de excepciones.
import java.text.SimpleDateFormat;		// Formato de fecha.
import java.util.Date;					// Obtener timestamp.
import java.util.Arrays;				// Arrays utilizados para controlar las distintas posiciones.

public class reinas {
	public static boolean t = false;			 // Activa el log de las operaciones al pasar "-t".
	public static boolean g = false;			 // Activa el modo gráfico al pasar "-g".
	public static boolean s = false;			 // Activa la escritura del resultado en un archivo.
//	public static boolean modoSimple = false;	 // Activa la ejecución del programa en modo simple. Deprecated -> ModoUltraRapido() (Linea 119)
	public static FileWriter log;	 			 // Escritura de archivo para el log.
	public static FileWriter output; 			 // Escritura de archivo para el resultado.
	public static int[] tablero;				 // Guarda la posición de las reinas.
	public static int fila = 0;					 // Indices 'fila' y 'posicion' para los dos bucles 'for' del algoritmo.	
	public static int posicion = 1;
	public static int scan = 1;					 // Contador de iteraciones del algoritmo. 
	public static long index = 0;				 // Contador de soluciones encontradas.
	public static int n = 0;					 // Lados del tablero n x m.
	public static int m = 0;					 
	
	/*	Método principal 'main'. Recorre los argumentos pasados.
	 * 	  Si coincide con '-g', '-h' o '-t' activa el modo gráfico, la ayuda o la traza respectivamente.
	 *	  Si es un número, lo toma como el tamaño del tablero. 
	 *    Si se quiere establecer un tablero rectangular se debe pasar '-r' seguido de los dos lados. Ejemplo: 'java -jar reinas.jar -r 4 5'.
	 *	  Si el argumento no coincide con ninguno de los casos anteriores se toma como nombre de archivo de salida.
	 *	  Tras evaluar los argumentos inicializa el Array del tablero y arranca el algoritmo.
	 */
	public static void main (String args[]) throws NullPointerException, IOException {	
		String archivo="";		// Guarda el nombre del archivo de salida.
		int modo = -1;			// Almacenar el valor introducido por el usuario cuando se pide seleccionar modo de ejecución.
		for (int i=0; i<args.length; i++) {												// Inicio del análisis de los argumentos.
			if (args[i].toLowerCase().equals("-h")||args.length==0) Error("ayuda", "", "");  // Muestra la ayuda.
			else if (args[i].toLowerCase().equals("-t")) t = true;							 // Activa la traza.
			else if (args[i].toLowerCase().equals("-g")) g = true;							 // Activa el modo gráfico.
			else if (args[i].toLowerCase().equals("-r")) {		// Con '-r' se espera los lados de un rectángulo en los dos siguientes argumentos.
				try {											
					if (n!=m) Error("duplicado_1", "", "");		// Si n y m son distintos es que ya se ha pasado previamente otros valores.
					n = Math.min(Integer.parseInt(args[i+1]), Integer.parseInt(args[i+2]));	// n será el menor de los lados: filas, num de reinas.
					m = Math.max(Integer.parseInt(args[i+1]), Integer.parseInt(args[i+2])); // m será el mayor: columnas, posiciones.
					if (n<=0 || m<=0) Error("rectangulo_1", args[i+1], args[i+2]);	
					if (n==m && (n==2 || n==3)) Error("size_2", args[i+1], "");
					tablero = new int[m];						// Se inicializa el tablero si no se han detectado errores previamente.
					Arrays.fill(tablero, 0, m, 0);
					i+=2;										// Como se han analizado 3 argumentos (-r y los 2 lados) se avanza 2 posiciones.
				} catch (Exception e) {
					Error("rectangulo_2", args[i+1], args[i+2]);// Captura el error si falla Integer.parseInt.
				}
			}
			else if (Character.isDigit(args[i].charAt(0))) {	// Cuando un argumento empieza por un número puede ser el lado del tablero
				try {											// o el nombre del archivo de salida. 
					int j = Integer.parseInt(args[i]);			// Si no es un Integer se captura la excepción y se trata como nombre de archivo.
					if (n!=0) Error("lado_1", args[i], Integer.toString(n)); // Si se pasan 2 Integer en los argumentos devuelve un error.
					n = j;										// Si no, se toma como el lado del tablero.
					if (n==1 || n>=4) {
						tablero = new int[n];
						Arrays.fill(tablero, 0, n, 0);			// Inicializa el array de las reinas.
						m = n;									// Al ser un cuadrado los dos lados son iguales. 
					} else if (n<=0) Error("size_1", args[i], "");
					else Error("size_2", args[i], "");
				} catch (Exception e) {							// Si el argumento no es un Integer se trata como nombre del archivo de salida.
					if (s==true) Error("salida_duplicada", args[i], archivo);
					s = true;
					archivo = args[i];
				}
			}
			else {							// Si el argumento no encaja en los anteriores supuestos se trata como nombre del archivo de salida.
				if (s==true) Error("salida_duplicada", args[i], archivo);
				s = true;
				archivo = args[i];
			}
		} 	// Fin del análisis de los argumentos
		if (n==0) Error("no_lado", "", "");	// Si tras evaluar args 'n' sigue siendo 0 (valor inicial) es que no se ha pasado el lado del tablero.
		if (s==true) {						// Inicia el objeto FileWriter para escribir en el archivo de salida.
			try {
				File outfile = new File(archivo);	
				if (outfile.exists()) Error("salida_1", archivo, "");
				output = new FileWriter (outfile);
			} catch (Exception e) {			// Esta excepción captura caracteres inválidos para nombres de archivos (por ejemplo '?')
				Error("salida_2", archivo, "");
			}
		}
		if (t==true) {								// Crea la carpeta para guardar los logs e inicia el objeto FileWriter.
			new File("Reinas_logs").mkdir(); 		
			String d = new SimpleDateFormat("'Reinas_Log_'yyyyMMddhhmmssSSS'.log'").format(new Date());
			File f = new File("Reinas_logs", d); 	
			log = new FileWriter(f);				
		}					
		if (n>=15) {								// Para valores superiores a 15 se da la opción de ejecutar en modo simplificado.
			InputStream iss = reinas.class.getResourceAsStream("simplificado");  	
			Scanner scn = new Scanner (iss, "UTF-8");// En el archivo 'simplificado' incluido en el jar se explica su funcionamiento.
			String simple = scn.useDelimiter("\\A").next();	
			System.out.println(simple);
			System.out.println("\n Por favor, elija el modo de ejecuci\u00f3n (0, 1 \u00f3 2): ");
			do {							// Se ofrecen 3 opciones al usuario: Salir, Modo normal y Modo simplificado (una única solución).
				Scanner in = new Scanner(System.in);
				try {
					modo = in.nextInt();
					if (modo==1) {
						System.out.println("Se ha elegido el modo normal. Por favor, p\u00f3ngase c\u00f3modo. Arrancando...");
					} else if (modo==2) {
						System.out.println("Se ha elegido el modo simplificado. Arrancando...");
						//modoSimple = true;
						ModoUltraRapido();	
					} else if (modo==0) System.exit(0);
					else System.out.println("Se ha introducido una opci\u00f3n no v\u00e1lida. Por favor, vuelva a intentarlo.");
				} catch (Exception e) {		
					System.out.println("Se ha introducido una opci\u00f3n no v\u00e1lida. Por favor, vuelva a intentarlo.");
				}
			} while (modo !=0 && modo!=1 && modo!=2);
		}
		if (n==1) SolucionRapida();			// Si uno de los lados del tablero es 1 se crea la solución directamente.
		else VueltaAtras();					// Si no, se arranca el algoritmo de forma normal.
	}
	
	/*	ModoUltraRapido(). Comentado en la memoria de la práctica. No utiliza la vuelta atrás, pero es un método que
	 * 		ofrece una solución válida de forma directa conociendo sólo el tamaño del tablero. 
	 */
	public static void ModoUltraRapido() throws IOException {
		int p = 2;
		for (int i=0; i<(n/2); i++) {
			tablero[i] = p;
			p+=2;
		}
		p = 1;
		for (int i=(n/2); i<n; i++) {
			tablero[i] = p;
			p+=2;
		}
		if (n%6 == 2) {
			int x = tablero[(n/2)];
			tablero[(n/2)] = tablero[(n/2) + 1];
			tablero[(n/2) + 1] = x;
			for (int i = (n/2) + 2; i<(n-1); i++) {
				int y = tablero[i];
				tablero[i] = tablero[i+1];
				tablero[i+1] = y;
			}
		} else if (n%6 == 3) {
			for (int i = 0; i < (n/2)-1; i++) {
				int x = tablero[i];
				tablero[i] = tablero[i+1];
				tablero[i+1] = x;
			}
			for (int i = 1; i <= 2; i++) {
				for (int j = n/2; j < (n-1); j++) {
					int y = tablero[j];
					tablero[j] = tablero[j+1];
					tablero[j+1] = y;
				}
			}
		}
		ImprimirSolucion();
		System.exit(0);
	}
	
	/*	Método utilizado cuando uno de los lados del tablero vale 1. 
	 *  Sólo se puede colocar una reina porque sólo hay una fila y el número de resultados diferentes será la magnitud del lado m.
	 */
	public static void SolucionRapida() throws IOException {
		for (int i=1; i<=m; i++) {
			tablero[0] = i;
			ImprimirSolucion();
			if (t==true) Log("solucion");
			index++; scan++;
		}		
		if (t==true) Log("fin");
		else System.exit(0);
	}
	
	/* Método que guarda los distintos mensajes de error.*/
	public static void Error(String txt, String err1, String err2) {
		String archivo = "";
		InputStream is = reinas.class.getResourceAsStream("Readme");  	
		Scanner sc = new Scanner (is, "UTF-8");							
		String h = sc.useDelimiter("\\A").next();	// El mensaje de ayuda está almacenado en el archivo 'Readme' dentro del jar.
		switch(txt) {
			case "ayuda":
			System.out.println(h);
			break;
			case "duplicado_1":
			System.out.println(" Se ha producido un error. El argumento '-r' se encuentra duplicado.");
			System.out.println(" Introduzca 'reinas -h' para obtener ayuda.\n");
			break;
			case "size_1":
			System.out.println(" Se ha producido un error al evaluar '"+err1+"'. El lado del tablero debe ser entero positivo");
			System.out.println(" Introduzca 'reinas -h' para obtener ayuda.\n");
			break;
			case "size_2":
			System.out.println(" No existen soluciones para tableros de lado "+err1+".");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
			break;
			case "rectangulo_1":
			System.out.println(" Se ha producido un error al evaluar '"+err1+"' '"+err2+"'. El lado del tablero debe ser entero positivo.");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
			break;
			case "rectangulo_2":
			System.out.println(" Se ha producido un error al evaluar los argumentos '-r "+err1+" "+err2+"'.");
			System.out.println(" Tras pasar '-r' se espera recibir las dimensiones de un tablero rectangular.");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
			break;
			case "lado_1":
			System.out.println(" Se ha producido un error al evaluar los argumentos '"+err1+"' y '"+err2+"'.");
			System.out.println(" Recomendamos archivos de salida con extensi\u00f3n.");
			System.out.println(" Si ha intentado crear un tablero rectangular, utilice '-r' seguido de los 2 lados.");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
			break;
			case "lado_2":
			System.out.println(" Se ha producido un error al evaluar el argumento '"+err1+"' como nombre de archivo de salida.");
			System.out.println(" Por favor, utilice caracteres v\u00e1lidos o introduzca 'reinas -h' para obtener ayuda.");
			break;
			case "salida_1":
			System.out.println(" Se ha producido un error. El archivo de salida '"+err1+"' ya existe.");
			break;
			case "salida_2":
			System.out.println(" Se ha producido un error al evaluar '"+err1+"' como archivo de salida.");
			System.out.println(" Por favor, revise que contenga caracteres permitidos para nombres de archivos.");
			break;
			case "no_lado":
			System.out.println(" Parece que se le ha olvidado introducir el lado del tablero.");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
			break;
			case "salida_duplicada":
			System.out.println(" Se ha producido un error al evaluar '"+err1+"' y '"+err2+"'.");
			System.out.println(" Introduzca 'reinas -h' para obtener m\u00e1s informaci\u00f3n.\n");
		}
		System.exit(0);  // Sea cual sea el mensaje de error siempre se finaliza el programa.
	}
	
	/* Método 'Log' que guarda los diferentes mensajes que se van a escribir en el log. */
	public static void Log(String txt) throws IOException {
		SimpleDateFormat f = new SimpleDateFormat("'['hh:mm:ss.SSS']'");// Formato de fecha para escribir cada línea del log.
		switch(txt) {
			case "checking":
			log.write("\n"+f.format(new Date())+"Comprobando fila: "+letra(fila)+"; desde posición: "+posicion); 
			log.flush();
			break;
			case "acierto":
			log.write("\n"+f.format(new Date())+"  Acierto: "); 
			for (int k=0;k<=fila;k++) {
				log.write(letra(k)+tablero[k]+"; ");
			} 
			log.flush();
			break;
			case "solucion":
			log.write("\n"+f.format(new Date())+"			SOLUCION #"+(index+1)+" ENCONTRADA: ");
			for (int k=0;k<=fila;k++) {
				log.write(letra(k)+tablero[k]+"; ");
			}
			log.write("Vuelta atrás #"+scan); 
			log.flush();
			break;
			case "fallo":
			log.write("\n"+f.format(new Date())+"Ningún acierto en fila "+letra(fila)+". -- Vuelta atrás #"+scan+" --"); 
			log.flush();
			break;
			case "fin":
			log.write("\n"+f.format(new Date())+"   Fin del programa. "+index+" solucion(es) encontrada(s).");
			log.close();
			System.exit(0);
			break;
		}
	}
	
	/* Método central del algoritmo VueltaAtras(). 
	 * 	Escanea el tablero (árbol) de arriba hacia abajo (filas = ramas = n) y de izquierda a derecha (posiciones = nodos = m).
	 *	Si la posición 'j' de la fila 'i' es completable, se guarda en 'tablero[i] = j' y se pasa a la siguiente fila.
	 *		Si el acierto se produce en la última fila se entiende que ya se tiene una solución completa. 
	 *		En este caso se imprime la solución. Se elimina la posición guardada de las dos últimas filas (se pone de nuevo a '0')
	 *		y se escanea la última fila que aún tenga OpcionesPendientes().	 
	 *	Si no se produce un acierto se sigue escaneando la rama hasta llegar al último nodo. 
	 *  Si llega al final sin acierto se 'vuelve atrás' de la misma forma que con los aciertos.
	 *	El algoritmo finaliza cuando la primera fila tiene guardada la última posición y se está explorando la última posición de la segunda fila.
	 */
	public static void VueltaAtras () throws NullPointerException, IOException {												
		do {												
			if (t==true) Log("checking");
			for (int i=fila; i<n; i++) {			// Primer bucle for. Recorre las filas (desde 0 a n-1)
				for (int j=posicion; j<=m; j++) {		// Segundo bucle for. Recorre las posiciones (columnas, de 1 a m)
					if (tablero[0]==m&&fila==1&&j==m) {		// Condición que comprueba que se han evaluado todas las posibles soluciones --> Fin.
						if (t==true) Log("fin");
						System.exit(0);
					}
					if (ComprobarSolucion(i, j)) {		// PRIMER BLOQUE: Si se produce un acierto.
						tablero[i]=j;						// Guarda la posición de la reina en la fila actual. Solución k-prometedora.		
						if (t==true) Log("acierto");
						if (i==n-1) {						// Solucion COMPLETA: Si la fila actual(i) es la última fila(n-1).
							if (t==true) Log("solucion");
							ImprimirSolucion();
							index++;
						/*	if (modoSimple == true) {		// FIN del programa si se tiene una solución y está activado el modo simple.
								if (t==true) Log("fin");	// Deprecated --> ModoUltraRapido() (Linea 119)
								System.exit(0);
							}							*/
							if (tablero[i-1]==m) {		//	Tras obtener una solución completa se vuelve atrás hasta la rama más
								Vuelta2(i);				//	próxima que aún tenga nodos sin recorrer.
								break;					
							} 	Vuelta1(i);				
								break;
						}
						fila++;						//	Pasa a la fila siguiente si el acierto no genera una solución completa.
						posicion=1;					//  Empieza a escanear la nueva fila desde la primera posición.
						break;													
					}
					if (j==m) {							// SEGUNDO BLOQUE: Si se llega al final de una fila sin ningún acierto.
						if (t==true) Log("fallo");				
						if (tablero[i-1]==m) {			//  El mecanismo para la 'vuelta atrás' es el mismo que cuando hay un acierto.
							Vuelta2(i);	
							break;
						}	Vuelta1(i);
							break;										
					}													
				}																
				if (fila<i) break;		// Al salir del bucle interno (j) se comprueba si se ha modificado el índice (fila) del bucle externo (i).
			}				        	// Si se ha modificado este índice se sale del bucle y se volverá a entrar con los nuevos índices.
		} while (true);						
	}
	
	/* Métodos Vuelta1 y Vuelta2. 
	 *	Se utilizan para implementar la vuelta atrás. 
	 *		-Si la fila anterior tiene guardada la última posición se vuelve atrás 2 filas (Vuelta2)
	 *		-Si no, se vuelve atrás 1 fila (Vuelta1).
	 *	Estos métodos modifican las variables globales 'fila' y 'posicion' que sirven de índices para los bucles del algoritmo VueltaAtras().
	 *  También borran las posiciones correspondientes guardadas en el tablero e incrementan el contador de iteraciones.
	 */
	public static void Vuelta1(int i) {
		fila = i - 1;										
		posicion = tablero[i-1] + 1;
		tablero[i] = tablero[i-1] = 0;
		scan++;	
	}
	public static void Vuelta2(int i) {
		fila = i - 2;
		posicion = tablero[i-2] + 1;
		tablero[i] = tablero[i-1] = tablero[i-2] = 0;
		scan++;
	}
	
	/* Método ComprobarSolucion (fila, posicion)
	 *	Compara la posición de la reina de la fila actual con las posiciones guardadas de las filas anteriores.
	 *		-Devuelve true si la posición es válida.
	 * 		-Devuelve false si causa conflicto con otras filas.
	 *  El conflicto aparece cuando coincide en fila, columna o en las diagonales.
	 */
	public static boolean ComprobarSolucion (int fila, int posicion) {
		if (fila == 0 && tablero[0]==0) return true;
		for (int i=0; i<fila; i++) {
			if (posicion == tablero[i] || posicion == tablero[i]-(fila-i) || posicion == tablero[i]+(fila-i)) return false;
			if (tablero[i]==0) return false;
		}
		return true;
	}
	
	/* Método letra(int i)
	 *	Genera una secuencia de letras en función del valor introducido. 
	 * letra(0) = A, letra(26) = AA, letra(700) = ZY, letra(729) = ABB...
	 */
	public static String letra(int i) {
		return i < 0 ? "" : letra((i / 26) - 1) + (char)(65 + i % 26);
	}
	
	/* Método ImprimirSolucion() imprime cada solución completa.
	 * 	Si, además, está activado el modo gráfico, llama al método Grafico() para imprimir el tablero correspondiente.
	 */
	public static void ImprimirSolucion() throws IOException {
		SimpleDateFormat time = new SimpleDateFormat("'['hh:mm:ss.SSS']'");	// Timestamp a modo informativo.
		if (s==true) output.write(time.format(new Date())+" Solucion #"+(index+1)+": ");
		else System.out.print(time.format(new Date())+" Solucion #"+(index+1)+": ");
		for (int i=0; i<n; i++) {
			if (s==true) output.write(letra(i)+tablero[i]+"; ");
			else System.out.print(letra(i)+tablero[i]+"; ");
		}
		if (s==true) {
			if (g==false) output.write("\n"); 
			output.flush();
		} else System.out.println("\n");
		if (g==true) Grafico();
	}
	
	/*	Método Grafico() que imprime un tablero con la solución actual. */
	public static void Grafico() throws IOException {
		String linea = "-";
		String nums ="   ";
		String fila = " |";
		for (int i=0; i<m; i++) {
			linea = linea.concat("----");
			if ((i+1)<10) nums = nums.concat("  0"+(i+1));
			else nums = nums.concat("  "+(i+1));
		}
		for (int i=1; i<=n; i++) {
			if (s==true) output.write("\n   "+linea); 
			else System.out.println("   "+linea);
			for (int j=1; j<=m; j++) {
				if (tablero[i-1]==j) fila = fila.concat(" R |");
				else if (i%2==0) {					
					if (j%2==0)	fila = fila.concat(" * |");
					else fila = fila.concat("   |");
				} else {
					if (j%2==0)	fila = fila.concat("   |");
					else fila = fila.concat(" * |");
				}
			}
			if (s==true) {
				if (i<27) output.write("\n "+letra(i-1)+fila);
				else output.write("\n"+letra(i-1)+fila);
			}
			else {
				if (i<27) System.out.println(" "+letra(i-1)+fila);
				else System.out.println(letra(i-1)+fila);
			}
			fila = " |";
		}
		if (s==true) {
			output.write("\n   "+linea);
			output.write("\n"+nums+"\n\n");
			output.flush();
		}
		else {
			System.out.println("   "+linea);
			System.out.println(nums+"\n\n");
		}
	}
}