// Librerias
#include <cmath>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


// Variables globales
int matriz[ 1000 ][ 1000 ];


// Funciones
void vaciarMatriz( int );
void imprimirMatriz( int );
void valoresManual( );
void leerArchivo( );
void aleatorios( );


int main()
{
	system("cls"); // Limpiar consola
	system("title Reemplazo FIFO"); // Cambiar titulo ventana
	setlocale(LC_ALL, ""); // Aceptar acentos

    // Variables
    int opcion = 0;

    do
    {
        // Limpiar consola cada que se entra
        system( "cls" );

        // Titulo
        cout << "\n Reemplazo FIFO " << endl;

        cout << " Menu " << endl;

        // Opciones dentro del algoritmo
        cout << " 1. Llenar los valores manualmente. " << endl;
        cout << " 2. Leerlos de un archivo txt." << endl;
        cout << " 3. Valores aleatorios." << endl << endl;

        // Lectura de la opcion seleccionada
        cout << " Opcion: "; cin >> opcion;

    // Validacion de la opcion
    } while ( opcion != 1 && opcion != 2 && opcion != 3 );
    

    // Mandar a cada opcion
    switch ( opcion )
    {

        // 1. Llenar los valores manualmente.
        case 1:
            valoresManual( );
            break;

        // 2. Leerlos de un archivo.txt.
        case 2:
            leerArchivo( );
            break;

        // 3. Valores aleatorios
        case 3:
            aleatorios( );
            break;
        
        default: break;
    }

    // Detener ejecucion
    system( "pause" );
	return 0;	
}


// Vaciar la matriz por si exisitiera valores basura
void vaciarMatriz( int k )
{
    // Recorrer la matriz la cantidad especificada
    for ( int m = 0; m < k; m++ )
    {
        for ( int f = 0; f < k; f++ )
        {
            matriz[ m ][ f ] = -1;
        }
    }
}


// Funcion que permite imprimir la matriz que se esta utilizando
void imprimirMatriz( int limite )
{

    // Encabezados de la tabla
    cout << "Proce\tLlega\ttiempo\tPriori\tInicio\t Fin\tTiemTot\tEspera\tTiemPro" << endl;

    // Recorrer tabla la cantidad de procesos
    for ( int i = 0; i < limite; i++ )
    {

        // Imprimir cada renglon de la tabla
        for ( int k = 0; k < 9; k++ )
        {

            // Imprimir por temas de estetica
            if( matriz[ i ][ k ] < 10 ) cout << "  " << matriz[ i ][ k ] << "\t";
            else if( matriz[ i ][ k ] < 100 && matriz[ i ][ k ] >= 10 ) cout << " " << matriz[ i ][ k ] << "\t";
            else cout << matriz[ i ][ k ] << "\t";
        }

        // Separar cada renglon
        cout << endl;
    }
}


// Opcion 1. Introducir los valores manualmente
void valoresManual( )
{
    int noProcesos = 0;

    // Pedir cantidad de procesos
	cout << "Introduce la cantidad de procesos: "; cin >> noProcesos; 

    // Vaciado de los espacios que necesitamos
    vaciarMatriz( noProcesos );

    // Variables que se ocupan y se piden al usuario por cada proceso
    int llegada = 0 , tiempo = 0 , prioridad = 0;

    // Ciclo para pedir datos
    for ( int k = 0; k < noProcesos; k++ )
    {

        // Titulo del Proceso
        cout << " Proceso #" << ( k + 1 ) << endl;

        for (int i = 0; i < 9; i++)
        {

            // Para cada caso
            switch ( i )
            {

                // Nombre del proceso
                case 0:
                    matriz[ k ][ i ] = ( k + 1 );
                    break;

                // Pedir tiempo de llegada
                case 1:
                    cout << " Llegada: "; cin >> llegada;
                    matriz[ k ][ i ] = llegada;
                    break;

                // Pedir tiempo de que se toma
                case 2:
                    cout << " Tiempo: " ; cin >> tiempo;
                    matriz[ k ][ i ] = tiempo;
                    break;

                // Pedir prioridad
                case 3:
                    cout << " Prioridad: "; cin >> prioridad;
                    matriz[ k ][ i ] = prioridad;
                    break;
            
                // LLenar el resto de la tabla con ceros
                default:
                    matriz[ k ][ i ] = 0;
                    break;
            }
        }
    }

    cout << "\t Primer tabla de datos " << endl;
    // Mostrar como quedo la matriz
    imprimirMatriz( noProcesos );
}


// Opcion 2: Leer valores de un archivo externo txt
void leerArchivo( )
{
    system( "cls" );

    cout << " Intrucciones para el archivo txt: " << endl;
    cout << " 1. El archivo debe estar en la misma carpeta que el programa. " << endl;
    cout << " 2. El archivo debe llamarse 'archivo.txt'" << endl;
    cout << " 3. El primer linea y primer numero define la cantidad de procesos. " << endl;
    cout << " 4. Los valores deben estar separados por espacios. " << endl << endl;

    cout << " Ejemplo: archivo.txt" << endl;
    cout << " 10 (numero de procesos)" << endl;
    cout << " (Llegada) (Tiempo en procesador) (Prioridad) " << endl;
    cout << " 0 2 3" << endl << " 1 4 2" << endl << " 2 2 1" << endl;

    cout << endl << endl << " Continuar... " << endl;
    system( "pause" );

    string nombreArchivo = "archivo.txt";
    ifstream archivo( nombreArchivo.c_str( ) );

    string linea = "" , llegada = "" , tiempo = "" , prioridad = "";
    int noProcesos = 0;
    bool espacio1 = true , espacio2 = true;

    for ( int k = -1; getline( archivo , linea ); k++ )
    {

        if( linea == "" )
        {
            k--;
            continue;
        }

        if( k == -1 ) noProcesos = stoi( linea );
        else
        {
            for (int i = 0; i < 9; i++)
            {
                llegada = ""; tiempo = ""; prioridad = "";
                espacio1 = true; espacio2 = true;

                for (int m = 0; m < linea.length( ); m++)
                {
                    if ( espacio1 && espacio2 ) llegada += linea[ m ];
                    else if ( espacio2 ) tiempo += linea[ m ];
                    else prioridad += linea[ m ];
                    
                    if ( linea[ m ] == ' ' && espacio1 ) espacio1 = false;
                    else if ( linea[ m ] == ' ' && espacio2 ) espacio2 = false;
                }

                switch ( i )
                {
                    case 0: matriz[ k ][ i ] = ( k + 1 );           break;
                    case 1: matriz[ k ][ i ] = stoi( llegada );     break;
                    case 2: matriz[ k ][ i ] = stoi( tiempo );      break;
                    case 3: matriz[ k ][ i ] = stoi( prioridad );   break;
                    default: matriz[ k ][ i ] = 0;                  break;
                }
            }
        }
    }

    system( "cls" );
    cout << "\t Reemplazo de página FIFO " << endl << endl;
    imprimirMatriz( noProcesos );

}


// Opcion 3. Valores aleatorios
void aleatorios( )
{

    // Limpiar consola
    system( "cls" );

    // Necesario para numeros aleatorios
    srand(time(NULL));

    // Cantidad de procesos que se tendran
    int noProcesos = 0;
    do
    {
        cout << " Cantitdad de procesos: "; cin >> noProcesos;
    } while ( noProcesos <= 0 || noProcesos >= 101);
    
    // Separador
    cout << endl;

    // Variable para seleccionar una opcion
    int seleccion = 0;

    // Variables que se ocupan y se piden al usuario
    int maxLlegada = 0 , maxTiempo = 0 , maxPrioridad = 0;

    do
    {
        // Menu para limites
        cout << "\t Opciones " << endl;
        cout << " 1. Definir limites manualmente. " << endl;
        cout << " 2. Limites por defecto (Llegada: 0-20, Tiempo: 1-10, Prioridad: 0-5) " << endl;

        // Lectura de seleccion
        cout << endl << endl << " Seleccion: "; cin >> seleccion;

    // Validacion de seleccion
    } while ( seleccion != 1 && seleccion != 2 );

    switch ( seleccion )
    {
        case 1:

            // Lectura de limites de llegada
            do
            {
                system( "cls" );
                cout << " Llegada " << endl;
                cout << " Introduce el valor maximo: "; cin >> maxLlegada;
            } while ( maxLlegada < 0 || maxLlegada >= 21 );


            // Lectura de limites de tiempo
            do
            {
                system( "cls" );
                cout << " Tiempo " << endl;
                cout << " Introduce el valor maximo: "; cin >> maxTiempo;
            } while ( maxTiempo < 1 || maxTiempo >= 11 );


            // Lectura de limites de prioridad
            do
            {
                system( "cls" );
                cout << " Prioridad " << endl;
                cout << " Introduce el valor maximo: "; cin >> maxPrioridad;
            } while ( maxPrioridad < 0 || maxPrioridad >= 6 );

            break;

        case 2:
            
            // minLlegada = rand() % 21;
            maxLlegada = 20;
            maxTiempo = 10;
            maxPrioridad = 5;
            break;
    
        default: break;
    }

    system( "cls" );
    cout << "\t Valores definidos " << endl;
    cout << " Llegada: 0-" << maxLlegada << endl;
    cout << " Tiempo: 1-" << maxTiempo << endl;
    cout << " Prioridad: 0-" << maxPrioridad << endl;

    for ( int i = 0; i < noProcesos; i++)
    {
        for ( int k = 0; k < 9; k++)
        {
            switch ( k )
            {
                // Numero de proceso
                case 0: matriz[ i ][ k ] = i; break;

                // Generar llegada
                case 1: matriz[ i ][ k ] = rand( ) % ( maxLlegada + 1 ); break;

                // Generar tiempo
                case 2: matriz[ i ][ k ] = rand( ) % ( maxTiempo + 1 ); break;

                // Generar prioridad
                case 3: matriz[ i ][ k ] = rand( ) % ( maxPrioridad + 1 ); break;
            
                // Llenar con 0 las demas columnas
                default: matriz[ i ][ k ] = 0; break;
            }
        }
    }

    // Limpiar consola
    system( "cls" );

    cout << "\t Tabla con valores aleatorios " << endl;
    imprimirMatriz( noProcesos );

    // Separador
    cout << endl;
}




