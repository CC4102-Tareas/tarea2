#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 1

/**
    Implementación hecha seǵun capítulo 20 Cormen 3° edición (pág. 531)
*/
typedef struct proto-veb {
    int universo;        // tamaño del universo de la estructura.
    int min;             // almacena el valor mínimo que contiene el Proto-VEB, no está en la estructura.
    int max;             // almacena el valor máximo que contiene el Proto-VEB, no está en la estructura.

    int *resumen;        // arreglo de int que indica que estructuras en el cluster son vacías.
    Proto-veb **cluster; // arreglo de Proto-veb para almancenar los hijos (son raíz de u).
} Proto-VEB;

/**
    Funciones auxiliares para calcular los indices dentro del Proto-VEB
*/
int high(x, u) {
    return x/sqrt(u);
}

int low(x,u) {
    return x%sqrt(u);
}

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
    Inserta número en la estructura.
*/
void insertar(Nodo **v, int x) {
    int aux;
    int high = high(x, temp->u);
    int low = low(x, temp->u);

    VEB * temp= *v;

    if (temp->min == NULL) {
        vEB-Empty-Tree-Insert(&temp, x);
    } else if (x < temp->min) {
        aux = x;
        x = temp->min;
        temp->min = aux;
        
        if (temp->u >2) {
            if (vEB-Tree-Minimum(temp->cluster[high]) == NULL) {
                vEB-Tree-Insert(temp->resumen, high);
                vEB-Empty-Tree-Insert(temp->cluster[high], low);
            } else {
                vEB-Tree-Insert(temp->cluster[high], low);
            }
        }

        if(x > temp->max) {
            temp->max = x;
        }
    }

    (DEBUG?printf("\nLa clave ingresada es menor que %d, nos movemos al hijo izquierdo.", x->clave):1);
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
