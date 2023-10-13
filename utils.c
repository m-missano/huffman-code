#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hufftree.h"

// Funcao para converter um valor int em binstr -> string no formato bin do int
char *intToBinstr(int num)
{
    // Determina o número de bits do int
    int size = sizeof(num) * 8;

    char *binstr = (char *)malloc(size);

    for (int i = size - 1; i >= 0; i--)
    {
        // Obtem o i-esimo bit do int e converte para string
        sprintf(binstr + size - i - 1, "%d", (num >> i) & 1);
    }
    binstr[size] = '\0';
    return binstr;
}

void write_char_on_file(FILE *fout, FILE *fin, Table *tab)
{
    char caractere,c;
    int cont = 0;
    int k = 0;
    rewind(fin);
    while ((caractere = fgetc(fin)) != EOF)
    {
        for (int i = 0; i < tab->size; i++)
            if (caractere == tab->table[i].c)
            {
                char *code = intToBinstr(tab->table[i].code);
                for (int i = 0; i < strlen(code); i++)
                {
                    if (code[i] == '1')
                        c = c | (1 << (7 - k)); // shifts 1 to relevant position and OR with the temporary char
                    else if (code[i] == '0')
                        c = c | (0 << (7 - k)); // shifts 0 to relevant position and OR with the temporary char
                    k++;
                }
            }
        if((cont+1)%8 == 0){
            k=0;
            fputc(c,fout);
            c=0;
        }
        cont++;
    }
}