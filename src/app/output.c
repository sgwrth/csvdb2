#include "../app/messages.h"
#include "../core/entry.h"
#include <stdio.h>
#include <stdlib.h>
#include "./output.h"

void print_entries(Entry *entry)
{
	if (entry != NULL) {
		printf(TABLE_HEADER);
		printf(TABLE_HRLINE);
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
	printf(TABLE_HEADER);
	printf(TABLE_HRLINE);
	printf("%-25s|", entry->name);
	printf("%-25s|", entry->phonenumber);
	printf("%6d\n", entry->year_of_birth);
	printf("\n");
}
