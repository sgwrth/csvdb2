#include "../core/entry.h"
#include "../core/input.h"
#include "../utils/buf.h"
#include "../utils/csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./file.h"

void write_to_file(Entry *entry)
{
	Entry *selected = select_entry(entry);
	if (selected != NULL) {
		FILE *fp = fopen(get_filename(), "a");
		fprintf(fp, "\"%s\"", selected->name);
		fprintf(fp, ",");
		fprintf(fp, "\"%s\"", selected->phonenumber);
		fprintf(fp, ",");
		fprintf(fp, "%d", selected->year_of_birth);
		fprintf(fp, "\n");
		fclose(fp);
	} else
		printf("No matching entry found.\n");
}

void write_all_to_file(Entry *entry)
{
	Entry *selected = entry;
	if (selected != NULL) {
		FILE *fp = fopen(get_filename(), "w");
		do {
			fprintf(fp, "\"%s\"", selected->name);
			fprintf(fp, ",");
			fprintf(fp, "\"%s\"", selected->phonenumber);
			fprintf(fp, ",");
			fprintf(fp, "\"%d\"", selected->year_of_birth);
			fprintf(fp, "\n");
			selected = selected->next;
		} while (selected != NULL); 
	fclose(fp);
	}
}

FILE *open_file()
{	
	FILE *fp = fopen(get_filename(), "r");
	while (fp == NULL) {
		printf("error: file not found\n");
		char try_again_or_quit = UNDEFINED;
		while (try_again_or_quit != TRY_AGAIN
				&& try_again_or_quit != CREATE_NEW
				&& try_again_or_quit != QUIT) {
			printf("[T]ry again\n"),
			printf("[C]reate a new db\n");
			printf("[Q]uit the program?\n");
			printf("Enter: ");
			scanf("%c", &try_again_or_quit);
			clr_buf(stdin);
		}
		if (try_again_or_quit == CREATE_NEW) {
			return NULL;
        } else if (try_again_or_quit == QUIT) {
			exit(0);
        }
		fp = fopen(get_filename(), "r");
	}
	return fp;
}

int read_from_file(Entry **begin)
{
	FILE *fp = open_file();
	if (fp == NULL) {
		return 0;
    }
	char ch;
	char csv_as_single_str[BUFSIZ];
	int i = 0;
	while ((ch = fgetc(fp)) != EOF) {
		csv_as_single_str[i] = ch;
		i++;
	}
	printf("%s", csv_as_single_str);

	int m = 0;
	do {
        /* Read each line of CSV content. */
		char csv_line[BUFSIZ];
		memset(csv_line, 0, BUFSIZ);
		int n = 0;
		while ((ch = csv_as_single_str[m]) && ch != '\n') {
			csv_line[n] = ch;
			m++;
			n++;
		}
		m++;        /* At end of line: go to next line. */
		int j = 0;  /* Starting pos of csv_line to read from. */

        /* Parse the contents of each line to individual values. */
		char name[NAME_LEN];
		parse_entry_val_from_slice(csv_line, name, &j);
		char phonenumber[PHONENUMBER_LEN];
		parse_entry_val_from_slice(csv_line, phonenumber, &j);
		char year_of_birth[YEAR_OF_BIRTH_LEN];
		parse_entry_val_from_slice(csv_line, year_of_birth, &j);

        /* Create new entry from parsed values. */
		Entry *new_node = malloc(sizeof(Entry));
		strncpy(new_node->name, name, NAME_LEN);
		strncpy(new_node->phonenumber, phonenumber, PHONENUMBER_LEN);
		int temp = atoi(year_of_birth);
		new_node->year_of_birth = temp;

        /* Clear values. */
		memset(name, 0, NAME_LEN);
		memset(phonenumber, 0, PHONENUMBER_LEN);
		memset(year_of_birth, 0, YEAR_OF_BIRTH_LEN);

		new_node->next = *begin;
		*begin = new_node;
	} while (csv_as_single_str[m] != '\0');
	fclose(fp);
	return 0;
}
