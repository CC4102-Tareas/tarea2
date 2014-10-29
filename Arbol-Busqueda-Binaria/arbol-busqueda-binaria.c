#include <stdio.h>
#include <stdlib.h>
 
#define DEBUG 1

/**
    Implementación hecha seǵun capítulo 12 Cormen 3° edición (pág. 286)
*/
typedef struct nodo {
   int clave;
   struct nodo *hijo_izq, *hijo_der, *padre;
} Nodo;

/**
    Interfaces
*/
Nodo *crear_nodo(int);
void insertar(Nodo **, Nodo **);
Nodo *buscar(Nodo **, int);

void dibujar_arbol(Nodo *);
void dibujar_arbol_helper(Nodo *, int);

void inorder(Nodo **);
void preorder(Nodo **);
void postorder(Nodo **);

/**
    Propiedades que debe cumplir un árbol de búsqueda binaria:
        1) Sea x un nodo en un árbol de búsqueda binaria:
            1.1) Si y es un nodo en el sub-árbol izquierdo de x. entonces y.clave <= x.clave
            1.2) Si y es un nodo en el sub-árbol derecho de x. entonces y.clave >= x.clave
*/

void main() {
   int choice;
   char ans = 'N';
   int key;

   Nodo *nuevo_nodo, *raiz, *tmp;
   raiz = NULL;

   system("clear");
 
   printf("\nPrograma para árbol de búsqueda binaria:");
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
            
            printf("\nIngresar elemento : ");
            scanf("%d", &nuevo_nodo->clave);
            
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
        (DEBUG?printf("\nEl nodo ingresado es la raíz."):1);
        *raiz = *z;
    } else if ((*z)->clave < y->clave) {
        (DEBUG?printf("\nEl nodo ingresado ahora es el hijo izquierdo de %d", y->clave):1);
        y->hijo_izq = *z;
    } else {
        (DEBUG?printf("\nEl nodo ingresado ahora es el hijo derecho de %d", y->clave):1);
        y->hijo_der = *z;
    }
}

/*
    Realiza la búsqueda de una clave dentro de un árbol de búsqueda binario.
    Versión recursiva.
*/
Nodo *buscar(Nodo **raiz, int clave) {
    Nodo *temp;
    temp = *raiz;
    
    (DEBUG?printf("\nSe busca en la clave %d", (*raiz)->clave):1);
    if (*raiz == NULL || (*raiz)->clave == clave) {
        (DEBUG?printf("\nEncontrado!! %d", (*raiz)->clave):1);
        return *raiz;
    }

    // si la clave del árbol es mayor que la buscada
    if ((*raiz)->clave > clave) {
        (DEBUG?printf("\nVamos al hijo izquierdo"):1);
        return buscar(&(*raiz)->hijo_izq, clave);
    } else {
        (DEBUG?printf("\nVamos al hijo derecho"):1);
        return buscar(&(*raiz)->hijo_der, clave);
    }
}


/*
 This function displays the tree in inorder fashion
*/
void inorder(Nodo **temp) {
   if (*temp != NULL) {
      inorder(&((*temp)->hijo_izq));
      printf("%d ", (*temp)->clave);
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
