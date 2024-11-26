/*
Cesar Augusto Ramirez Davila
A01712439
04/09/2024

Nueva fecha de correccion: 23/11/2024


*/
#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <vector> // Se incluye la librería vector para trabajar con vectores

using namespace std;

template <class T> // Definimos la clase plantilla (template) que permitirá trabajar con cualquier tipo de dato
class Sorts
{
public:
    // Métodos públicos de la clase Sorts:
    void ordenaSeleccion(vector<T> &);              // selection sort
    void ordenaBurbuja(vector<T> &);                // bubble sort
    void ordenaMerge(vector<T> &);                  // merge sort
    int busqSecuencial(const vector<T> &, T) const; //
    int busqBinaria(const vector<T> &, T) const;    // binary search

private:
    // Métodos privados que se utilizan en ordenaMerge:
    void mergeSplit(vector<T> &, vector<T> &, int left, int right);             // Divide el vector para el merge sort
    void mergeArray(vector<T> &, vector<T> &, int left, int middle, int right); // Combina subarrays ordenados en merge sort
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &arr)
{
    int tamanio = arr.size();               // tamanio del arreglo
    for (int i = 0; i < (tamanio - 1); i++) // creacion de un indice que abarca desde el primer hasta el penultimo elemento
    {
        int min_pos = i;                      // se asume que el elemento mas pequeño es el indice en el que nos encontramos
        for (int j = i + 1; j < tamanio; j++) // el indice j avanza desde i + 1 ya que el indice i ya esta ordenado y solo se centra en la parte no ordenada del array
        {
            if (arr[j] < arr[min_pos]) // si el elemento del indice j resulta ser menor que el valor minimo supuesto
            {
                min_pos = j; // se le asigna el valor del indice j
            }
        }
        T aux; // se declara una variable auxiliar para hacer el intercambio de valores
        ///////////////////
        aux = arr[i];          // la variable auxiliar toma el valor del array en el indice i
        arr[i] = arr[min_pos]; // el valor del array en i toma el nuevo valor minimo que es el de j
        arr[min_pos] = aux;    // y ahora el valor minimo anterior toma el valor guardado en la variable auxiliar
    }

    /*
    NOTAS SELECTION SORT
    esta muy bien explicado en las anotaciones del codigo
    no hace falta un resumen
    bastante parecido al bubble sort en complejidad
    a lo mejor un nivelito mas parriba
    */
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &arr)
{
    int tamanio = arr.size(); // tamaño del vector

    for (int i = 0; i < tamanio - 1; i++) // ciclo for que inicia en cero y continua hasta que i alcance el tamanio del arreglo, i++
    {
        for (int j = 0; j < tamanio - i - 1; j++) /*segundo buble que va desde cero hasta que j
                                                sea del tamanio del arreglo menos i para evitar
                                                comparar los datos que ya estan ordenados y menos uno para que no se salga del arreglo, j++*/
        {
            if (arr[j] > arr[j + 1]) // si elemento de la izquierda es manor que el de la derecha
            {
                T aux; // variable auxiliar para intercambio de valores
                /////////////////////////////
                aux = arr[j];        // se sobrescribe el valor auxiliar con el valor del de la izquierda
                arr[j] = arr[j + 1]; // el de la izauierda de sobreescribe con el de la derecha
                arr[j + 1] = aux;    // el de la derecha se le asigna el valor  de la auxiliar
            }
        }
    }
}
/*
NOTAS BUBBLE SORT

No tiene ciencia compara usando dos indices que recorren el arreglo
si el de la derecha/siguiente es menor que el de la izquierda/anterior
entonces se hace un intercambio de valores mediante una variable auxiliar
y ya esta
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// funcion que hace todo el merge sort
template <class T>
void Sorts<T>::ordenaMerge(vector<T> &arr)
{
    vector<T> aux(arr.size());               // creacion de vector auxiliar del mismo tamanio que el orignal
    mergeSplit(arr, aux, 0, arr.size() - 1); // llamada recursiva al metodo que divide y ordena
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// metodo recursivo que divide el vector en mitades a partir de un punto medio
template <class T>
void Sorts<T>::mergeSplit(vector<T> &arr, vector<T> &aux, int left, int right)
{
    if (left >= right) // si esta vacio o solo tiene un elemento no se hace nada
    {
        return;
    }

    int middle = left + (right - left) / 2;    // punto medio
    mergeSplit(arr, aux, left, middle);        // mitad izquierda del vector
    mergeSplit(arr, aux, middle + 1, right);   // mitad derecha del vector
    mergeArray(arr, aux, left, middle, right); // combinar dos mitades ordenadas
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fusionar las dos mitades ordenadas
template <class T>
void Sorts<T>::mergeArray(std::vector<T> &arr, std::vector<T> &aux, int left, int middle, int right)
{
    for (int x = left; x <= right; x++) // for que copia el rango actual del vector original al auxliar/ temporal
    {
        aux[x] = arr[x];
    }
    // inicializacion de los 3 indices que van ordenando la mitad izquierda, derecha y el vector original
    int i = left;       // indice de la mitad izquierda
    int j = middle + 1; // indice de la mitad derecha
    int k = left;       // indice del vector orignal

    while (i <= middle && j <= right) // ciclo while que indica que mientras cada indice no sobre pase sus porciones correspondientes seguira ocurriendo
    {
        if (aux[i] <= aux[j]) // si el elemento de la izquierda es menor que el de la derecha se coloca primer oel de la izquierda
        {
            arr[k++] = aux[i++]; // el indice k avanza para poder pegar en el siguiente lugar del array y el indice i avanza para evaluar el siguiente y no se copien repetidos en i
        }
        else // caso contrario el elemento de la derecha es menor
        {
            arr[k++] = aux[j++]; // se coloca entonces primero y avanzan los indices para no pegar valores duplicados en j y para no pegar todo en el mismo indice en k
        }
    }
    while (i <= middle) // si aun quedan elementos en la mitad izquierda
    {
        arr[k++] = aux[i++]; // se pegan al vector original y como los elementos de la derecha ya estan en su lugar no se hace nada mas
    }
    /*
    NOTAS MERGE SORT
    este si esta bien perro augusto entonces por si acaso mejor aqui te dejo notitas el dia que lo vuelvas a ocupar

    Asi a grandes rasgos lo que hace es que divide el arreglo en mitades cada vez mas pequenias
    y al final las acomoda y vuelve a unir estas mitades pero ya arregladas
    en este caso lo hice de forma recursiva, no se si se pueda hacer de otro modo pero por el momento
    esta jalo y pues ya mejor ni le muevas, se que lo que se te complica mas de las 3 mitades de entender es
    la funcion que ordena las mitades entonces pues basicamente esta funciona con un vector temporal y con 3 indices (i,j y k)
    los cuales representan el indice que va desde;
    i = mitad izquierda
    j = mitad derecha
    k = arreglo completo del orignal

    con un ciclo for voy pegando estos valores a uno temporal y al final se los paso al orignal
    ahora con un ciclo while lo que hiciste fue definir limites para cada indice de las mitades (i y j)
    donde pones que el ciclo se ejecuta hasta que estas no lleguen a su tamanio en este caso que la mitad izquierda no pase
    la mitad del arreglo y que la derecha no pase el indice derecho final luego mientras esto se cumpla
    se evalua si el vector auxiliar que tiene los datos se va pasando por las dos mitades con los indices i y j si el de la
    izquierda osea el indice i es menor que el del indice j de la mitad derecha entonces ese valor se pasa al arreglo orignal
    y ambos indices crecen para poder pegar en el siguiente espacio y no haya datos repetidos por parte de i y que no se este
    pegando todo en el mismo lugar por parte de j
    de caso contrario pues lo mismo pero en lugar de i es j.

    te pongo un ejemplo mas visual de como funciona esto
    por ejemplo tenemos un arreglo auxiliar y uno original
1.

            i         j
    aux[] ={0, 3, 5 , 6 , 7 , 8}

    arr[] = {0}
    i solo llega hasta el 5 que es su limite en el while y j hasta el 8, van avanzando mientras se van comparando, si i es menor que j entonces el valor de i
    se pega en el arreglo original e i pasa el siguiente elemento

2.
                i           j
    aux[] ={0,  7,  5 , 6 , 3 , 8}
    de nuevo se vuelve a hacer la comparacion y asi sucesivamente
    arr[] ={0, 3}

    IMPORTANTE
    si el que resulto mayor no es el que se imprime ese indice no avanza al siguiente por ejemplo i
    no se mueve de 7 hasta que se comprare con el siguiente de j para evitar saltarte datos en el arreglo
    */
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &arr, T element) const
{
    int tamanio = arr.size();         // tamanio del vector
    for (int i = 0; i < tamanio; i++) // se crea un indice i que va desde 0 hasta el tamanio -1, i aumenta en cada iteracion
    {
        if (arr[i] == element) // si el elemento en el indice i es el que se busca
        {
            return i;
        }
    }
    return -1; // caso contrario se retorna temp con valor de -1 indicando que no se encontro el elemento
}
/*
NOTAS LINEAR SEARCH
si no sabes hacer este ya mejor date de baja papi
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &arr, T element) const
{
    int left = 0;               // indice de busqueda izquierda
    int right = arr.size() - 1; // indice de busqueda derecha
    while (left <= right)       // mientras que el indice de la izquierda no sobrepase el de la derecha
    {
        int mid = left + (right - left) / 2; // punto medio
        if (arr[mid] == element)             // si el valor del indice del punto medio es igual al valor que estamos buscando
        {
            return mid; // retorna el valor del punto medio
        }
        if (arr[mid] > element)
        {
            right = mid - 1;
        }
        if (arr[mid] < element)
        {
            left = mid + 1;
        }
    }
    return -1; // si pasa significa que no encontro el elemento y retorna -1
    /*
    NOTAS BINARY SEARCH

    Este metodo lo que hace es que busca el indice de algun elemento especifico
    en un arreglo, para ello utilizamos un metodo mas inteligente que ir de
    izquierda a derecha, busca desde el elemento del medio, si el elemento es mayor
    busca en la fraccion del array que va despues de este o caso contrario si es menor
    asi se ahorra tiempo en buscar el indice de algun elemento en especifico
    */
}

#endif /* SORTS_H_ */