#ifndef PQUEUE_H
#define PQUEUE_H

#include "hufftree.h"

typedef struct S_QElement {
    Node* data;
    int priority;
    struct S_QElement* next;
} QElement;

typedef struct s_PQueue {
    QElement* element;
} PQueue; 

PQueue* createPriorityQueue();
int isEmpty(PQueue* pqueue);
void enqueue(PQueue* pqueue, Node* data, int priority);
Node* dequeue(PQueue* pqueue);

#endif