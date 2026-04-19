#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

int max3(int a, int b, int c) {
    return maximo(maximo(a, b), c);
}

int max_cruce(int A[], int izq, int mid, int der) {
    int suma = 0;
    int mejorIzq = INT_MIN;
    int mejorDer = INT_MIN;

    for (int i = mid; i >= izq; i--) {
        suma += A[i];
        if (suma > mejorIzq)
            mejorIzq = suma;
    }

    suma = 0;

    for (int i = mid + 1; i <= der; i++) {
        suma += A[i];
        if (suma > mejorDer)
            mejorDer = suma;
    }

    return mejorIzq + mejorDer;
}

int max_subarreglo(int A[], int izq, int der) {
    if (izq == der)
        return A[izq];

    int mid = (izq + der) / 2;

    return max3(
        max_subarreglo(A, izq, mid),
        max_subarreglo(A, mid + 1, der),
        max_cruce(A, izq, mid, der)
    );
}

void resolverArchivo() {
    FILE *f = fopen("casos.txt", "r");

    if (f == NULL) {
        printf("\nNo se pudo abrir casos.txt\n");
        return;
    }

    int t;
    fscanf(f, "%d", &t);

    for (int caso = 1; caso <= t; caso++) {
        int n;
        fscanf(f, "%d", &n);

        int *A = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            fscanf(f, "%d", &A[i]);

        clock_t ini = clock();
        int resultado = max_subarreglo(A, 0, n - 1);
        clock_t fin = clock();

        double tiempo = (double)(fin - ini) / CLOCKS_PER_SEC;

        printf("\nCaso %d:\n", caso);
        for (int i = 0; i < n; i++)
            printf("%d ", A[i]);

        printf("\nSuma maxima = %d\n", resultado);
        printf("Tiempo = %.6f segundos\n", tiempo);

        free(A);
    }

    fclose(f);
}

void pruebasGrandes() {
    int tamanos[] = {10, 100, 1000, 10000};

    for (int k = 0; k < 4; k++) {
        int n = tamanos[k];
        int *A = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            A[i] = rand() % 201 - 100;

        clock_t ini = clock();
        int resultado = max_subarreglo(A, 0, n - 1);
        clock_t fin = clock();

        double tiempo = (double)(fin - ini) / CLOCKS_PER_SEC;

        printf("\nn = %d\n", n);
        printf("Suma maxima = %d\n", resultado);
        printf("Tiempo = %.6f segundos\n", tiempo);

        free(A);
    }
}

int main() {
    int op;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Leer casos.txt\n");
        printf("2. Pruebas grandes\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        if (op == 1)
            resolverArchivo();
        else if (op == 2)
            pruebasGrandes();
        else if (op == 3)
            printf("Programa finalizado.\n");
        else
            printf("Opcion invalida.\n");

    } while (op != 3);

    return 0;
}