#include <stdio.h>
#include <stdlib.h>

// Funcao para converter um valor int em binstr -> string no formato bin do int
char* intToBinstr(int num) {
    // Determina o número de bits do int
    int size = sizeof(num) * 8; 
    
    char* binstr = (char*) malloc(size);

    for (int i = size - 1; i >= 0; i--) {
        // Obtem o i-esimo bit do int e converte para string
        sprintf(binstr+size-i-1, "%d", (num >> i) & 1); 
    }
    binstr[size] = '\0';
    return binstr;
}