#include "hufftree.h"
#include "utils.h"
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
    
	
	FILE* fin= fopen(argv[1],"r");
	FILE* fout= fopen("output.huffman","w");
	Tree *tree = create_tree(alphabet, ALPHABET_SIZE);
    Table *table = create_table(tree);
    print_table(table);
	write_char_on_file(fout,fin,table);
    deallocate_tree(tree);
}
