#include "hufftree.h"
#include "pqueue.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned short int  wbuffer[BUFFSIZE];

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
    int counter = 0, depth = 0;
    Table* meta_table = (Table*) malloc(sizeof(Table));
    meta_table->table = (TableData*) malloc(sizeof(TableData) * tree->nleafs_number);
    meta_table->size = tree->nleafs_number;
    if(recursive_table(tree->root, (meta_table->table), 0, &counter, &depth) == -1){
        fprintf(stderr, "Err: code table overflow\n");
        return NULL;
    }
    return meta_table;
}

// Funcao para cdificar cada elemento da tabela
int recursive_table(Node* root, TableData* table, int code, int *counter, int *depth) {
    if(pow(2, 32)-1 < code) {
        return -1;
    }
    if (root->left == NULL && root->right == NULL) {
        table[*counter].c = root->c;
        table[*counter].code_size = *depth;
        (*counter)++;
        return 0;
    }

    *depth = *depth + 1;
    if(recursive_table(root->left, table, (code << 1), counter, depth) == -1)
        return -1;
    if(recursive_table(root->right, table, ((code << 1) | 1), counter, depth) == -1)
        return -1;
    return 0;
}

// Funcao para printar a tabela
void print_table(Table* table){
    char *bitstr;
    for(int i=0; i<table->size; i++){
        fprintf(stdout, "%c : ", table->table[i].c); 
        bitstr = intToBinstr(table->table[i].code);
        /*for(int j=0; j<32; j++) {
            fprintf(stdout, "%c", bitstr[j]);
        }*/
    }
}

/*
// Função para
int encode(FILE* fp_in, FILE* fp_out, Table* table) {
    char caractere;
    unsigned short int aux=0;

    int bits_counter = 0;

	rewind(fp_in);
	while ((caractere = fgetc(fp_in)) != EOF) {
		
        for (int i = 0; i < table->size; i++) {
			if (table->table[i].c == caractere) {
                bits_counter += table->table[i].code_size;
                if(bits_counter >= sizeof(unsigned short int)){
                    
                } else {
                    //aux = aux << (table->table[i].code_size);
                }
                
				//fputs(table->table[i].code, fp_out);
			}
		}

	}
}
*/