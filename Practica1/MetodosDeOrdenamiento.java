import java.util.*;

public class MetodosDeOrdenamiento {

    /* ================= MERGE SORT ================= */

    private static void merge(int[] arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        int[] L = new int[n1];
        int[] R = new int[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];

        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;

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
    }

    private static void mergeSort(int[] arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    /* ================= QUICK SORT ================= */

    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    /* ================= HEAP SORT ================= */

    private static void heapify(int[] arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            heapify(arr, n, largest);
        }
    }

    private static void heapSort(int[] arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, i, 0);
        }
    }

    /* ================= PROGRAMA PRINCIPAL ================= */

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();

        int opcionAlg;
        int opcionTam;
        int[] tamanos = {10, 100, 1000, 10000, 100000, 1000000};
        int n;

        System.out.println("=== MENU ORDENAMIENTOS ===");
        System.out.println("1. Merge Sort");
        System.out.println("2. Quick Sort");
        System.out.println("3. Heap Sort");
        System.out.print("Seleccione algoritmo: ");
        opcionAlg = scanner.nextInt();

        System.out.println("\nSeleccione tamaño:");
        for (int i = 0; i < 6; i++)
            System.out.println((i + 1) + ". " + tamanos[i] + " elementos");

        System.out.print("Opcion: ");
        opcionTam = scanner.nextInt();

        if (opcionTam < 1 || opcionTam > 6) {
            System.out.println("Opcion invalida");
            scanner.close();
            return;
        }

        n = tamanos[opcionTam - 1];

        int[] arr = new int[n];

        for (int i = 0; i < n; i++)
            arr[i] = random.nextInt();

        System.out.println("\nOrdenando " + n + " elementos...\n");

        // Obtener referencia al Runtime
        Runtime runtime = Runtime.getRuntime();

        // Forzar garbage collection antes de la medición
        System.gc();
        long memoriaAntes = runtime.totalMemory() - runtime.freeMemory();

        long inicio = System.nanoTime();

        if (opcionAlg == 1)
            mergeSort(arr, 0, n - 1);
        else if (opcionAlg == 2)
            quickSort(arr, 0, n - 1);
        else if (opcionAlg == 3)
            heapSort(arr, n);
        else
            System.out.println("Opcion invalida");

        long fin = System.nanoTime();

        // Obtener memoria después del ordenamiento
        long memoriaDespues = runtime.totalMemory() - runtime.freeMemory();
        long memoriaUsada = memoriaDespues - memoriaAntes;

        double tiempoSegundos = (double)(fin - inicio) / 1_000_000_000.0;
        double memoriaUsadaMB = memoriaUsada / (1024.0 * 1024.0);
        double memoriaAntesM = memoriaAntes / (1024.0 * 1024.0);
        double memoriaDespuesM = memoriaDespues / (1024.0 * 1024.0);

        System.out.println("=== RESULTADOS ===");
        System.out.printf("Tiempo: %.6f segundos%n", tiempoSegundos);
        System.out.printf("Memoria antes: %.2f MB%n", memoriaAntesM);
        System.out.printf("Memoria despues: %.2f MB%n", memoriaDespuesM);
        System.out.printf("Memoria usada por el algoritmo: %.2f MB%n", memoriaUsadaMB);
        System.out.printf("Memoria total del arreglo: %.2f MB%n", (n * 4.0) / (1024.0 * 1024.0));

        scanner.close();
    }
}