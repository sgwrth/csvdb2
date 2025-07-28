#include "../core/entry.h"
#include <stdio.h>
#include <stdlib.h>
#include "./output.h"

void print_entries(Entry *entry)
{
	if (entry != NULL) {
		printf("NAME                     |PHONENUMBER              |Y.O.B.\n");
		printf("-------------------------|-------------------------|------\n");
		do {
			printf("%-25s|", entry->name);
			printf("%-25s|", entry->phonenumber);
			printf("%6d\n", entry->year_of_birth);
			entry = entry->next;
		}
		while (entry != NULL);
		printf("\n");
	}
}

void print_entry(Entry *entry)
{
	printf("NAME                     |PHONENUMBER              |Y.O.B.\n");
	printf("-------------------------|-------------------------|------\n");
	printf("%-25s|", entry->name);
	printf("%-25s|", entry->phonenumber);
	printf("%6d\n", entry->year_of_birth);
	printf("\n");
}
