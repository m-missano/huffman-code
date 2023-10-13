#ifndef HTREE_H
#define HTREE_H

typedef struct S_Node {
    struct S_Node *left;
    struct S_Node *right;
    char c;
    int freq;
} Node;

typedef struct S_Tree {
    Node *root;
    int nleafs_number;
} Tree;

typedef struct S_Table {
    char c;
    int code;
} Table;


Tree* create_tree(int* frequencies, int size);
Node* create_node(int freq, char c, Node *left, Node *right);
void inorder_traversal(Node* root);
void deallocate_tree(Tree* tree);
void deallocate_node(Node* root);

Table* create_table(Tree* tree);
int recursive_table(Node* root, Table* table, int code, int *counter);
void print_table(Table* table, int tabsize);

#endif