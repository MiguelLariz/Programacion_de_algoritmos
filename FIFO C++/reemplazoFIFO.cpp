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

    system( "pause" );

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

void imprimirMatriz( int limite )
{

    cout << "Proce\tLlega\ttiempo\tPriori\tInicio\t Fin\tTiemTot\tEspera\tTiemPro" << endl;
    for ( int i = 0; i < limite; i++ )
    {
        for ( int k = 0; k < 9; k++ )
        {
            if( matriz[ i ][ k ] < 10 ) cout << "  " << matriz[ i ][ k ] << "\t";
            else if( matriz[ i ][ k ] < 100 && matriz[ i ][ k ] >= 10 ) cout << " " << matriz[ i ][ k ] << "\t";
            else cout << matriz[ i ][ k ] << "\t";
        }

        cout << endl;
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
    int tamanioMatriz = 0;
    bool espacio1 = true , espacio2 = true;

    for ( int k = -1; getline( archivo , linea ); k++ )
    {

        if( linea == "" )
        {
            k--;
            continue;
        }

        if( k == -1 ) tamanioMatriz = stoi( linea );
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
    imprimirMatriz( tamanioMatriz );

}
