import heapq
from collections import Counter

class Nodo:
    def __init__(self, caracter, frecuencia):
        self.caracter = caracter
        self.frecuencia = frecuencia
        self.izquierda = None
        self.derecha = None

    def __lt__(self, otro):
        return self.frecuencia < otro.frecuencia

codigos = {}
texto_decodificado = ""

def construir_arbol(texto):
    frecuencias = Counter(texto)

    heap = []

    for caracter, frecuencia in frecuencias.items():
        heapq.heappush(heap, Nodo(caracter, frecuencia))

    while len(heap) > 1:
        izquierda = heapq.heappop(heap)
        derecha = heapq.heappop(heap)

        nuevo = Nodo(None, izquierda.frecuencia + derecha.frecuencia)

        nuevo.izquierda = izquierda
        nuevo.derecha = derecha

        heapq.heappush(heap, nuevo)

    return heap[0]

def generar_codigos(nodo, codigo=""):

    if nodo is None:
        return

    if nodo.caracter is not None:
        codigos[nodo.caracter] = codigo
        print(f"{repr(nodo.caracter)} : {codigo}")

    generar_codigos(nodo.izquierda, codigo + "0")
    generar_codigos(nodo.derecha, codigo + "1")

def codificar(texto):

    print("\n=== TEXTO CODIFICADO ===\n")

    bits = ""

    for caracter in texto:
        bits += codigos[caracter]

    print(bits)

    return bits

def decodificar(bits, raiz):

    global texto_decodificado

    actual = raiz

    print("\n=== TEXTO DECODIFICADO ===\n")

    for bit in bits:

        if bit == "0":
            actual = actual.izquierda
        else:
            actual = actual.derecha

        if actual.caracter is not None:
            print(actual.caracter, end="")
            texto_decodificado += actual.caracter
            actual = raiz

    print()

def guardar_arbol(nodo, espacio=0, archivo=None):

    if nodo is None:
        return

    espacio += 5

    guardar_arbol(nodo.derecha, espacio, archivo)

    archivo.write("\n")

    for _ in range(5, espacio):
        archivo.write(" ")

    if nodo.caracter is not None:
        archivo.write(f"{nodo.caracter}({nodo.frecuencia})\n")
    else:
        archivo.write(f"{nodo.frecuencia}\n")

    guardar_arbol(nodo.izquierda, espacio, archivo)

def main():

    with open("texto.txt", "r", encoding="utf-8") as archivo:
        texto = archivo.read()

    raiz = construir_arbol(texto)

    print("=== TABLA HUFFMAN ===\n")

    generar_codigos(raiz)

    with open("arbolp.txt", "w", encoding="utf-8") as archivo_arbol:
        guardar_arbol(raiz, 0, archivo_arbol)

    print("\n=== TEXTO ORIGINAL ===\n")
    print(texto)

    bits = codificar(texto)

    decodificar(bits, raiz)

    if texto == texto_decodificado:
        print("\nVERIFICACION EXITOSA")
    else:
        print("\nERROR EN DECODIFICACION")

if __name__ == "__main__":
    main()