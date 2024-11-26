#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////
// clase que representa la lista enlazada
template <class T>
class List
{
private:
  struct Link
  {
    T value;                                                           // valor almacenado en los nodos
    Link *next;                                                        // puntero que apunta al siguiente nodo
    Link(const T &val, Link *nxt = nullptr) : value(val), next(nxt) {} // constructor del nodo
  };

  Link *head; // puntero al primer nodo de la lista
  /////////////////////////////////////////////////////////////////////////////////////////////

public:
  List() : head(nullptr) {} // Constructor inicializo la lista vacia apuntando head a nullptr
  /////////////////////////////////////////////////////////////////////////////////////////////

  ~List() // Destructor
  {
    while (head != nullptr) // mientras
    {
      Link *temp = head; // guardamos el nodo actual
      head = head->next; // Avanza al siguiente nodo
      delete temp;       // Libera el espacio del nodo actual
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  // insertar el nuevo elemento alfinal de la lista;
  void insertion(const T &value)
  {
    Link *newNode = new Link(value);
    if (head == nullptr) // si la lista esta vacia
    {
      head = newNode; // el nuevo nodo es la cabeza
    }
    else // si no esta vacia se recorre la lista hasta encontrar el ultimo nodo
    {
      Link *current = head;
      while (current->next != nullptr) // mientras el nodo actual no sea el ultimo en la lista
      {
        current = current->next; // Avanza al siguiente nodo
      }
      // cuando sea el ultimo nodo el la lista
      current->next = newNode; // se conecta el ultimo nodo al nuevo
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  // Busca un elemento y devuelve su índice
  int search(const T &value) const
  {
    Link *current = head;
    int index = 0;                 // inicializo una variable index en cero
    while (current != nullptr)     // mientras el nodo actual no sea el ultimo en la lista
    {                              // se ejecuta este codigo
      if (current->value == value) // si el valor del nodo actual es el que se esta buscando
      {
        return index; // devuelve su indice
      }
      else // si no lo es
      {
        current = current->next; // Avanza al siguiente nodo
        ++index;                 // el indice aumenta en uno
      }
    }
    // si no encuentra el valor retorna el valor especial -1
    return -1;
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  // Actualiza un elemento en el indice que se ponga como argumento
  void update(int index, const T &value)
  {
    if (index < 0) // si el indice indica menor a cero
    {
      throw out_of_range("Indice invalido"); // mostrar mensaje de error
    }

    Link *current = head;
    int actIndex = 0; // indice actual inicializado en cero

    while (current != nullptr) // mientras el actual no sea el ultimo nodo de la lista
    {                          // se ejecuta este codigo
      if (actIndex == index)   // si el indice actual es el que se busca
      {
        current->value = value; // actualizamos el valor del nodo
        return;
      }
      current = current->next; // se avanza al siguiente nodo
      ++actIndex;              // el indice actual tambien avanza
    }
  }
  /////////////////////////////////////////////////////////////////////////////////////////////
  // Elimina el elemento en un índice dado
  void deleteAt(int index)
  {
    if (index < 0 || head == nullptr) // si el indice es menor a cero o el actual es el ultimo nodo
    {
      throw out_of_range("Indice invalido");
    }
    if (index == 0)      // caso especial
    {                    // si el elemento que se busca resultara ser el primero
      Link *temp = head; // sea crea un nodo temporal y se le asigna el valor de head
      head = head->next; // la cabeza se actualiza a ser el siguiente nodo
      delete temp;       // Liberamos la memoria del nodo
      return;
    }

    // caso "estandar"
    Link *current = head;
    int actIndex = 0; // indice actual

    while (current->next != nullptr && actIndex < index - 1) // mientras el actual no sea el ultimo nodo y el indice actual sea menor al indice menos 1
    {
      current = current->next; // nos movemos al nodo anterior al que queremos eliminar
      ++actIndex;
    }

    // en caso de que se llegue al final de la lista y no encuentre el indice
    if (current->next == nullptr) // si el nodo actual es el ultimo de la lista
    {
      throw out_of_range("Indice fuera del rango"); // mostrar mensaje de error
    }

    // Puntero temporal al nodo que queremos eliminar
    Link *temp = current->next; // Nodo que vamos a eliminar
    current->next = temp->next; // reconecto los nodos  para omitir el que se borro
    delete temp;                // Libero la memoria del nodo que borre
  }
  /////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////////////////////
  // convertir la lista en un string
  string toString() const
  {
    stringstream aux;
    Link *current = head;

    aux << "[";                // corchete de apertura
    while (current != nullptr) // mientras el actual no sea el ultimo nodo de la lista
    {
      aux << current->value;        // agrega el valor actual
      if (current->next != nullptr) // si el actual no es el ultimo nodo de la lista
      {
        aux << ", "; // se agrega el separador de valores
      }
      current = current->next; // avanza al siguiente nodo
    }
    aux << "]";       // se ciera el corchete del arreglo/lista
    return aux.str(); // Devuelve la cadena que se genero
  }
};
#endif // LIST_H
