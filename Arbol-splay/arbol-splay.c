#include <stdio.h>
#include <stdlib.h>
 
#define DEBUG 1

/**
    Implementación hecha según URL: https://www.cs.berkeley.edu/~jrs/61b/lec/36
*/
typedef struct nodo {
   int clave;
   struct nodo *hijo_izq, *hijo_der, *padre;
} Nodo;

/**
    Interfaces
*/
Nodo *crear_nodo(int);
void rotacion_izq(Nodo **, Nodo **);
void rotacion_der(Nodo **, Nodo **);
void insertar(Nodo **, Nodo **);
void llevar_a_raiz(Nodo **, Nodo **);
Nodo *buscar(Nodo **, int);

void dibujar_arbol(Nodo *);
void dibujar_arbol_helper(Nodo *, int);

void inorder(Nodo **);
void preorder(Nodo **);
void postorder(Nodo **);

void mostrar_nodo(Nodo *);
/**
    Propiedades que debe cumplir un árbol rojo-negro:
        1) Todo nodo es ROJO o NEGRO.
        2) La raíz es NEGRO.
        3) Toda hoja es NEGRO.
        4) Para cada nodo i, todas las rutas del nodo i a sus hojas contienen el mismo número de nodos negros.
*/

void main() {
   int choice;
   char ans = 'N';
   int key;

   Nodo *nuevo_nodo, *raiz, *tmp;
   raiz = NULL;

   system("clear");
 
   printf("\nPrograma para árbol rojo-negro:");
   do {
      printf("\n1.Insertar");
      printf("\n2.Buscar");
      printf("\n3.Listar árbol");
      printf("\n4.Dibujar arbol");
      printf("\n5.Exit");
      printf("\nIndicar operación : ");
      scanf("%d", &choice);
 
      switch (choice) {
      case 1:
         do {
            nuevo_nodo = crear_nodo(1);
                       
            insertar(&raiz, &nuevo_nodo);
            nuevo_nodo = crear_nodo(2);
            insertar(&raiz, &nuevo_nodo);
            nuevo_nodo = crear_nodo(3);
            insertar(&raiz, &nuevo_nodo);
            nuevo_nodo = crear_nodo(4);

            //printf("\nIngresar elemento : ");
            //scanf("%d", &nuevo_nodo->clave);
            
            insertar(&raiz, &nuevo_nodo);
            printf("\nQuiere ingresar mas elementos?(y/n) : ");
            scanf(" %c", &ans);
         } while (ans == 'y');
         break;
 
      case 2:
         printf("\nIngresar clave a ser buscada : ");
         scanf("%d", &key);
 
         tmp = buscar(&raiz, key);
         if(tmp == NULL)
            printf("\nNo existe la clave en el árbol!!!");

         break;
 
      case 3:
         if (raiz == NULL) {
            printf("Arbol no está creado.");
         } else {
            printf("\nMostrar Inorder : ");
            inorder(&raiz);
            printf("\nMostrar Preorder : ");
            preorder(&raiz);
            printf("\nMostrar Postorder : ");
            postorder(&raiz);
         }
         break;
      case 4:
         dibujar_arbol(raiz);
         break;
      }
   } while (choice != 5);
}

/**
 Crea un nuevo nodo
*/
Nodo *crear_nodo(int clave) {
   Nodo *temp;
   temp = (Nodo *) malloc(sizeof(Nodo));
   temp->clave = clave;
   temp->hijo_izq = NULL;
   temp->hijo_der = NULL;
   temp->padre = NULL;

   return temp;
}

/**
    Esta función realiza una rotación a la izquierda de un nodo dentro del árbol

        Y                             X     
       / \        rotate left        / \
      X   ^      <------------      ^   Y   
     / \ /C\                       /A\ / \
    ^  ^                               ^  ^ 
   /A\/B\                             /B\/C\

*/
void rotacion_izq(Nodo **raiz, Nodo **x) {
  
    //(DEBUG?printf("\nRotación izquierda del nodo con valor %d", (*x)->clave):1);

    // y es el hijo derecho de x
    Nodo *y = (*x)->hijo_der;
    // el hijo derecho de X es el hijo izquierdo de Y
    (*x)->hijo_der= y->hijo_izq;

    // si el hijo izquierdo de y no es NULL, se actualiza el padre de este.
    if (y->hijo_izq != NULL) {
        y->hijo_izq->padre = *x;
    }
    // El padre de x es ahora el padre de y.
    y->padre = (*x)->padre;

    // si x es la raíz
    if ((*x)->padre == NULL) {
        // ahora y es la raíz
        *raiz = y;
    // si x es el hijo izquierdo
    } else if (*x == (*x)->padre->hijo_izq) {
        (*x)->padre->hijo_izq = y;
    // de lo contrario Y es el hermano derecho
    } else {
        (*x)->padre->hijo_der = y;
    }
    
    // el hijo izquierdo de y es x
    y->hijo_izq = *x;
    // x tiene como nuevo padre a y.
    (*x)->padre = y;
}

/**
    Esta función realiza una rotación a la derecha de un nodo dentro del árbol

        Y                             X     
       / \        rotate right       / \
      X   ^      ------------>      ^   Y   
     / \ /C\                       /A\ / \
    ^  ^                               ^  ^ 
   /A\/B\                             /B\/C\

*/
void rotacion_der(Nodo **raiz, Nodo **y) {

    //(DEBUG?printf("\nRotación derecha del nodo con valor %d", (*y)->clave):1);

    // x es el hijo izquierdo de y
    Nodo *x = (*y)->hijo_izq;
    // el hijo izquierdo de y es el hijo derecho de x
    (*y)->hijo_izq= x->hijo_der;

    // si el hijo derecho de x no es NULL, se actualiza el padre de este.
    if (x->hijo_der != NULL) {
        x->hijo_der->padre = *y;
    }
    // El padre de y es ahora el padre de x.
    x->padre = (*y)->padre;

    // si x es la raíz
    if ((*y)->padre == NULL) {
        // ahora y es la raíz
        *raiz = x;
    // si y es el hijo derecho
    } else if (*y == (*y)->padre->hijo_der) {
        (*y)->padre->hijo_der = x;
    // de lo contrario x es el hermano izquierdo
    } else {
        (*y)->padre->hijo_izq = x;
    }
    
    // el hijo derecho de x es y
    x->hijo_der = *y;
    // y tiene como nuevo padre a x.
    (*y)->padre = x;
}

/**
    Inserta un nodo en la estructura.
*/
void insertar(Nodo **raiz, Nodo **z) {
    Nodo *y = NULL;
    Nodo *x = *raiz;
    
    // avanzamos hasta llegar al nodo donde se va a insertar
    while(x != NULL) {
        y = x;
        // si la clave a insertar es menor que la que está en x.
        if ((*z)->clave < x->clave) {
            (DEBUG?printf("\nLa clave ingresada es menor que %d, nos movemos al hijo izquierdo.", x->clave):1);
            // nos movemos al nodo de la izquierda
            x = x->hijo_izq;
        // de lo contrario nos vamos a la derecha.
        } else {
            (DEBUG?printf("\nLa clave ingresada es mayor que %d, nos movemos al hijo derecho.", x->clave):1);
            x = x->hijo_der;
        }
    }

    // el padre de z será el nodo hoja encontrado en el WHILE
    (*z)->padre = y;

    // si el árbol está vacío.
    if (y == NULL) {
        // z es la raíz.
        (DEBUG?printf("\nEl nodo %d es la raíz.", (*z)->clave):1);
        *raiz = *z;
    } else if ((*z)->clave < y->clave) {
        (DEBUG?printf("\nEl nodo %d ahora es el hijo izquierdo de %d", (*z)->clave, y->clave):1);
        y->hijo_izq = *z;
    } else {
        (DEBUG?printf("\nEl nodo %d ahora es el hijo derecho de %d", (*z)->clave, y->clave):1);
        y->hijo_der = *z;
    }

    // llevamos la llave a la raíz
    llevar_a_raiz(&*raiz, &*z);
}

/*
    Realiza la búsqueda de una clave dentro del árbol.
*/
Nodo *buscar(Nodo **raiz, int clave) {
    Nodo *temp;
    temp = *raiz;

    // buscamos desde la raíz
    while (temp != NULL) {
        (DEBUG?printf("\nSe busca en la clave %d", temp->clave):1);

        // si es la clave buscada
        if (temp->clave == clave) {
            break;
        }

        // si la clave buscada es menor
        if (temp->clave > clave) {
            (DEBUG?printf("\nVamos al hijo izquierdo"):1);
            temp = temp->hijo_izq;
        } else {
            (DEBUG?printf("\nVamos al hijo derecho"):1);
            temp = temp->hijo_der;
        }
    }
    
    // si no encontró la llave, recuperamos el último nodo encontrado.
    if (temp == NULL) {
        temp = temp->padre;
        (DEBUG?printf("\nNo se encontró la llave, mantenemos la llave %d", temp->clave):1);
    } else {
        (DEBUG?printf("\nSe encontró la llave %d", temp->clave):1);
    }
    
    // llevamos la llave a la raíz
    llevar_a_raiz(&*raiz, &temp);
    
    return temp;
}

void llevar_a_raiz(Nodo **raiz, Nodo **nodo) {
    Nodo *temp;
    temp = *nodo;

    (DEBUG?printf("\nComenzamos a realizar las rotaciones."):1);

    // realizamos las rotaciones pertinenes hasta encontrar la raiz
    while (temp != *raiz) {
        
        (DEBUG?printf("\nEstamos en la llave %d", temp->clave):1);
        
        // si el padre es la raiz, y soy el hijo el derecho
        if (temp->padre == *raiz && temp == temp->padre->hijo_der) {
           
            (DEBUG?printf("\n%d es el hijo derecho de la raíz %d.", temp->clave, temp->padre->clave):1);
            // zig    
            temp = temp->padre;
            rotacion_izq(&*raiz, &temp);
            // temp ya no es la raíz, debemos ir a la raíz
            temp = temp->padre;
        // si el padre es la raiz, y soy el hijo el izquierdo
        } else if (temp->padre == *raiz && temp == temp->padre->hijo_izq) {

            (DEBUG?printf("\n%d es el hijo izquierdo de la raíz %d.", temp->clave, temp->padre->clave):1);
            // zag
            temp = temp->padre;
            rotacion_der(&*raiz, &temp);
            // temp ya no es la raíz, debemos ir a la raíz
            temp = temp->padre;
        // si temp es el hijo derecho de un hijo izquierdo
        } else if (temp == temp->padre->hijo_der && temp->padre == temp->padre->padre->hijo_izq) {
            
            (DEBUG?printf("\n%d es el hijo derecho de %d, que es hijo izquierdo de %d.", temp->clave, 
                                                                                         temp->padre->clave, 
                                                                                         temp->padre->padre->clave):1);
            // zig-zag
            temp = temp->padre;
            rotacion_izq(&*raiz, &temp);
            temp = temp->padre->padre;
            rotacion_der(&*raiz, &temp);
            temp = temp->padre;
        // si temp es el hijo izquierdo de un hijo derecho
        } else if (temp == temp->padre->hijo_izq && temp->padre == temp->padre->padre->hijo_der) {
            
            (DEBUG?printf("\n%d es el hijo izquierdo de %d, que es hijo derecho de %d.", temp->clave, 
                                                                                         temp->padre->clave, 
                                                                                         temp->padre->padre->clave):1);
            // zag-zig
            temp = temp->padre;
            rotacion_der(&*raiz, &temp);
            temp = temp->padre->padre;
            rotacion_izq(&*raiz, &temp);
            temp = temp->padre;
        // si temp es el hijo izquierdo de un hijo izquierdo
        } else if (temp == temp->padre->hijo_izq && temp->padre == temp->padre->padre->hijo_izq) {
            
            (DEBUG?printf("\n%d es el hijo izquierdo de %d, que es hijo izquierdo de %d.", temp->clave, 
                                                                                           temp->padre->clave, 
                                                                                           temp->padre->padre->clave):1);
            // zag-zag
            temp = temp->padre;
            rotacion_der(&*raiz, &temp);
            temp = temp->padre->padre;
            rotacion_der(&*raiz, &temp);
            temp = temp->padre;
        // si temp es el hijo derecho  de un hijo derecho
        } else if (temp == temp->padre->hijo_der && temp->padre == temp->padre->padre->hijo_der) {
            
            (DEBUG?printf("\n%d es el hijo derecho de %d, que es hijo derecho de %d.", temp->clave, 
                                                                                       temp->padre->clave, 
                                                                                       temp->padre->padre->clave):1);
            // zag-zag
            temp = temp->padre;
            rotacion_izq(&*raiz, &temp);
            temp = temp->padre->padre;
            rotacion_izq(&*raiz, &temp);
            temp = temp->padre;
        } 
    }
}

/*
 This function displays the tree in inorder fashion
*/
void inorder(Nodo **temp) {
   if (*temp != NULL) {
      inorder(&((*temp)->hijo_izq));
      mostrar_nodo(*temp);
      //printf("%d ", (*temp)->clave);
      inorder(&((*temp)->hijo_der));
   }
}
/*
 This function displays the tree in preorder fashion
*/
void preorder(Nodo **temp) {
   if (*temp != NULL) {
      printf("%d ", (*temp)->clave);
      preorder(&((*temp)->hijo_izq));
      preorder(&((*temp)->hijo_der));
   }
}
 
/*
 This function displays the tree in postorder fashion
*/
void postorder(Nodo **temp) {
   if (*temp != NULL) {
      postorder(&((*temp)->hijo_izq));
      postorder(&((*temp)->hijo_der));
      printf("%d ", (*temp)->clave);
   }
}


void dibujar_arbol(Nodo *raiz) {
    dibujar_arbol_helper(raiz, 0);
    puts("");
}

#define ESPACIO_POR_NIVEL 2
void dibujar_arbol_helper(Nodo *arbol, int nivel) {
    int i;
    if (arbol == NULL) {
        printf("<árbol vacío>");
        return;
    }
    if (arbol->hijo_der != NULL) {
        dibujar_arbol_helper(arbol->hijo_der, nivel + ESPACIO_POR_NIVEL);
    }
    for(i=0; i < nivel; i++)
        printf(" ");
        
    printf("%d\n", arbol->clave);
    
    if (arbol->hijo_izq != NULL) {
        dibujar_arbol_helper(arbol->hijo_izq, nivel + ESPACIO_POR_NIVEL);
    }
}

void mostrar_nodo(Nodo *nodo) {
    
    printf("\n");

    if (nodo != NULL) {
        printf("Nodo %d", nodo->clave);

        if (nodo->padre != NULL)
            printf("| padre: %d", nodo->padre->clave);
        if (nodo->hijo_izq != NULL)
            printf("| hijo_izq: %d", nodo->hijo_izq->clave);
        if (nodo->hijo_der != NULL)
            printf("| hijo_der: %d", nodo->hijo_der->clave);
    } else {
        printf("Nodo Nulo!!");
    }

}
