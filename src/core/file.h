#ifndef FILE_H
#define FILE_H
#include "../core/entry.h"
#include <stdio.h>

void write_to_file(Entry*, char*);
void write_all_to_file(Entry*, char*);
FILE *open_file(char**);
int read_from_file(char**, Entry**);

#endif
