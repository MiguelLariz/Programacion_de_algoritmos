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
void valoresManual( );
void leerArchivo( );


int main()
{
	system("cls"); // Limpiar consola
	system("title Reemplazo FIFO"); // Cambiar titulo ventana
	setlocale(LC_ALL, ""); // Aceptar acentos

    // Variables
    int opcion = 0;

    do
    {
        system( "cls" );

        cout << "\n Reemplazo FIFO " << endl;

        cout << " Menu " << endl;

        cout << " 1. Llenar los valores manualmente. " << endl;
        cout << " 2. Leerlos de un archivo txt." << endl;
        cout << " 3. Aleatorios." << endl << endl;

    cout << " Opcion: "; cin >> opcion;

    } while ( opcion != 1 && opcion != 2 && opcion != 3 );
    
    
    switch ( opcion )
    {
        case 1: break;

        case 2:
            leerArchivo( );
            break;

        case 3: break;
        
    default:
        break;
    }

	return 0;	
}


// Vaciar la matriz por si exisitiera valores basura
void vaciarMatriz( int k )
{
    for ( int m = 0; m < k; m++ )
    {
        for ( int f = 0; f < k; f++ )
        {
            matriz[ m ][ f ] = -1;
        }
    }
}


void valoresManual( )
{
    int noProcesos = 0;
    // Pedir cantidad de procesos
	cout << "Introduce la cantidad de procesos: "; cin >> noProcesos; 

    // Vaciado de los espacios que necesitamos
    vaciarMatriz( noProcesos );

    for ( int k = 0; k < noProcesos; k++ )
    {
        
    }
}


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

    string nombreArchivo = "archivo.txt";
    ifstream archivo( nombreArchivo.c_str( ) );

    string linea = "" , llegada = "" , tiempo = "" , prioridad = "";
    int tamanioMatriz = 0;
    bool espacio1 = true , espacio2 = true;

    for ( int k = 0; getline( archivo , linea ); k++ )
    {

        if( linea == "" )
        {
            k--;
            continue;
        }

        if( k == 0 ) tamanioMatriz = stoi( linea );
        else
        {
            llegada = ""; tiempo = ""; prioridad = "";
            espacio1 = true; espacio2 = true;

            for (int m = 0; m < linea.length( ); m++)
            {
                if ( espacio1 && espacio2 ) llegada += linea[ m ];
                else if ( espacio2 ) tiempo += linea[ m ];
                else y += linea[ m ];
                
                if ( linea[ m ] == ' ' && espacio1 ) espacio1 = false;
                else if ( linea[ m ] == ' ' && espacio2 ) espacio2 = false;
            }

            // cout << " x: " << x << endl;
            // cout << " y: " << y << endl;

            matriz[ stoi( x ) ][ stoi( y ) ] = k;
        }

        // cout << linea << endl;

    }
    
    

}
