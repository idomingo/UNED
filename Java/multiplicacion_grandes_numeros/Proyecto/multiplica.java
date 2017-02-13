/**
 * class: multiplica
 * Multiplica dos números enteros cualquiera x e y.
 * Los datos se puede introducir desde el terminal o leer desde un archivo
 * especificado como argumento. El producto se puede obtener
 * por el terminal o se puede guardar en un archivo.
 * Argumentos de entrada:
 * [-h] Muestra un mensaje de ayuda por pantalla.
 * [-t] Guarda la traza de las operaciones en multiplica_logs/<date>.log
 * [archivo_entrada] [archivo_salida]
 * 
 * @IkerDomingoPérez 
 * @71126454N
 * @PREDA_UNED_LasTablas
 * @2016
 */
import java.util.Scanner;				// Lectura de datos
import java.io.File;					// Tratamiento de archivos
import java.io.FileWriter; 				// Escritura en archivos
import java.io.FileReader;              // Lectura de archivos
import java.io.FileNotFoundException;	// Tratamiento de excepciones
import java.io.IOException;				// Tratamiento de excepciones
import java.text.SimpleDateFormat;		// Formato de fecha 
import java.util.Date;					// Obtener timestamp
import java.io.InputStream;				// Obtener recurso del archivo jar

public class multiplica {

	public static boolean traza = false; // Guarda el log de las operaciones al pasar como argumento "-t"
	public static FileWriter log;
	public static boolean negX = false;  // Controlan el signo de los números en la entrada
	public static boolean negY = false;
	public static int index = 0;		 // Contador de llamadas al algoritmo recursivo.
	
	/* Método principal. Ejecuta el programa en función de los argumentos pasados.
	 * Si existe al menos un argumento que sea "-h" o si se introducen más argumentos de los esperados, muestra la ayuda y termina el programa.
	 * Si no hay "-h" busca "-t" para activar o no la traza. 
	 * Dependiendo de si se ha activado la traza y del número de elementos de args[] el método espera nombres de fichero en las posiciones 0, 1 ó 2.
	 * Llamadas a métodos:
	 *	Input() 						Entrada y salida por terminal.
	 *	InputFile(args[m]) 				Entrada desde archivo, salida por terminal.
	 *	InOutFile(arcs[m], args[n])  	Entrada y salida a fichero. 
	 */	
	public static void main(String args[]) throws FileNotFoundException, IOException {
		 
		InputStream is = multiplica.class.getResourceAsStream("Readme");  //El mensaje de ayuda está almacenado en el archivo 'Readme' dentro del jar
		Scanner s = new Scanner (is, "UTF-8");							  //Lee el archivo
		String h = s.useDelimiter("\\A").next();;						  //useDelimiter permite que no pierda el formato para mostrarlo por pantalla

		if (args.length == 0) Input(); 
		for (String element:args) {
			if (element.equals("-h")||args.length>3) {
				System.out.println(h);
				System.exit(0);
			} 
		}
		for (String element:args) {
			if (element.equals("-t")) {
				traza = true;
				new File("Multiplica_logs").mkdir();  //Crea la carpeta para guardar los logs
				String d = new SimpleDateFormat("yyyyMMddhhmmssSSS'.log'").format(new Date());
				File f = new File("Multiplica_logs", d); //Crea un archivo log con timestamp al milisegundo y revisa que no exista otro igual.
				if (f.exists()) { 
					System.out.println("Se ha producido un error al intentar guardar el log. \nEl archivo " + f + " ya existe.");
					System.exit(0);
				} 
				log = new FileWriter(f);
				if (args.length == 1) Input();
				if (args.length == 2) InputFile(args[1]);
				if (args.length == 3) InOutFile(args[1], args[2]);
				System.out.println(h);
				System.exit(0);
			}
			if (args.length == 1) InputFile(args[0]);
			if (args.length == 2) InOutFile(args[0], args[1]);
			System.out.println(h);
			System.exit(0);
		}	
	}
			
	// Método que revisa si un número leido como String es un número entero válido. 
	// Si el número es válido devuelve true para número negativo y false para positivo. 
	// El resultado se guarda en las variables globales negX y negY. 
	// Si el número no es válido finaliza el programa.
	public static boolean Comprobar(String x) {
		boolean numero_valido, signo;
		if (x.startsWith("-")) {
			x = x.substring(1);
			signo = true;
		} else if (x.startsWith("+")) {
			x = x.substring(1);
			signo = false;	
		} else signo = false;
		for (int i=0; i<x.length(); i++) {
			numero_valido = false;
			if (Character.isDigit(x.charAt(i))) {
				numero_valido = true;
				continue; 
			}
			if (numero_valido==false) {
				System.out.println("El n\u00famero introducido no es v\u00e1lido. Contiene el caracter " + x.charAt(i));
				System.exit(0);
			}
		}
		return signo;
	}
	
	// Método que revisa si un número tiene signo '+' o '-' y lo elimina. 
	public static String Signo(String x) {
		if (x.startsWith("-")) {
			x = x.replace("-", "");
		} else if (x.startsWith("+")) {
			x = x.replace("+", "");
		}
		return x;
	}
	
	//	Método para igualar en longitud 2 cadenas de caracteres añadiendo ceros a la izquierda.			
    public static String Igualar(String x, String y) {
        int aux = y.length() - x.length();
        for (int i=1; i<=aux; i++) {
        x = "0".concat(x);
        }
        return x;
    }
	
	// Método que suma 2 números x + y guardados como String. 
	// Primero iguala en longitud los números y luego se suma dígito a dígito con acarreo.
    public static String Suma (String x, String y) {
        String resultado = "";
        boolean acarreo = false;
        if (x.length() < y.length()) {
            x = Igualar(x, y);
        } else if (x.length() > y.length()) {
            y = Igualar(y, x);
        }
        for (int i = x.length() - 1; i >= 0; i--) {
            int j = Integer.parseInt(String.valueOf(x.charAt(i)));
            int k = Integer.parseInt(String.valueOf(y.charAt(i)));
            int m = j+k;
            if (acarreo == true) m++;
            if (m>=10) {
                m = m % 10;
                acarreo = true; 
            } else {
                acarreo = false;
            } 
            resultado = Integer.toString(m).concat(resultado);
        }
            if (acarreo == true) {
            return "1".concat(resultado);
        } else {
			return resultado;
		}
    }
	
	// Método que resta 2 números x - y guardados como String. 
	// Se resta como en el colegio. Número a número y con acarreo.
	// En la llamada a este método el número 'x' siempre va a ser mucho mayor que el número 'y', por lo que
	// no tiene en cuenta un posible resultado negativo.
	public static String Resta (String x, String y) {
		String resultado = "";
		int j, k, m;
		boolean acarreo = false;
        if (y.length() < x.length()) y = Igualar(y, x); 
		for (int i = x.length() - 1; i >= 0; i--) {
			j = Integer.parseInt(String.valueOf(x.charAt(i)));
			k = Integer.parseInt(String.valueOf(y.charAt(i)));
			if (acarreo == true) {
			    m = j-k-1;
			 } else {
			     m = j-k;
			 }
			if (m < 0) {
				acarreo = true;
				m += 10;
			} else {
				acarreo = false;
			}
			resultado = Integer.toString(m).concat(resultado);
		}
		return resultado;
	}
	
	// Método que comprueba si un número almacenado como String es todo ceros.	
	public static boolean NumeroCero (String x) {
		boolean numero_cero = false;
		for (int i=0; i<x.length(); i++) {
			if (x.charAt(i)=='0') {
				numero_cero = true; 
			} else {
				numero_cero = false;
				break;
			}
		}
			return numero_cero;
	}
	
	/* Método karatsuba. Núcleo del algoritmo. Multiplica 2 números guardados como cadena de caracteres ("x" * "y").	
	 * 
	 *
	 *
	 */
    public static String karatsuba(String x, String y) throws IOException {
        String A, B, C, D, resultado;  
        int m, n;
		// Inicializa el log. El timestamp se actualiza cada vez que se escribe una línea. 
		SimpleDateFormat sdfLog = new SimpleDateFormat("'Multiplica_['yyyy-MM-dd_hh:mm:ss.SSS']'");
		if (traza == true) {			
			if (index==0) log.write(sdfLog.format(new Date())+" INICIO\n"+sdfLog.format(new Date())+" AB: " + x + "\n"+sdfLog.format(new Date())+" CD: " + y + "\n");
			else log.write(sdfLog.format(new Date())+" Karatsuba - Algoritmo Recursivo - Iteraci\u00f3n #" + index + " \n"+sdfLog.format(new Date())+" AB: " + x + "\n"+sdfLog.format(new Date())+"  CD: " + y + "\n");
		}
		index++; //Incrementa el contador de llamadas recursivas al algoritmo.
		
		// Comprueba si alguno de los 2 números es igual a cero -> Primera Solución Simple.
		if (NumeroCero(x)==true || NumeroCero(y)==true) {
			return "0";		
		}

		// Si la suma del número de dígitos de 2 números x e y es igual o inferior a 9, se pueden multiplicar 
		// sin sobrepasar el límite para Integer en Java (2^32 = 10 cifras)
        if (x.length() + y.length() <= 9) return Integer.toString(Integer.parseInt(x)*Integer.parseInt(y));
		
		// Iguala los números añadiendo ceros a la izquierda si son de diferente tamaño.
		if (x.length() < y.length()) {
            x = Igualar(x, y);
			if (traza == true) log.write(sdfLog.format(new Date())+"  -Igualar longitud-\n"+sdfLog.format(new Date())+" AB: " + x + "\n"+sdfLog.format(new Date())+" CD: " + y + "\n");
        } else if (x.length() > y.length()) {
            y = Igualar(y, x);
			if (traza == true) log.write(sdfLog.format(new Date())+"  -Igualar longitud-\n"+sdfLog.format(new Date())+" AB: " + x + "\n"+sdfLog.format(new Date())+" CD: " + y + "\n");
        }
		// Partimos cada número por la mitad en 2 subcadenas de longitud m y n. Si el número es de longitud impar la primera subcadena es la más larga	
		// 'n' se usará más adelante al multiplicar la parte correspondiente por 10^n o 10^n/2
		// teniendo en cuenta que en el algoritmo 'n' hace referencia a la longitud del número, aquí multiplicaremos por 10^2n y 10^n respectivamente.
        m = x.length()/2 + x.length()%2;
        n = x.length()/2;
        A = x.substring(0, m);
        B = x.substring(m);
        C = y.substring(0, m);
        D = y.substring(m);
		if (traza == true) log.write(sdfLog.format(new Date())+" Divisi\u00f3n en substrings:\n"+sdfLog.format(new Date())+"  A: " + A + "  B: " + B + "\n"+sdfLog.format(new Date())+"  C: " + C + "  D: " + D + "\n");   
		
		/* Implementación del algoritmo con 4 multiplicaciones. Fórmula general: AB * CD = ACx10^n + (AD + CB)x10^n/2 + BD		
         * String AC = karatsuba(A, C);
         * for (int i=1;i<=n*2;i++) {AC = AC.concat("0");}
         * String ADBC = Suma(karatsuba(A, D), karatsuba(B, C));
         * for (int i=1;i<=n;i++) {ADBC = ADBC.concat("0");}
         * String BD = karatsuba(B, D);
         * return Suma(Suma(res1, res2), res3).replaceFirst("^0*", "");	
		 */
		
		/* 3 multiplicaciones. Fórmula general: AB * CD = [AC * 10^n] + [K * 10^(n/2)] + [BD]		
		 * 														K = [(A+B)(C+D) - AC - BD]								
		 */
		// Llamadas recursivas al algoritmo. AB (primera), K (segunda) y BD (tercera)
		String AC = karatsuba(A, C);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Mult A: " + A + " * C: " + C + " = " + AC + "\n");
		String BD = karatsuba(B, D);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Mult B: " + B + " * D: " + D + " = " + BD + "\n");
		String suma1 = Suma(A, B);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Suma A: " + A + " + B: " + B + " = " + suma1 + "\n");
		String suma2 = Suma(C, D);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Suma C: " + C + " + D: " + D + " = " + suma2 + "\n");
		String mult = karatsuba(suma1, suma2);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Mult [(Suma A + B): " + suma1 + " * (Suma C + D): " + suma2 + "] = " + mult + "\n");
		String K = Resta(Resta(mult, AC), BD);
		if (traza == true) log.write(sdfLog.format(new Date())+"   Resta [Mult((A+B)(C+D)): " + mult + " - AC: " + AC + " - BD: " + BD + "] = " + K + "\n");
		
		// Multiplicamos las partes primera y segunda por 10^2n y 10^n
		for (int i=1;i<=n*2;i++) {		// AC * 10^2n
            AC = AC.concat("0");
        }
		for (int i=1;i<=n;i++) {		// K * 10^n
            K = K.concat("0");
        }
		// Obtenemos el resultado, eliminamos primero los ceros a la izquierda.
		resultado = Suma(Suma(AC, K), BD).replaceFirst("^0*", ""); 
		if (traza == true) {
			log.write(sdfLog.format(new Date())+"  ------AB * CD = [AC * 10^n] + [K * 10^(n/2)] + [BD]	------\n"+sdfLog.format(new Date())+" K = [(A+B)(C+D) - AC - BD]\n");
			log.write(sdfLog.format(new Date())+" [AC * 10^n] = 	" +AC + "\n");
			log.write(sdfLog.format(new Date())+" [K * 10^(n/2)] = 	" +K + "\n");
			log.write(sdfLog.format(new Date())+" [BD] = 		" +BD + "\n");
			log.write(sdfLog.format(new Date())+" [AC + K + BD] = 	" +resultado +"\n"); 
			log.flush();
		}
		return resultado;
    }
	
	// Método Input(). Entrada y salida de datos por el terminal. 
	// Lee 2 números 'x' e 'y'. Los guarda como String. 
	// Verifica que son números válidos y apunta el signo de cada uno en 'negX' y 'negY'.
	// Elimina el signo (si lo hay) y llama al método karatsuba(x, y).
	// Si los signos coinciden, devuelve el resultado sin signo. Si no, lo precede de '-'.
	public static void Input() throws IOException {
		String x, y;
		Scanner input = new Scanner(System.in);
		System.out.print("Introduzca el primer n\u00famero: ");
		x = input.next();
		negX = Comprobar(x);
		System.out.println("N\u00famero guardado: " + x);
		System.out.print("Introduzca el segundo n\u00famero: ");
		y = input.next();
		negY = Comprobar(y);
		System.out.println("N\u00famero guardado: " + y);
		x = Signo(x);
        y = Signo(y);
		if (negX==negY)	{
			System.out.println("\n------------------RESULTADO---------------------------\n"+karatsuba(x, y));
		} else {
			System.out.println("\n\n------------------RESULTADO---------------------------\n-"+karatsuba(x, y));
		} 
		if (traza==true) log.close();
		System.exit(0);
	}
	
	// Método InputFile(args[m]). Se leen los datos desde el archivo pasado como argumento.
	// La salida se muestra por el terminal.
	public static void InputFile(String file) throws FileNotFoundException, IOException {
		String x, y;
		File f = new File(file);
		if (!f.isFile()) {			 // Comprueba que el archivo de entrada exista.
			System.out.println("Se ha producido un error. El archivo de entrada '" + file + "' no existe.");
			System.exit(0);
		} else if (!f.canRead()) { 	 // Comprueba que se puede leer el archivo.
			System.out.println("Se ha producido un error. El archivo de entrada '" + file + "' est\u00e1 protegido y no se puede leer.");
			System.exit(0);
		} else if (f.length()==0) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + file + "' no contiene datos.");
			System.exit(0);
		}
		Scanner s = new Scanner(new FileReader(f));
		do {
		x = s.next().replaceFirst("^ *", "");	// Lee el contenido del archivo utilizando el espacio en blanco ' ' como separador y elimina los espacios en blanco a la izquierda.
		} while (x.isEmpty()); 					// Bucle mientras el contenido sea nulo: De esta forma se ignoran líneas en blanco.
		negX = Comprobar(x);					// Comprueba que el número leido es válido
		if (!s.hasNext()) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + file + "' s\u00f3lo contiene un n\u00famero");
			System.exit(0);
		}
		do {
		y = s.next().replaceFirst("^ *", "");
		} while (y.isEmpty());
		negY = Comprobar(y);
		if (s.hasNext()) {						// Comprueba que se ha terminado de leer el archivo. Si contiene algo más que dos números devuelve un error y finaliza el programa.
			System.out.println("Se ha producido un error. El archivo de entrada '"+file+"' contiene m\u00e1s de dos n\u00fameros.");
			System.exit(0);
		}
		System.out.println(" Primer N\u00famero: " + x);
		System.out.println(" Segundo N\u00famero: " + y);
		x = Signo(x);
		y = Signo(y);
		System.out.println(" ------------------RESULTADO---------------------------");
		if (negX==negY)	{
			System.out.println(karatsuba(x, y));
		} else {
			System.out.println("-"+karatsuba(x, y));
		} 
		if (traza==true) log.close();
		System.exit(0);
	}	

	
	// Método InOutFile(args[m], args[n]). Lee los datos desde el archivo args[m] y escribe el resultado en args[n].	
	public static void InOutFile(String FileIn, String FileOut) throws FileNotFoundException, IOException {
		String x, y;
		File in = new File(FileIn);
		if (!in.isFile()) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + FileIn + "' no existe.");
			System.exit(0);
		} else if (!in.canRead()) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + FileIn + "' est\u00e1 protegido y no se puede leer.");
			System.exit(0);
		} else if (FileIn.length()==0) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + FileIn + "' no contiene datos.");
			System.exit(0);
		}
		File out = new File(FileOut);	
		if (out.exists()) {				//Comprueba que el archivo de salida no existe. Si ya existe un archivo con ese nombre devuelve error y finaliza el programa.
			System.out.println("Se ha producido un error. El archivo de salida '" + FileOut + "' ya existe.");
			System.exit(0);
		}
		FileWriter f = new FileWriter(out);
		Scanner s = new Scanner(new FileReader(in));
		do {
			x = s.next().replaceFirst("^ *", "");	  
		} while (x.isEmpty()); 
		negX = Comprobar(x);
		if (!s.hasNext()) {
			System.out.println("Se ha producido un error. El archivo de entrada '" + FileIn + "' s\u00f3lo contiene un n\u00famero");
			System.exit(0);
		}
		do {
			y = s.next().replaceFirst("^ *", "");
		} while (y.isEmpty());
		negY = Comprobar(y);
		if (s.hasNext()) {
			System.out.println("Se ha producido un error. El archivo de entrada '"+FileIn+"' contiene m\u00e1s de dos n\u00fameros.");
			System.exit(0);
		}
		x = Signo(x);
		y = Signo(y);
		if (negX==negY)	{		// En el archivo de salida sólo se escribe el resultado.
			f.write(karatsuba(x, y));
			f.close();
		} else {
			f.write("-"+karatsuba(x, y));
			f.close();
		} 
		if (traza==true) log.close();
		System.exit(0);
	} 
}