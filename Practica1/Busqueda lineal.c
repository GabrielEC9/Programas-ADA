#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_SIZE 100003

/* ==========================
   Estructura para Hash
   ========================== */
typedef struct Node {
    int key;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

/* ==========================
   Funcion Hash
   ========================== */
int hashFunction(int key) {
    return key % HASH_SIZE;
}

void insertHash(int key) {
    int index;
    Node* newNode;

    index = hashFunction(key);

    newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int searchHash(int key) {
    int index;
    Node* temp;

    index = hashFunction(key);
    temp = hashTable[index];

    while (temp != NULL) {
        if (temp->key == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

/* ==========================
   Busqueda Lineal
   ========================== */
int linearSearch(int arr[], int n, int target) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

/* ==========================
   Busqueda Binaria
   ========================== */
int binarySearch(int arr[], int n, int target) {
    int left, right, mid;

    left = 0;
    right = n - 1;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

/* ==========================
   Generar arreglo ordenado
   ========================== */
void generateArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
}

/* ==========================
   Liberar memoria hash
   ========================== */
void freeHash() {
    int i;
    Node* temp;
    Node* aux;

    for (i = 0; i < HASH_SIZE; i++) {
        temp = hashTable[i];
        while (temp != NULL) {
            aux = temp;
            temp = temp->next;
            free(aux);
        }
        hashTable[i] = NULL;
    }
}

/* ==========================
   Programa Principal
   ========================== */
int main() {

    int option;
    int sizeOption;
    int sizes[7] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int n;
    int *arr;
    int target;
    int i;

    clock_t start, end;
    double cpu_time;

    printf("===== MENU DE BUSQUEDA =====\n");
    printf("1. Busqueda Lineal\n");
    printf("2. Busqueda Binaria\n");
    printf("3. Busqueda Hash\n");
    printf("Seleccione opcion: ");
    scanf("%d", &option);

    printf("\nSeleccione tamaño del arreglo:\n");
    for (i = 0; i < 7; i++) {
        printf("%d. %d elementos\n", i+1, sizes[i]);
    }

    printf("Opcion: ");
    scanf("%d", &sizeOption);

    if (sizeOption < 1 || sizeOption > 7) {
        printf("Opcion invalida\n");
        return 1;
    }

    n = sizes[sizeOption - 1];

    arr = (int*)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Error de memoria\n");
        return 1;
    }

    generateArray(arr, n);

    target = n - 1;   /* Peor caso */

    if (option == 1) {

        start = clock();
        linearSearch(arr, n, target);
        end = clock();

    } else if (option == 2) {

        start = clock();
        binarySearch(arr, n, target);
        end = clock();

    } else if (option == 3) {

        for (i = 0; i < HASH_SIZE; i++)
            hashTable[i] = NULL;

        for (i = 0; i < n; i++)
            insertHash(arr[i]);

        start = clock();
        searchHash(target);
        end = clock();

        freeHash();

    } else {
        printf("Opcion invalida\n");
        free(arr);
        return 1;
    }

    cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTiempo de ejecucion: %f segundos\n", cpu_time);
    printf("Memoria usada por arreglo: %.2f MB\n",
           (n * sizeof(int)) / (1024.0 * 1024.0));

    free(arr);

    return 0;
}
