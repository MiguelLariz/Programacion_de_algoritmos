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
#include <windows.h>
using namespace std;


// Variables globales
int matriz[ 1000 ][ 1000 ];
int matrizClon[ 1000 ][ 1000 ];
int noProcesos = 0;


// Funciones para ingresar valores
void vaciarMatriz( int );
void imprimirMatriz( int );
void clonarMatriz( int ); 
void imprimirMatrizClon( int );
void calculosTabla( );

// Lectura de valores
void valoresManual( );
void leerArchivo( );
void aleatorios( );

// Metodo FIFO
void fifo( );
void mostrarResultadosFIFO( );

// Metodo EnseguidaMasCorto
void EnseguidaMasCorto( );
void mostrarResultadosSPN( int [] );


int main()
{
	system("cls"); // Limpiar consola
	system("title Programacion de Algoritmos - FIFO y EnseguidaMasCorto"); // Cambiar titulo ventana
	setlocale(LC_ALL, ""); // Aceptar acentos

    // Variables
    int opcion = 0 , metodo = 0;

    do
    {
        // Limpiar consola cada que se entra
        system( "cls" );

        // Seleccionar metodo
        do
        {
            cout << "\t Metodos disponibles " << endl;

            cout << endl;
            cout << " 1. FIFO " << endl;
            cout << " 2. Enseguida el mas corto " << endl;

            cout << "¿Que metodo se va a usar?"; cin >> metodo;

        } while ( metodo != 1 && metodo != 2 );


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

    switch ( metodo )
    {
        case 1: fifo( ); break;
        case 2: EnseguidaMasCorto( ); break;;
        default:break;
    }
    

    // Detener ejecucion
    cout << endl << endl;
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

    // Separador
    cout << endl << endl;

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


// Clonar matriz para no perder los datos originales
void clonarMatriz( int limite )
{
    for ( int i = 0; i < limite; i++ )
    {
        for ( int k = 0; k < 9; k++ ) matrizClon[ i ][ k ] = matriz[ i ][ k ];
    }
}


// Imprimir los valores de la matriz clon 
void imprimirMatrizClon( int limite )
{
    cout << "Matriz clon" << endl;
    // Encabezados de la tabla
    cout << "Proce\tLlega\ttiempo\tPriori\tInicio\t Fin\tTiemTot\tEspera\tTiemPro" << endl;

    // Recorrer tabla la cantidad de procesos
    for ( int i = 0; i < limite; i++ )
    {

        // Imprimir cada renglon de la tabla
        for ( int k = 0; k < 9; k++ )
        {

            // Imprimir por temas de estetica
            if( matrizClon[ i ][ k ] < 10 ) cout << "  " << matrizClon[ i ][ k ] << "\t";
            else if( matrizClon[ i ][ k ] < 100 && matrizClon[ i ][ k ] >= 10 ) cout << " " << matrizClon[ i ][ k ] << "\t";
            else cout << matrizClon[ i ][ k ] << "\t";
        }
        // Separar cada renglon
        cout << endl;
    }
}


// Llenar los campos que faltan de la tabla
void calculosTabla( )
{
    // Variables para llenar la tabla
    int inicio = matriz[ 0 ][ 1 ] , fin = matriz[ 0 ][ 2 ];

    for ( int k = 0; k < noProcesos; k++ )
    {
        // Calcular el inicio
        matriz[ k ][ 4 ] = inicio;
        if ( ( k + 1 ) < noProcesos ) inicio += matriz[ k ][ 2 ];

        // Calcular el fin
        matriz[ k ][ 5 ] = fin;
        if ( (k + 1) < noProcesos ) fin += matriz[ ( k + 1 ) ][ 2 ];

        // Calcular tiempo en procesador
        matriz[ k ][ 6 ] = matriz[ k ][ 5 ] - matriz[ k ][ 1 ];

        // Calcular tiempo de espera
        matriz[ k ][ 7 ] = matriz[ k ][ 6 ] - matriz[ k ][ 2 ];

        // Calcular tiempo promedio
        matriz[ k ][ 8 ] = matriz[ k ][ 6 ] / matriz[ k ][ 2 ];
    }
}


// Opcion 1. Introducir los valores manualmente
void valoresManual( )
{

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


// Funcion FIFO
void fifo( )
{

    // limpiar consola
    system( "cls" );
    // Titulo del programa
    cout << " Reemplazo de paginas FIFO " << endl;

    // Explicacion de como se selecciona
    cout << " Metodo de seleccion: Llegada -> Prioridad -> Mas corto " << endl;

    // Vector para indicar cual sigue
    int posiciones[ noProcesos ];

    // Vaciado del vector
    for ( int i = 0; i < noProcesos; i++ ) posiciones[ i ] = 0;

    clonarMatriz( noProcesos );

    int sigProceso = 0 , sigLlegada = 1000 , sigTiempo = 0 , sigPrioridad = 0;

    for ( int k = 0; k < noProcesos; k++)
    {
        sigLlegada = 1000;
        for ( int m = 0; m < noProcesos; m++ )
        {
            if ( matrizClon[ m ][ 1 ] < sigLlegada )
            {
                sigProceso = m;
                sigLlegada = matrizClon[ m ][ 1 ];
                sigTiempo = matrizClon[ m ][ 2 ];
                sigPrioridad = matrizClon[ m ][ 3 ];
            }
            else if( matrizClon[ m ][ 1 ] == sigLlegada )
            {
                if ( matrizClon[ m ][ 3 ] < sigPrioridad )
                {
                    sigProceso = m;
                    sigLlegada = matrizClon[ m ][ 1 ];
                    sigTiempo = matrizClon[ m ][ 2 ];
                    sigPrioridad = matrizClon[ m ][ 3 ];
                }
                else if( matrizClon[ m ][ 3 ] == sigPrioridad )
                {
                    if ( matrizClon[ m ][ 2 ] < sigTiempo )
                    {
                        sigProceso = m;
                        sigLlegada = matrizClon[ m ][ 1 ];
                        sigTiempo = matrizClon[ m ][ 2 ];
                        sigPrioridad = matrizClon[ m ][ 3 ];
                    }
                }
            }
        }

        matrizClon[ sigProceso ][ 1 ] = 10000;
        posiciones[ k ] = sigProceso;
    }

    // Imprimir orden de procesos
    // for ( int x = 0; x < noProcesos; x++ ) cout << ( posiciones[ x ] + 1 ) << " ";


    // Volver a los valores originales
    clonarMatriz( noProcesos );


    // Acomodar procesos
    for ( int i = 0; i < noProcesos; i++ )
    {
        for ( int k = 0; k < 9; k++ ) matriz[ i ][ k ] = matrizClon[ posiciones[ i ] ][ k ];
    }

    // Llenar valores que faltan de la tabla
    calculosTabla( );

    // Mostrar la tabla final
    imprimirMatriz( noProcesos );

    // Mostrar los valos visualmente (graficados)
    mostrarResultados( );

}


// Se muestran los resultados visualmente como en excel
void mostrarResultados( )
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int inicio = 0 , fin = 0;
    bool espera = false;

    for ( int i = 0; i < noProcesos; i++ )
    {

        cout << i << "   ";

        // Espacios de separación, cuando un proceso ocupo
        // el procesador y otro estuvo esperando
        for ( int k = 0; k < matriz[ i ][ 4 ]; k++)
        {
            // La "o" hace referencia la tiempo de espera
            if ( k >= matriz[ i ][ 1 ] )  SetConsoleTextAttribute( hConsole, 7 ) , cout << "o";
            else cout << " ";
            
        }

        
        // tiempo en procesador
        for ( int m = matriz[ i ][ 4 ]; m < matriz[ i ][ 5 ]; m++ )
        {

            // Los colores se cuentan desde el 1
            if ( i != 6 ) SetConsoleTextAttribute( hConsole , ( i + 1 ) ); 
            
            // El color numero 7 es blanco y no se toma en cuenta
            else if ( i >= 6 && i <= 11 ) SetConsoleTextAttribute( hConsole , ( i + 3 ) );

            // Se reinician los colores
            else SetConsoleTextAttribute( hConsole, i - 11 );

            // la "x" hace referencia a cuando el proceso dentro
            // en el procesador
            cout << "x";
        }

    // Regresar todo al color blanco
    SetConsoleTextAttribute( hConsole, 7 );
        cout << endl;
    }
}


// Metodo de Enseguida el Mas Corto
void EnseguidaMasCorto( )
{

    // limpiar consola
    system( "cls" );
    // Titulo del programa
    cout << " Enseguida el Mas Corto " << endl;

    // Explicacion de como se selecciona
    cout << " Metodo de seleccion: Mas corto -> Prioridad -> Llegada" << endl;

    // Guarfar los valores de la matriz original en una matriz bandera
    clonarMatriz( noProcesos );

    // Vector para guardar y comparar los procesos que ya hayan llegado
    int posiciones[ noProcesos ];

    // Vector que guardara los valores de los procesos que este en espera
    int posicionProcesos[ noProcesos ];
    int llegadaProcesos[ noProcesos ];
    int tiempoProcesos[ noProcesos ];
    int prioridadProcesos[ noProcesos ];

    // Variables para guardar los valores del proceso que sigue
    int posicionMenor = 0 , llegadaMenor = 0 , tiempoMenor = 1000 , prioridadMenor = 0;

    // Vaciar los vectores para que no guarden valores basura
    for ( int k = 0; k < noProcesos; k++ )
    {
        posiciones[ k ] = -1;
        posicionProcesos[ k ] = -1;
        llegadaProcesos[ k ] = -1;
        tiempoProcesos[ k ] = -1;
        prioridadProcesos[ k ] = -1;
    }

    // Variable para el tiempo total que se ocupara el procesador
    int totalTiempo = 0;

    // Hacer la suma de todos los tiempos que se toman los procesos
    for ( int k = 0; k < noProcesos; k++ ) totalTiempo += matriz[ k ][ 2 ]; 

    // Variables para guardar posiciones y cantidad de vueltas para los ciclos
    int indice = 0 , marcar = 0 , vueltas = 0 , hecho = 0;

    for ( int i = 0; i <= totalTiempo; i++ )
    {

        // Reinicio de variables que se ocupan
        vueltas = 0;
        indice = 0;

        // Recorrer todos los procesos
        for ( int k = 0; k < noProcesos; k++ )
        {

            // Ponerlos en espera para saber cual va a pasar
            if ( matrizClon[ k ][ 1 ] <= i )
            {
                posicionProcesos[ indice ] = matrizClon[ k ][ 0 ];
                llegadaProcesos[ indice ] = matrizClon[ k ][ 1 ];
                tiempoProcesos[ indice ] = matrizClon[ k ][ 2 ];
                prioridadProcesos[ indice ] = matrizClon[ k ][ 3 ];
                indice++;
                vueltas++;
            }
        }

        // Encontrar el menor tiempo de los procesos en espera
        tiempoMenor = 100;
        marcar = 0;

        // El ciclo gira la cantidad de procesos que esta en espera
        // para encontrar al mas pequeño de los formados
        for ( int e = 0; e < vueltas; e++ )
        {

            // Buscar el de menor tiempo que este formado
            for ( int m = 0; m < indice; m++ )
            {
                // Comparar el menor tiempo guardado con el del
                // proceso anterior
                if ( tiempoProcesos[ m ] < tiempoMenor )
                {
                    posicionMenor = posicionProcesos[ m ];
                    llegadaMenor = llegadaProcesos[ m ];
                    tiempoMenor = tiempoProcesos[ m ];
                    prioridadMenor = prioridadProcesos[ m ];
                    marcar = m;
                }

                // Si son iguales los tiempos comparar la menor 
                // prioridad de ambos proceso
                else if ( tiempoProcesos[ m ] == tiempoMenor )
                {

                    // Comparar la menor prioridad de ambos procesos
                    if ( prioridadProcesos[ m ] < prioridadMenor )
                    {
                        posicionMenor = posicionProcesos[ m ];
                        llegadaMenor = llegadaProcesos[ m ];
                        tiempoMenor = tiempoProcesos[ m ];
                        prioridadMenor = prioridadProcesos[ m ];
                        marcar = m;
                    }

                    // Si son iguales las prioridades se compara con el
                    // que haya llegado antes
                    else if ( prioridadProcesos[ m ] == prioridadMenor )
                    {

                        // Guardar el proceso que haya llegado antes
                        if ( llegadaProcesos[ m ] < llegadaMenor )
                        {
                            posicionMenor = posicionProcesos[ m ];
                            llegadaMenor = llegadaProcesos[ m ];
                            tiempoMenor = tiempoProcesos[ m ];
                            prioridadMenor = prioridadProcesos[ m ];
                            marcar = m;
                        }

                        // Si llegaron al mismo tiempo, tienen el mismo
                        // tiempo y la misma prioridad, se guarda
                        // cualquiera de los dos
                        else
                        {
                            posicionMenor = posicionProcesos[ m ];
                            llegadaMenor = llegadaProcesos[ m ];
                            tiempoMenor = tiempoProcesos[ m ];
                            prioridadMenor = prioridadProcesos[ m ];
                            marcar = m;
                        }
                    }
                }
            }
        }

        // Se suma el tiempo del menor proceso para despues validar 
        // los procesos que hayan llegado en ese momento o antes
        i += ( tiempoMenor - 1 );

        // Guardar el proceso con menor tiempo
        posiciones[ hecho ] = posicionMenor;
        hecho++;

        // Cambiar los valores por valores grandes para que ya no
        // sean tomados en cuenta y siga con los siguientes procesos
        matrizClon[ posicionMenor - 1 ][ 0 ] = 100000;
        matrizClon[ posicionMenor - 1 ][ 1 ] = 100000;
        matrizClon[ posicionMenor - 1 ][ 2 ] = 100000;
        matrizClon[ posicionMenor - 1 ][ 3 ] = 100000;

    }

    // Imprimir orden de procesos
    // cout << "Posiciones " << endl;
    // for ( int x = 0; x < noProcesos; x++ ) if ( posiciones[ x] != -1 ) cout << posiciones[ x ] << " ";
    // cout << endl << endl;
    // system( "pause" );

    // Volver a los valores originales porque se había cambiado
    // la menor llegada por 1000
    clonarMatriz( noProcesos );

    for ( int k = 0; k < noProcesos; k++ )
    {
        for ( int m = 0; m < 9; m++ ) matriz[ k ][ m ] = matrizClon[ posiciones[ k ] - 1 ][ m ];
    }

    // Mostrar la tabla original sin llenar
    // imprimirMatriz( noProcesos );


    // Llenar la tabla con los valores que le faltan
    calculosTabla( );

    // Clonar los valores de toda la tabla en la matrizClon
    clonarMatriz( noProcesos );

    int menor = 1000 , lugar = 0;
    for ( int i = 0; i < noProcesos; i++ )
    {
        menor = 1000;
        for ( int k = 0; k < noProcesos; k++ )
        {
            if ( matrizClon[ k ][ 0 ] < menor )
            {
                menor = matrizClon[ k ][ 0 ];
                lugar = k;
            }
        }

        for ( int m = 0; m < 9; m++ ) matriz[ i ][ m ] = matrizClon[ lugar ][ m ];

        matrizClon[ lugar ][ 0 ] = 1000;
    }

    // Mostrar la tabla final
    imprimirMatriz( noProcesos );
    
    // Mostrar los resultados finales graficados
    mostrarResultados( );
}


