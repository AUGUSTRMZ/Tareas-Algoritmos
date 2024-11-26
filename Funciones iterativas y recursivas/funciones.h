#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <string>
using namespace std;

/*
A01712439
Cesar Augusto Ramirez Davila
20/08/2024
*/

class Funciones // clase funciones
{
public: // funciones de la clase
    int sumaIterativa(int);
    int sumaRecursiva(int);
    int sumaDirecta(int);
};

// Implementacion de las funciones previamente definidas

// Suma Iterativa
int Funciones::sumaIterativa(int n) // se establece n como parametro
{
    int contador = 0;            // inicio un contador en cero
    for (int i = 1; i <= n; ++i) // ciclo for con un valor de i inicial en 1, este se detiene hasta que i sea igual a n
    {
        contador += i; // cada que se se repita el ciclo, se añade el valor de i al contador
    }
    return contador; // la funcion retorna el contador con la suma total.
}

// Suma Recursiva
int Funciones::sumaRecursiva(int n) // se establece n como parametro
{
    return (n == 0) ? 0 : n + sumaRecursiva(n - 1);
    /*
    Si n no vale 0, devuelve 0 (el caso base).
    En caso de que no valga 0, regresa el valor de n + la recursion de n -1
    */
}

// Suma Directa
int Funciones::sumaDirecta(int n) // se establece n como parametro
{
    return n * (n + 1) / 2; // formula directa para calcular los primeros 'n' numeros
    // la formula suma los numeros en pares en donde de manera susesiva los pares suman n+1
    // al final se divide entre 2 ya que  cada numero se cuenta dos veces en la formacion de los pares
}
#endif
