#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

/**
  Implementación hecha según Cormen (capítulo 15, página 397)
 */

/**
  Estructura de cada nodo del árbol.
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

void generar_tablas(float[], float[], int);
void imprimir_matrices();

void dibujar_arbol(Nodo *);
void dibujar_arbol_helper(Nodo *, int);
void inorder(Nodo **);
void preorder(Nodo **);
void postorder(Nodo **);
void mostrar_nodo(Nodo *);

/**
  Main para probar el comportamiento de la estructura

  @param argv[1] = Exponente del experimento a realizar.  
  @param argv[2] = Path del archivo que contiene el arreglo con las probabilidades de aparecer de cada entrada.
  @param argv[3] = Path del archivo que contiene el arreglo con las llaves.
  @param argv[4] = Path del archivo que contiene el arreglo con las busquedas a ser realizadas.
 */
void main(int argc, char *argv[]); {

    // Contador
    int i;

    // Arreglo para cargar los elementos (4 MB)
    int *llaves = malloc(1024 * 1024 * sizeof(int));

    // Arreglo para cargar los elementos (4 MB)
    float *prob = malloc(1024 * 1024 * sizeof(int));
    
    // Arreglo para cargar consultas al arbol (buffer de 400 kB)
    int *buffer_consultas = malloc(1024 * 1024 * 100 * sizeof(int));

    // Exponente
    int exp = atoi(argv[1]);

    // Variables relativas al tiempo de ejecucion
    struct timeval antes , despues;
    double tiempo_construccion, tiempo_busqueda;

    // Variables para construir y consultar arbol
    Nodo *nuevo_nodo, *raiz, *tmp;
    raiz = NULL;

    // Lecturas de archivo: inserciones y consultas

    FILE * fptr = fopen(argv[2], "rb");

    fread(llaves, 1024 * 1024 * sizeof(int), 1, fptr);

    fclose(fptr);

    fptr = fopen(argv[3], "rb");

    fread(buffer_consultas, 1024 * 1024 * 100 * sizeof(int), 1, fptr);

    fclose(fptr);


    int i;
    int N = argv[4];
    int ctd_elem_cons = argv[100*argv[1]];

    /**
      tabla e[1..N+1][0..N] que almacena los costos de cada subarbol i,j.
      El primer índice termina con N+1 para tener un subarbol ficticio d_n.
      El segundo índice comienza desde 0 para tener un subarbol ficticio d_0
      Lo anterior se traduce en computar e[N+1,N] y e[1,0]
      Ocupa las celdas e[i,j] tales que j >= i-1
     */
    float e[N+1][N+1];
    /**
      Matriz para guardar la raíz de cada sub-arbol que contiene las llaves
      en el rango [i,j].
      Ocupa las celdas root[i,j] que cumplen la condición 1 < i =< j < N
     */
    int raiz[N][N];
    /**
      Se necesita otra tabla por eficiencia.
      Se usa para evitar calcular los pesos w(i,j) desde cero cada vez que
      varía e.
      w[1..N+1][0..N]
      Para 1 <= i <= N+1 tenemos w[i,i-1] = q_(i-1)
      Para j >= i tenemos w[i,j] = w[i,j-1] + p_j + q_j
     */
    float w[N+1][c+1];

    float p[] = {0.1, 0.025, 0.2, 0.125, 0.125, 0.05, 0.3, 0.075};
    float q[N];
    // se inicializa a cero dado que estos datos nunca son consultados.
    for(i=0;i<N;i++) {
        q[i] = 0;
    }

    //float p[] = { 0.15, 0.10, 0.05, 0.10, 0.20};
    //float q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    // Genera las matrices e, w, raiz con los datos respectivos para
    // armar el árbol óptimo.
    generar_tablas(p, q, N, e, w, root);

    // en este punto ya están construidas las matrices e, w y raiz
    // ahora formamos el árbol.
    Nodo *nuevo_nodo, *raiz;
    raiz = NULL;

    int izq = 1, der = N-1;
    int raiz = -1;
    for(i=0;i<1;i++) {
        // obtenemos la raiz 
        if (raiz == -1) {
            raiz = root[izq,der];
        } else {
            raiz
        }

        // busco la raíz del 
        nuevo_nodo = crear_nodo(1);
        insertar(&raiz, &nuevo_nodo);
    }

    // una vez armado el árbol se imprime en pantalla
    dibujar_arbol(raiz);

    // ahora realizamos las búsquedas de cada llave
    for(i=0;i<1;i++) {
        buscar(&raiz, key);
    }
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
  Función que genera la matriz e, w y root.
 */
void generar_tablas(float p[], float q[], int n, float e[n+1][n+1], float w[n+1][n+1], float root[n][n]) {
    int i,l,j,r;
    float t;

    for(i=0;i<=n;i++) {
        e[i][i] = q[i];
        w[i][i] = q[i];
    }

    for(l=0;l<n;l++) {
        for(i=0;i<(n-l);i++) {
            j = i + l+1;
            e[i][j] = 1000;
            w[i][j] = w[i][j-1] + p[j-1] + q[j];

            for(r=i;r<=j;r++) {
                t = e[i][r] + e[r+1][j] + w[i][j];

                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j-1] = r+1;
                }
            }
        }
    }
    imprimir_matrices();
}

void crear_arbol() {
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
}
/**
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
    return temp;
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
/**
  función que oculta un parámetro inicial que es
  irrelevante para el que usa la función.
 */
void dibujar_arbol(Nodo *raiz) {
    dibujar_arbol_helper(raiz, 0);
    puts("");
}
/**
  Dibuja la estructura del árbol de izquierda a derecha.
Ej:
hijo1
/
Raiz
\
hijo2
 */
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
/**
  Muestra la información de un nodo.
 */
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
/*****************************************************************************************
  Funciones auxiliares específicas para este árbol
 ******************************************************************************************/
/**
  Función que imprime en la salida estándar el contenido de las
  matrices e, w, raiz
 */
void imprimir_matrices() {
    int row, columns;
    printf("\nMatriz e\n");
    for (row=0; row<N+1; row++) {
        for(columns=0; columns<N+1; columns++)
            printf("%f ", e[row][columns]);
        printf("\n");
    }
    printf("\nMatriz raiz\n");
    for (row=0; row<N; row++) {
        for(columns=0; columns<N; columns++)
            printf("%d ", raiz[row][columns]);
        printf("\n");
    }
    printf("\nMatriz w\n");
    for (row=0; row<N+1; row++) {
        for(columns=0; columns<N+1; columns++)
            printf("%f ", w[row][columns]);
        printf("\n");
    }
    printf("\n");
}
