#ifndef STRUCTS_H
#define STRUCTS_H
#include "../enums/enums.h"
#include "../const/constants.h"

typedef struct Entry_struct Entry;
struct Entry_struct {
	char name[NAME_LEN];
	char phonenumber[PHONENUMBER_LEN];
	int year_of_birth;
	Entry *next;
};

int is_set_name(Entry*);
int is_set_phonenumber(Entry*);
int is_set_year_of_birth(Entry*);
void set_name(Entry*);
void set_phonenumber(Entry*);
void set_year_of_birth(Entry*);
void set_entry_data(Entry*);

#endif
