#ifndef FILE_H
#define FILE_H
#include "../core/entry.h"
#include <stdio.h>

void write_to_file(Entry*);
void write_all_to_file(Entry*);
FILE *open_file();
int read_from_file(Entry**);

#endif
