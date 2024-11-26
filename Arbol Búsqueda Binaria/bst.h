#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

template <typename T>
class BST // clase del arbol binarie xd
{
private:
  struct Node // definicion de nodo del arbol
  {
    T data;      // dato que se almacena en el nodo
    Node *left;  // puntero al subarbol izquierdo
    Node *right; // puntero al subarbol derecho

    // constructor
    Node(T value) : data(value), left(nullptr), right(nullptr) {} // inicializar los nodos con un valor
  };

  Node *root; // Puntero a la raiz del arbol

  // Agregar un valor al arbol
  void add(Node *&node, T value)
  {
    if (node == nullptr) // si en el nodo actual no hay, se crea un nuevo nodo
    {
      node = new Node(value);
    }
    else if (value < node->data) // si al valor es menor al que esta en el nodo actual
    {
      add(node->left, value); // se agrega al subarbol izquierdo
    }
    else // si es mayor
    {
      add(node->right, value); // se agrega al subarbol derecho
    }
  }
  // recorre el arbol
  string visit(Node *node, int order) const
  {
    if (node == nullptr) // si el nodo tiene valor nulo, devuelve un string vacio
    {
      return "";
    }
    ostringstream oss; // stream que construye la salida
    if (order == 0)    // raiz, izquierda, derecha
    {
      oss << node->data << " ";         // raiz
      oss << visit(node->left, order);  // izquierda
      oss << visit(node->right, order); // derecha
    }
    else if (order == 1) // izquierda, raiz, derecha
    {
      oss << visit(node->left, order);  // izquierda
      oss << node->data << " ";         // raiz
      oss << visit(node->right, order); // derecha
    }
    else if (order == 2) // izquierda, derecha, raiz
    {
      oss << visit(node->left, order);  // izquierda
      oss << visit(node->right, order); // derecha
      oss << node->data << " ";         // raiz
    }
    string result = oss.str();                   // conbierto el stream a string
    if (!result.empty() && result.back() == ' ') // eliminar cualquier espacio en blanco
    {
      result.pop_back();
    }
    return result; // devolver la cadena construida
  }

  // calcular altura del arbol
  int height(Node *node) const
  {
    if (node == nullptr) // si el nodo es nulo
    {
      return 0; // tiene altura de cero
    }
    // retorna la altura maxima entro los arboles izquierdo y derecho
    return 1 + max(height(node->left), height(node->right));
  }

  // buscar ancestros de un valor
  string ancestors(Node *node, T value) const
  {
    if (node == nullptr) // si el nodo es nulo
    {
      return ""; // no hay ancestros
    }
    if (node->data == value) // si encontramos el valor
    {
      return ""; // entonces no hay ancestros
    }

    ostringstream oss; // construir la salida

    // verificar si el valor esta en el arbol izquirdo o derecho
    if ((node->left && !ancestors(node->left, value).empty()) ||
        (node->right && !ancestors(node->right, value).empty()))
    {
      oss << node->data << " "; // si el valor se encuentra en el subarbol izq o derecho agregamos el dato actual
      return oss.str();         // devolver el ancestro
    }
    if (value < node->data) // si el valor buscado es menor
    {
      return ancestors(node->left, value); // busca en el arbol izquierdo
    }
    else // caso contrario
    {
      return ancestors(node->right, value); // buaca en el derecho
    }
  }
  // saber en que nivel se encuentra un nodo
  int whatlevelamI(Node *node, T value, int level) const
  {
    if (node == nullptr)
    // si el nodo es nulo
    {
      return -1; // el valor entonces no esta en arbol
    }
    if (node->data == value)
    // si se encuentra el valor en el nodo
    {
      return level; // devolvemos el nivel actual
    }
    if (value < node->data)
    // si el valor es mayor que el valor del nodo actual
    {
      return whatlevelamI(node->left, value, level + 1); // se busca en el arbol izquierdo y el nivel incrementa en 1
    }
    else
    // si el valor es mayor
    {
      return whatlevelamI(node->right, value, level + 1); // lo mismo pero con el arbol derecho
    }
  }

public:
  // Constructor por defecto de un arbol vacio
  BST() : root(nullptr) {}
  ~BST() { clear(root); } // libera la memoria del arbol

  // libera la memoria de los nodos
  void clear(Node *node)
  {
    if (node != nullptr) // si el nodo no este vacio
    {
      clear(node->left);  // limpia el arbol izquierdo
      clear(node->right); // limpia el arbol derecho
      delete node;        // elimina el nodo actual
    }
  }

  // agregar valores al arbol
  void add(T value)
  {
    add(root, value);
  }

  // visitar el arbol (hola)
  string visit() const
  {
    return visit(root, 1);
  }

  //  calcula la altura del arbol
  int height() const
  {
    return height(root);
  }

  // obtiene los ancestros
  string ancestors(T value) const
  {
    return ancestors(root, value);
  }

  int whatlevelamI(T value) const
  {
    return whatlevelamI(root, value, 1); // el nivel raiz es el 1 acuerdese augusto
  }
};

// NOTAS BST
/*
A grandes rasgos...
El arbol siempre inicia desde la raiz por si solo y de ahi cambia hacia izquierda o derecha
segun lo necesite.

Mas explicado...
Root es el nodo inicial del arbol, todas las operaciones deben iniciar desde
el nodo root, cuando el arbol agrega, busca o hace algo siempre inicia desde la raiz
si el valor es menor que el valor del nodo actual se mueve hacia la izquierda
caso contrario es mayor se mueve a la derecha

Para insertar un numero en el arbol siempre como dije anteriormente augustito
se inicia desde la razi, si el valor es menor que la raiz baja un nivel en direccion
a la izquierda o si es mayor que la raiz baja hacia la derecha y asi hasta que haya un nodo vacio
donde el valor quede bien

Para buscar un numero igual LA RAIZ SIEMPRE LA RAIZ
compara el numero en el nodo actual con el que se esta buscando
y de nuevo segun la regla de si es mayor o menor se mueve a la
derecha o izquierda hasta que encuentre el numero


en un arbol vacio que es como se inicializa agregamos el numero 10
    10

si agrego 5 como es menor que 10 se va pa la izquierda
    10
   /
  5

ahora para agregar 15 lo mismo siempre de la raiz a ver que pedo
como es mayor que 10 se va pa la derecha
    10
   /  \
  5   15

y si agrego un 6 pues es menor que 10 asi que se va pa la izquierda pero es mayor que 5
entonces en el lado izquierdo se hace tantito a la derecha
    10
   /\  \
  5 6  15

y pues lo mismo cuando busco alguno de estos numeros por parametro le paso el
que estoy buscando y lo va comparando con lo que hay en el arbol y se mueve de
izquierda a derecha segun ocupe



*/

#endif // BST_H
