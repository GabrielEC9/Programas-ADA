import time
import random

def max_cruce(A, izq, mid, der):
    suma = 0
    mejor_izq = float('-inf')

    for i in range(mid, izq - 1, -1):
        suma += A[i]
        if suma > mejor_izq:
            mejor_izq = suma

    suma = 0
    mejor_der = float('-inf')

    for i in range(mid + 1, der + 1):
        suma += A[i]
        if suma > mejor_der:
            mejor_der = suma

    return mejor_izq + mejor_der


def max_subarreglo(A, izq, der):
    if izq == der:
        return A[izq]

    mid = (izq + der) // 2

    izquierda = max_subarreglo(A, izq, mid)
    derecha = max_subarreglo(A, mid + 1, der)
    cruce = max_cruce(A, izq, mid, der)

    return max(izquierda, derecha, cruce)


def resolver_archivo():
    try:
        with open("casos.txt", "r", encoding="utf-8") as archivo:
            lineas = [linea.strip() for linea in archivo if linea.strip()]

        t = int(lineas[0])

        for caso in range(1, t + 1):
            datos = list(map(int, lineas[caso].split()))
            n = datos[0]
            A = datos[1:]

            inicio = time.time()
            resultado = max_subarreglo(A, 0, n - 1)
            fin = time.time()

            print(f"\nCaso {caso}:")
            print(A)
            print(f"Suma maxima = {resultado}")
            print(f"Tiempo = {fin - inicio:.6f} segundos")

    except FileNotFoundError:
        print("\nNo se encontro el archivo casos.txt\n")


def pruebas_grandes():
    tamanos = [10, 100, 1000, 10000]

    for n in tamanos:
        A = [random.randint(-100, 100) for _ in range(n)]

        inicio = time.time()
        resultado = max_subarreglo(A, 0, n - 1)
        fin = time.time()

        print(f"\nn = {n}")
        print(f"Suma maxima = {resultado}")
        print(f"Tiempo = {fin - inicio:.6f} segundos")


def menu():
    while True:
        print("\n===== MENU =====")
        print("1. Leer casos.txt")
        print("2. Pruebas grandes")
        print("3. Salir")

        op = input("Opcion: ")

        if op == "1":
            resolver_archivo()

        elif op == "2":
            pruebas_grandes()

        elif op == "3":
            print("Programa finalizado.")
            break

        else:
            print("Opcion invalida.")


menu()