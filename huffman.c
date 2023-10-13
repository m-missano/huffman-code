#include "hufftree.h"
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 257

int alphabet[ALPHABET_SIZE] = {0};

void ler_arquivo(char file_name[256]) {
	char caractere;
	FILE *inputFile = fopen(file_name, "r");
	if (inputFile != NULL) {
		while ((caractere = fgetc(inputFile)) != EOF) {
				++alphabet[caractere];
		}
	}
}

int main(int argc, char *argv[]) {
	char file_name[256];
	if (argc == 2) {
		ler_arquivo(argv[1]);
	}
	else {
		printf("Erro: Forneça o nome do arquivo como argumento.\n");
		return 1; // Retorne um codigo de erro
	}
    Tree *tree = create_tree(alphabet, ALPHABET_SIZE);
    Table *table = create_table(tree);
    print_table(table, tree->nleafs_number);
    deallocate_tree(tree);
}
