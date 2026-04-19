#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#define TABLE_SIZE 2000
#define MAX_ID 50

typedef struct Node {
    char transaction_id[MAX_ID];
    struct Node* next;
} Node;

Node* hashTable[TABLE_SIZE] = {NULL};

int hash(char* str) {
    int sum = 0;
    for (int i = 0; str[i]; i++) {
        sum += str[i];
    }
    return sum % TABLE_SIZE;
}

int exists(char* id) {
    int index = hash(id);
    Node* temp = hashTable[index];

    while (temp) {
        if (strcmp(temp->transaction_id, id) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void insert(char* id) {
    int index = hash(id);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->transaction_id, id);
    newNode->next = hashTable[index];

    hashTable[index] = newNode;
}

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* data = (char*)malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';

    fclose(file);
    return data;
}

void processJSON(const char* filename) {
    char* jsonData = readFile(filename);
    if (!jsonData) {
        printf("Error leyendo archivo\n");
        return;
    }

    cJSON* root = cJSON_Parse(jsonData);
    if (!root) {
        printf("Error parseando JSON\n");
        free(jsonData);
        return;
    }

    FILE* out = fopen("ResultadoSinDuplicados.json", "w");
    if (!out) {
        printf("Error creando archivo de salida\n");
        cJSON_Delete(root);
        free(jsonData);
        return;
    }

    fprintf(out, "[\n");

    int size = cJSON_GetArraySize(root);
    int first = 1; // para controlar comas

    for (int i = 0; i < size; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);

        cJSON* idItem = cJSON_GetObjectItem(item, "transaction_id");
        cJSON* amountItem = cJSON_GetObjectItem(item, "amount");

        if (!idItem || !amountItem) continue;

        char* id = idItem->valuestring;
        int amount = amountItem->valueint;

        if (!exists(id)) {
            insert(id);

            if (!first) {
                fprintf(out, ",\n");
            }

            fprintf(out,
                "    {\"transaction_id\": \"%s\", \"amount\": %d}",
                id, amount
            );

            first = 0;
        }
    }

    fprintf(out, "\n]\n");

    fclose(out);
    cJSON_Delete(root);
    free(jsonData);

    printf("Archivo generado: ResultadoSinDuplicados.json\n");
}

int main() {
    processJSON("transaction_data.json");
    return 0;
}