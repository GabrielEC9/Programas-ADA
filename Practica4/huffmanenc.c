#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct Nodo {
    char caracter;
    unsigned frecuencia;
    struct Nodo *izq, *der;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct Nodo** array;
};

char codigos[256][100];
char textoDecodificado[1000] = "";

struct Nodo* nuevoNodo(char caracter, unsigned frecuencia) {
    struct Nodo* temp = (struct Nodo*)malloc(sizeof(struct Nodo));

    temp->izq = temp->der = NULL;
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;

    return temp;
}

struct MinHeap* crearMinHeap(unsigned capacity) {
    struct MinHeap* minHeap =
        (struct MinHeap*)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;
    minHeap->capacity = capacity;

    minHeap->array =
        (struct Nodo**)malloc(capacity * sizeof(struct Nodo*));

    return minHeap;
}

void swapNodo(struct Nodo** a, struct Nodo** b) {
    struct Nodo* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {

    int menor = idx;
    int izq = 2 * idx + 1;
    int der = 2 * idx + 2;

    if (izq < minHeap->size &&
        minHeap->array[izq]->frecuencia <
        minHeap->array[menor]->frecuencia)
        menor = izq;

    if (der < minHeap->size &&
        minHeap->array[der]->frecuencia <
        minHeap->array[menor]->frecuencia)
        menor = der;

    if (menor != idx) {

        swapNodo(&minHeap->array[menor],
                 &minHeap->array[idx]);

        minHeapify(minHeap, menor);
    }
}

struct Nodo* extraerMin(struct MinHeap* minHeap) {

    struct Nodo* temp = minHeap->array[0];

    minHeap->array[0] =
        minHeap->array[minHeap->size - 1];

    --minHeap->size;

    minHeapify(minHeap, 0);

    return temp;
}

void insertarMinHeap(struct MinHeap* minHeap,
                     struct Nodo* nodo) {

    ++minHeap->size;

    int i = minHeap->size - 1;

    while (i &&
           nodo->frecuencia <
           minHeap->array[(i - 1) / 2]->frecuencia) {

        minHeap->array[i] =
            minHeap->array[(i - 1) / 2];

        i = (i - 1) / 2;
    }

    minHeap->array[i] = nodo;
}

void construirMinHeap(struct MinHeap* minHeap) {

    int n = minHeap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int esTamanoUno(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

struct MinHeap* crearYConstruirMinHeap(
    char caracteres[],
    int frecuencias[],
    int size) {

    struct MinHeap* minHeap = crearMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] =
            nuevoNodo(caracteres[i], frecuencias[i]);

    minHeap->size = size;

    construirMinHeap(minHeap);

    return minHeap;
}

struct Nodo* construirArbolHuffman(
    char caracteres[],
    int frecuencias[],
    int size) {

    struct Nodo *izq, *der, *top;

    struct MinHeap* minHeap =
        crearYConstruirMinHeap(
            caracteres,
            frecuencias,
            size);

    while (!esTamanoUno(minHeap)) {

        izq = extraerMin(minHeap);
        der = extraerMin(minHeap);

        top = nuevoNodo('$',
                        izq->frecuencia + der->frecuencia);

        top->izq = izq;
        top->der = der;

        insertarMinHeap(minHeap, top);
    }

    return extraerMin(minHeap);
}

int esHoja(struct Nodo* root) {
    return !(root->izq) && !(root->der);
}

void guardarCodigos(struct Nodo* root,
                    int arr[],
                    int top) {

    if (root->izq) {
        arr[top] = 0;
        guardarCodigos(root->izq, arr, top + 1);
    }

    if (root->der) {
        arr[top] = 1;
        guardarCodigos(root->der, arr, top + 1);
    }

    if (esHoja(root)) {

        printf("%c: ", root->caracter);

        char codigo[100] = "";

        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);

            char bit[2];
            sprintf(bit, "%d", arr[i]);
            strcat(codigo, bit);
        }

        strcpy(codigos[(unsigned char)root->caracter], codigo);

        printf("\n");
    }
}

void codificarTexto(char texto[]) {

    printf("\n=== TEXTO CODIFICADO ===\n\n");

    for (int i = 0; texto[i] != '\0'; i++) {
        printf("%s", codigos[(unsigned char)texto[i]]);
    }

    printf("\n");
}

void decodificarTexto(struct Nodo* root,
                      char texto[]) {

    char bits[10000] = "";

    for (int i = 0; texto[i] != '\0'; i++) {
        strcat(bits,
               codigos[(unsigned char)texto[i]]);
    }

    printf("\n=== TEXTO DECODIFICADO ===\n\n");

    struct Nodo* actual = root;

    for (int i = 0; bits[i] != '\0'; i++) {

        if (bits[i] == '0')
            actual = actual->izq;
        else
            actual = actual->der;

        if (esHoja(actual)) {

            char temp[2];
            temp[0] = actual->caracter;
            temp[1] = '\0';

            strcat(textoDecodificado, temp);

            printf("%c", actual->caracter);

            actual = root;
        }
    }

    printf("\n");
}

void guardarArbol(struct Nodo* root, int espacio, FILE *archivo) {

    if (root == NULL)
        return;

    espacio += 5;

    guardarArbol(root->der, espacio, archivo);

    fprintf(archivo, "\n");

    for (int i = 5; i < espacio; i++)
        fprintf(archivo, " ");

    if(root->caracter != '$')
        fprintf(archivo, "%c(%d)\n",
                root->caracter,
                root->frecuencia);
    else
        fprintf(archivo, "%d\n",
                root->frecuencia);

    guardarArbol(root->izq, espacio, archivo);
}

int main() {

    FILE *archivo = fopen("texto.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    char texto[1000];

    fgets(texto, sizeof(texto), archivo);

    fclose(archivo);

    int frecuencia[256] = {0};

    for (int i = 0; texto[i] != '\0'; i++) {
        frecuencia[(unsigned char)texto[i]]++;
    }

    char caracteres[256];
    int frecuencias[256];

    int size = 0;

    for (int i = 0; i < 256; i++) {

        if (frecuencia[i] > 0) {

            caracteres[size] = i;
            frecuencias[size] = frecuencia[i];

            size++;
        }
    }

    struct Nodo* root =
        construirArbolHuffman(
            caracteres,
            frecuencias,
            size);

    int arr[MAX_TREE_HT], top = 0;

    printf("=== TABLA HUFFMAN ===\n\n");

    guardarCodigos(root, arr, top);

    FILE *archivoArbol = fopen("arbolc.txt", "w");

    guardarArbol(root, 0, archivoArbol);

    fclose(archivoArbol);

    printf("\n=== TEXTO ORIGINAL ===\n\n");
    printf("%s\n", texto);

    codificarTexto(texto);

    decodificarTexto(root, texto);

    if(strcmp(texto, textoDecodificado) == 0)
        printf("\nVERIFICACION EXITOSA\n");
    else
        printf("\nERROR EN DECODIFICACION\n");

    return 0;
}