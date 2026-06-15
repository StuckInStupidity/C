#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHGROUPS 10

typedef struct Node {
    int key;
    char *value;
    struct Node *next;
} Node;

typedef struct {
    Node *table[HASHGROUPS];
} Hashtable;

void initHashtable(Hashtable *ht) {
    for (int i = 0; i < HASHGROUPS; i++) ht->table[i] = NULL;
}

int isEmpty(const Hashtable *ht) {
    for (int i = 0; i < HASHGROUPS; i++) if (ht->table[i] != NULL) return 0;
    return 1;
}

int hashFunction(int key) {
    return key % HASHGROUPS;
}

void insertItem(Hashtable *ht, int key, const char *value) {
    int hashValue = hashFunction(key);
    Node *current = ht->table[hashValue];
    while (current) {
        if (current->key == key) {
            free(current->value);
            current->value = malloc(strlen(value) + 1);
            strcpy(current->value, value);
            printf("[WARNING] Key exists. Value replaced.\n");
            return;
        }
        current = current->next;
    }
    Node *newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = malloc(strlen(value) + 1);
    strcpy(newNode->value, value);
    newNode->next = ht->table[hashValue];
    ht->table[hashValue] = newNode;
}

void removeItem(Hashtable *ht, int key) {
    int hashValue = hashFunction(key);
    Node *current = ht->table[hashValue];
    Node *prev = NULL;
    while (current) {
        if (current->key == key) {
            if (prev) prev->next = current->next;
            else ht->table[hashValue] = current->next;
            free(current->value);
            free(current);
            printf("[INFO] Key removed.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("[INFO] Key not found.\n");
}

void printTable(const Hashtable *ht) {
    for (int i = 0; i < HASHGROUPS; i++) {
        Node *current = ht->table[i];
        while (current) {
            printf("[INFO] Key : %d  Value : %s\n", current->key, current->value);
            current = current->next;
        }
    }
}

void freeHashtable(Hashtable *ht) {
    for (int i = 0; i < HASHGROUPS; i++) {
        Node *current = ht->table[i];
        while (current) {
            Node *tmp = current;
            current = current->next;
            free(tmp->value);
            free(tmp);
        }
        ht->table[i] = NULL;
    }
}

int main(void) {
    Hashtable hT;
    initHashtable(&hT);
  
    if (isEmpty(&hT)) printf("Empty.\n");
    else printf("Not empty.\n");

    insertItem(&hT, 905, "M");
    insertItem(&hT, 305, "I");
    insertItem(&hT, 201, "T");
    insertItem(&hT, 107, "T");
    printTable(&hT);
    insertItem(&hT, 107, "S");
    removeItem(&hT, 305);
    removeItem(&hT, 929);
    printTable(&hT);
  
    if (isEmpty(&hT)) printf("Empty.\n");
    else printf("Not empty.\n");

    freeHashtable(&hT);
    return 0;
}
