#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t dataSize;
} List;

void initList(List* list, size_t dataSize) {
    list->head = NULL;
    list->dataSize = dataSize;
}

Node* createNode(void* data, size_t dataSize) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = malloc(dataSize);
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;
    return newNode;
}

void add(List* list, void* data) {
    Node* newNode = createNode(data, list->dataSize);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* aux = list->head;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}

int removeNode(List* list, void* data) {
    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL && memcmp(temp->data, data, list->dataSize) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Data not found\n");
        return 0;
    }

    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp->data); 
    free(temp);        

    return 1;
}

int exist(List* list, void* data) {
    Node* aux = list->head;
    while (aux != NULL) {
        if (memcmp(aux->data, data, list->dataSize) == 0) {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int isEmpty(List* list){
    if (list->head == NULL)
    {
        printf("La lista esta vacia\n");
        return 1;
    }else{
        printf("La lista no esta vacia\n");
        return 0;
    }
    
}

void print_data(void* data, char type) {
    switch (type) {
        case 'i':
            printf("%d", *(int*)data);
            break;
        case 'f':
            printf("%f", *(float*)data);
            break;
        case 'c':
            printf("%c", *(char*)data);
            break;
        case 's':
            printf("%s", (char*)data);
            break;
        default:
            printf("Tipo no soportado");
            break;
    }
}

void print_list(Node* head, char type) {
    Node* temp = head;
    int count = 0;

    while (temp != NULL) {
        printf("Elemento %d es: ", count);
        print_data(temp->data, type);
        printf("\n");
        temp = temp->next;
        count++;
    }
}

void releaseList(List* list) {
    Node* aux = list->head;
    while (aux != NULL) {
        Node* temp = aux;
        aux = aux->next;
        free(temp->data); 
        free(temp);     
    }
    list->head = NULL;
}

int main() {
    List list;
    initList(&list, sizeof(int));

    isEmpty(&list);

    int val1 = 120;
    int val2 = 34;
    int val3 = 421;
    add(&list, &val1);
    add(&list, &val2);
    add(&list, &val3);

    printf("Lista antes de eliminar:\n");
    print_list(list.head, 'i');

    removeNode(&list, &val2);

    printf("Lista despues de eliminar:\n");
    print_list(list.head, 'i');

    isEmpty(&list);

    int search = 421;
    if (exist(&list, &search)) {
        printf("El dato %i existe en la lista\n", search);
    } else {
        printf("El dato %i no existe en la lista\n", search);
    }

    releaseList(&list);

    return 0;
}