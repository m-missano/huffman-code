#include "hufftree.h"
#include "pqueue.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funcao para criar a arvore de huffman
Tree* create_tree(int* frequencies, int size) {
    PQueue* pqueue = createPriorityQueue();
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->nleafs_number = 0;

    // Cria os nos folha
    for(int i=0; i<size; i++){
        if(frequencies[i] != 0){
            Node *item = create_node(frequencies[i], i, NULL, NULL);
            tree->nleafs_number++;
            enqueue(pqueue, item, frequencies[i]);
        }
    }

    // Cria o restante dos nos
    while (!isEmpty(pqueue)) {
        Node *left = dequeue(pqueue);
        Node *right = dequeue(pqueue);
        tree->root = create_node(0, '\0', left, right);
        if(!isEmpty(pqueue))
            enqueue(pqueue, tree->root, tree->root->freq);
    }
    free(pqueue);
    //read_inorder(tree->root);
    return tree;
}

// Funcao para criar o no da arvore
Node* create_node(int freq, char c, Node *left, Node *right) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    new_node->left = left;
    new_node->right = right;
    new_node->c = c;

    if(freq != 0)
        new_node->freq = freq;
    else {
        new_node->freq = left->freq + right->freq;
    }
    return new_node;   
}

// Função para percorrer a árvore em ordem (in-order)
void read_inorder(Node* root) {
    if (root != NULL) {
        read_inorder(root->left);
        printf("%c:%d ", root->c, root->freq);
        read_inorder(root->right);
    }
}

// Funcao para desalocar a arvore de huffman
void deallocate_tree(Tree* tree) {
   deallocate_node(tree->root);
   free(tree);
}

// Funcao para desalocar os nos da arvore de huffman
void deallocate_node(Node* root) {
    if (root == NULL) {
        return;
    }
    deallocate_node(root->left);
    deallocate_node(root->right);
    free(root);
}

// Função para criar a tabela
Table* create_table(Tree* tree) {
    int counter = 0;
    Table* meta_table = (Table*) malloc(sizeof(Table));
    meta_table->table = (TableData*) malloc(sizeof(TableData) * tree->nleafs_number);
    meta_table->size = tree->nleafs_number;
    if(recursive_table(tree->root, (meta_table->table), 1, &counter) == -1){
        fprintf(stderr, "Err: code table overflow\n");
        return NULL;
    }
    return meta_table;
}

// Funcao para cdificar cada elemento da tabela
int recursive_table(Node* root, TableData* table, int code, int *counter) {
    if(pow(2, 31) < code) {
        return -1;
    }
    if (root->left == NULL && root->right == NULL) {
        table[*counter].c = root->c;
        table[*counter].code = code;
        (*counter)++;
        return 0;
    }
    if(recursive_table(root->left, table, (code << 1), counter) == -1)
        return -1;
    if(recursive_table(root->right, table, ((code << 1) | 1), counter) == -1)
        return -1;
    return 0;
}

// Funcao para printar a tabela
void print_table(Table* table){
    for(int i=0; i<table->size; i++){
        fprintf(stdout, "%c : %s : %d", table->table[i].c, intToBinstr( table->table[i].code),  table->table[i].code);
        fprintf(stdout, " : %f\n", floor(log2( table->table[i].code)));
    }
}