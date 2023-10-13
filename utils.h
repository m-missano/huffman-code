#ifndef UTILS_H
#define UTILS_H
#include "hufftree.h"
#include <stdio.h>
char* intToBinstr(int num, int size);
void write_char_on_file(FILE* fout, FILE* fin,Table* tab);

#endif