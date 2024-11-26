/*
Cesar Augusto Ramirez Davila
A01712439
*/

#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

template <class T>
class DList
{
private:
  // Estructura que representa un nodo de la lista doblemente enlazada.
  struct Link
  {
    T value;    // Valor almacenado en el nodo.
    Link *next; // Puntero al siguiente nodo.
    Link *prev; // Puntero al nodo anterior.
    Link(const T &val, Link *nxt = nullptr, Link *prv = nullptr)
        : value(val), next(nxt), prev(prv) {} // Constructor del nodo.
  };

  Link *head; // Puntero al primer nodo de la lista.
  Link *tail; // Puntero al último nodo de la lista.

public:
  DList() : head(nullptr), tail(nullptr) {} // Constructor: inicializa la lista vacía.
  ~DList()
  {
    while (head != nullptr) // mientras aun haya nodos en la lista
    {
      Link *temp = head; // guardamos el puntero al nodo actual
      head = head->next; // avanzo al siguiente nodo
      delete temp;       // liberar la memoria del nodo actual
    }

  } // Destructor: libera la memoria de los nodos.

  // Inserta un nuevo elemento al final de la lista
  void insertion(const T &value)
  {
    Link *newNode = new Link(value); // nuevo nodo con el valor dado
    if (tail == nullptr)             // si la lista esta vacia
    {
      head = newNode; // nuevo nodo se vuelve la cabeza
      tail = newNode; // nuevo nodo de vuelve la cola tambien
    }
    else // caso contrario la lista no esta vacia
    {
      tail->next = newNode; // conecto el ultimo nodo con el nuevo nodo
      newNode->prev = tail; // el nuevo nodo apunta hacia atras el nodo actual de la cola
      tail = newNode;       // Actualizamos la cola para que sea el nuevo nodo
    }
  }

  // Busca un valor en la lista y devuelve su índice
  int search(const T &value) const
  {
    Link *current = head;      // comenzamos en la cabeza de la lista
    int index = 0;             // creacion de un indice
    while (current != nullptr) // mientras el nodo actual no sea el ultimo de la lista
    {
      if (current->value == value) // si el valor que esta en el nodo actual es el valor que se busca
      {
        return index; // retorna el indice
      }
      // si no lo es
      current = current->next; // avanzamos al siguiente nodo
      ++index;                 // el indice incrementa
    }
    return -1; // si el valor no se encuentra se retorna el valor especial -1
  }

  // Actualiza el valor de un nodo en el índice dado
  void update(int index, const T &value)
  {
    if (index < 0) // si el indice es menor que cero
    {
      throw out_of_range("Indice no valido"); // da mensaje de error
    }
    Link *current = head; // comenzamos en la cabeza
    int actIndex = 0;     // indice actual inicializado en cero

    while (current != nullptr) // mientras el nodo actual no sea el ultimo de la lista
    {
      if (actIndex == index) // si el indice actual es igual al indice que se busca
      {
        current->value = value; // actualiza el valor del nodo en ese indice
        return;
      }
      // si no el nodo actual no esta en el indice que se busca
      current = current->next; // avanzamos al siguiente nodo
      ++actIndex;              // el indice aumenta
    }
    throw out_of_range("Indice fuera del rango"); // si se llega al final de la lista y no se encuentra el indice mostrar mensaje de error
  }

  void deleteAt(int index)
  {
    if (index < 0 || head == nullptr) // si el indice no es valido o la lista esta vacia
    {
      throw out_of_range("Indice fuera del rango");
    }
    Link *current = head; // Empezamos en la cabeza de la lista
    int actIndex = 0;     // Inicializamos la variable indice actual en ceros

    while (current != nullptr && actIndex < index) // mientras el actual no sea el ultimo nodo en la lista
    // y el indice actual sea menor al indice que estamos buscando
    {
      current = current->next; // avanzamos al siguiente nodo
      ++actIndex;              // incrementamos el indice actual;
    }
    if (current == nullptr) // si el nodo en el que nos encontramos es el final de la lista
    {
      throw out_of_range("Indice furea del rango"); // arrojar mensaje de error
    }

    if (current->prev != nullptr) // si el nodo anterior no es el primer nodo
    {
      current->prev->next = current->next; // el actual se vuelve el previo y este se conecta el siguiente
    }
    else // si el nodo es el primero
    {
      head = current->next; // actualizamos la cabeza
    }

    if (current->next != nullptr) // si el nodo actual no es el ultimo en la lista
    {
      current->next->prev = current->prev; // el actual se vuelve el siguiente y este se conecta al previo
    }
    else // si el nodo es el ultimo
    {
      tail = current->prev; // actualizamos la cola
    }
    delete current; // liberar la memoria del nodo eliminado

  } // Elimina el nodo en el índice dado.

  // Devuelve la representación de la lista en orden ascendente.
  string toStringForward() const
  {
    stringstream aux;
    Link *current = head;      // iniciamos en la cabeza de la lista
    aux << "[";                // inicio abriendo corchetes
    while (current != nullptr) // mientras aun haya elementos en la lista
    {
      aux << current->value;        // se imprime el valor del nodo actual
      if (current->next != nullptr) // mientras el siguiente nodo no sea el ultimo de la lista
      {
        aux << ", "; // hace la separacion de valores
      }
      current = current->next; // avanzamos al siguiente nodo
    }
    aux << "]";       // cerramos corchetes
    return aux.str(); // retorna el string creado a partir de la lista
  }
  // Devuelve la representación de la lista en orden descendente.
  string toStringBackward() const
  {
    stringstream aux;
    Link *current = tail; // iniciamos en la cola de la lista
    aux << "[";
    while (current != nullptr) // mientras aun haya elementos en la lista
    {
      aux << current->value;        // se imprime el valor del nodo actual
      if (current->prev != nullptr) // mientras el nodo anterior no sea el ultimo de la lista
      {
        aux << ", "; // se hace la separacion de valores
      }
      current = current->prev; // retrocedemos el nodo anterior
    }
    aux << "]";       // cerramos corchetes
    return aux.str(); // retorna el string creado a partir de la lista
  }
};

#endif // DLIST_H
