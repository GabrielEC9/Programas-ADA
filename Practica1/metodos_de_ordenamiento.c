#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================= MERGE SORT ================= */

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    int m;
    if (l < r) {
        m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/* ================= QUICK SORT ================= */

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    int pi;
    if (low < high) {
        pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* ================= HEAP SORT ================= */

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int temp;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    int i, temp;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (i = n - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

/* ================= MAIN CON MENU ================= */

int main() {
    int opcionAlg, opcionTam;
    int tamanos[] = {10, 100, 1000, 10000, 100000, 1000000};
    int n;
    int i;
    int *arr;

    printf("=== MENU ORDENAMIENTOS ===\n");
    printf("1. Merge Sort\n");
    printf("2. Quick Sort\n");
    printf("3. Heap Sort\n");
    printf("Seleccione algoritmo: ");
    scanf("%d", &opcionAlg);

    printf("\nSeleccione tamano:\n");
    for (i = 0; i < 6; i++)
        printf("%d. %d elementos\n", i + 1, tamanos[i]);

    printf("Opcion: ");
    scanf("%d", &opcionTam);

    n = tamanos[opcionTam - 1];

    arr = (int*)malloc(n * sizeof(int));

    srand(time(NULL));
    for (i = 0; i < n; i++)
        arr[i] = rand();

    printf("\nOrdenando %d elementos...\n", n);

    {
        clock_t inicio = clock();

        if (opcionAlg == 1)
            mergeSort(arr, 0, n - 1);
        else if (opcionAlg == 2)
            quickSort(arr, 0, n - 1);
        else if (opcionAlg == 3)
            heapSort(arr, n);
        else
            printf("Opcion invalida\n");

        clock_t fin = clock();

        printf("Tiempo: %.6f segundos\n",
               (double)(fin - inicio) / CLOCKS_PER_SEC);
    }

    free(arr);
    return 0;
}
