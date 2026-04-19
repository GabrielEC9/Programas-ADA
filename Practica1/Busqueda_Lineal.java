import java.util.*;

public class Busqueda_Lineal {

    /* ==========================
       Estructura para Hash
       ========================== */
    static class Node {
        int key;
        Node next;

        Node(int key) {
            this.key = key;
            this.next = null;
        }
    }

    private static final int HASH_SIZE = 100003;
    private static Node[] hashTable = new Node[HASH_SIZE];

    /* ==========================
       Funcion Hash
       ========================== */
    private static int hashFunction(int key) {
        return key % HASH_SIZE;
    }

    private static void insertHash(int key) {
        int index = hashFunction(key);
        Node newNode = new Node(key);
        newNode.next = hashTable[index];
        hashTable[index] = newNode;
    }

    private static boolean searchHash(int key) {
        int index = hashFunction(key);
        Node temp = hashTable[index];

        while (temp != null) {
            if (temp.key == key)
                return true;
            temp = temp.next;
        }
        return false;
    }

    /* ==========================
       Busqueda Lineal
       ========================== */
    private static int linearSearch(int[] arr, int n, int target) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == target)
                return i;
        }
        return -1;
    }

    /* ==========================
       Busqueda Binaria
       ========================== */
    private static int binarySearch(int[] arr, int n, int target) {
        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

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
    private static void generateArray(int[] arr, int n) {
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    }

    /* ==========================
       Liberar memoria hash
       ========================== */
    private static void freeHash() {
        for (int i = 0; i < HASH_SIZE; i++) {
            hashTable[i] = null;
        }
    }

    /* ==========================
       Programa Principal
       ========================== */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int option;
        int sizeOption;
        int[] sizes = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
        int n;
        int[] arr;
        int target;

        System.out.println("===== MENU DE BUSQUEDA =====");
        System.out.println("1. Busqueda Lineal");
        System.out.println("2. Busqueda Binaria");
        System.out.println("3. Busqueda Hash");
        System.out.print("Seleccione opcion: ");
        option = scanner.nextInt();

        System.out.println("\nSeleccione tamaño del arreglo:");
        for (int i = 0; i < 7; i++) {
            System.out.println((i + 1) + ". " + sizes[i] + " elementos");
        }

        System.out.print("Opcion: ");
        sizeOption = scanner.nextInt();

        if (sizeOption < 1 || sizeOption > 7) {
            System.out.println("Opcion invalida");
            scanner.close();
            return;
        }

        n = sizes[sizeOption - 1];

        arr = new int[n];

        generateArray(arr, n);

        target = n - 1;   /* Peor caso */

        long startTime, endTime;
        double cpu_time;

        if (option == 1) {
            startTime = System.nanoTime();
            linearSearch(arr, n, target);
            endTime = System.nanoTime();

        } else if (option == 2) {
            startTime = System.nanoTime();
            binarySearch(arr, n, target);
            endTime = System.nanoTime();

        } else if (option == 3) {
            for (int i = 0; i < HASH_SIZE; i++)
                hashTable[i] = null;

            for (int i = 0; i < n; i++)
                insertHash(arr[i]);

            startTime = System.nanoTime();
            searchHash(target);
            endTime = System.nanoTime();

            freeHash();

        } else {
            System.out.println("Opcion invalida");
            scanner.close();
            return;
        }

        cpu_time = (endTime - startTime) / 1_000_000_000.0;

        System.out.println("\nTiempo de ejecucion: " + cpu_time + " segundos");
        System.out.printf("Memoria usada por arreglo: %.2f MB%n",
                (n * 4.0) / (1024.0 * 1024.0));

        scanner.close();
    }
}