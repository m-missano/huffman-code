#include "pqueue.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar uma nova fila de prioridade vazia
PQueue* createPriorityQueue() {
    PQueue* pqueue = (PQueue*)malloc(sizeof(PQueue));
    pqueue->element = NULL;
    return pqueue;
}

// Função para verificar se a fila de prioridade está vazia
int isEmpty(PQueue* pqueue) {
    return (pqueue->element == NULL);
}

// Função para inserir um elemento na fila de prioridade
void enqueue(PQueue* pqueue, Node* data, int priority) {
    QElement* new_element = (QElement*)malloc(sizeof(QElement));
    new_element->data = data;
    new_element->priority = priority;
    new_element->next = NULL;
    

    if (isEmpty(pqueue) || priority < pqueue->element->priority) {
        new_element->next = pqueue->element;
        pqueue->element = new_element;
    } else {
        QElement* current = pqueue->element;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        new_element->next = current->next;
        current->next = new_element;
    }
}

// Função para remover e retornar o elemento de maior prioridade da fila de prioridade
Node* dequeue(PQueue* pqueue) {
    if (isEmpty(pqueue)) {
        printf("A fila de prioridade está vazia.\n");
        return NULL;
    }

    Node* data = pqueue->element->data;
    QElement* temp = pqueue->element;
    pqueue->element = pqueue->element->next;
    free(temp);

    return data;
}