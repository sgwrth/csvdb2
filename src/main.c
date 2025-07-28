#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./app/db.h"
#include "./core/entry.h"
#include "./core/input.h"
#include "./const/constants.h"
#include "./enums/enums.h"
#include "./utils/buf.h"

void exec_opt(char, Entry**);
char enter_another();
void insert_at_front(Entry**);
void insert_at_back(Entry**);
void print_entries(Entry*);
void print_entry(Entry*);
enum Insert_pos get_insert_pos();
int get_num_of_inserts();
void insert_entry(Entry**);
Entry *select_entry(Entry*);
char *get_filename();
void write_to_file(Entry*); 
void write_all_to_file(Entry*);
FILE *open_file();
int read_from_file(Entry**);
void write_chars_to_val(char[], char[], int*);
void edit_entry(Entry**);

int main()
{
	Entry *begin = NULL;
	enum Db open_or_new_db = decide_on_db();
	if (open_or_new_db == OPEN)
		read_from_file(&begin);
	char option;
	do {
		option = pick_opt(&begin);
		exec_opt(option, &begin);
	} while (option != SAVE_AND_QUIT );
	return 0;
}

void exec_opt(char option, Entry **begin)
{
	switch (option) {
		case ADD_NEW_ENTRY:
			insert_entry(begin);
			break;
		case SHOW_ALL_ENTRIES:
			print_entries(*begin);
			break;
		case EDIT_ENTRY:
			edit_entry(begin);
			break;
		case SAVE_AND_QUIT:
			write_all_to_file(*begin);
			break;
	}
}

void insert_at_front(Entry **begin)
{
	Entry *temp = malloc(sizeof(Entry));
	set_entry_data(temp);
	temp->next = *begin;
	*begin = temp;
}

void insert_at_back(Entry **begin)
{
	Entry *new = malloc(sizeof(Entry));
	strncpy(new->name, "[undefined]", NAME_LEN);
	strncpy(new->phonenumber, "[undefined]", PHONENUMBER_LEN);
	new->year_of_birth = 0;
	Entry *helper;
	helper = *begin;
	if (*begin == NULL)
		*begin = new;
	else {
		while (helper->next != NULL)
			helper = helper->next;
		helper->next = new;
	}
	set_entry_data(new);
	new->next = NULL;
}

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

enum Insert_pos get_insert_pos()
{
	char pos;
	do {
		printf("Insert at [f]ront or [b]ack?  Please enter: ");
		scanf("%c", &pos);
		clr_buf(stdin);
	} while (pos != 'f' && pos != 'b');
	if (pos == 'f')
		return AT_FRONT;
	return AT_BACK;
}

char enter_another()
{
	char another_entry;
	do {
		printf("Do you want to add another entry?  [Y]es or [n]o: ");
		scanf("%c", &another_entry);
		clr_buf(stdin);
	} while (another_entry != 'y' && another_entry != 'n');
	return another_entry;
}

void insert_entry(Entry **entry)
{
	enum Insert_pos pos = get_insert_pos();
	char another_entry = 'u';
	if (pos == AT_FRONT) {
		do {
			printf("### Enter Contact\n");
			insert_at_front(entry);
			another_entry = enter_another();
		} while (another_entry != 'n');
	} else {
		do {
			printf("### Enter Contact\n");
			insert_at_back(entry);
			another_entry = enter_another();
		} while (another_entry != 'n');
	}
}

Entry *select_entry(Entry *entry)
{
	printf("Enter search name: ");
	char *search_name = enter_search_name();
	Entry *selector = entry;
	while (strcmp(selector->name, search_name) != 0) {
		if (selector->next == NULL) {
			return NULL;
		}
		selector = selector->next;
	}
	return selector;
}

char *get_filename()
{
	char *filename = malloc(12);
	printf("Enter filename (max. 12 characters): ");
	scanf("%s", filename);
	clr_buf(stdin);
	return filename;
}

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
	char array_from_chars[BUFSIZ];
	int i = 0;
	while ((ch = fgetc(fp)) != EOF) {
		array_from_chars[i] = ch;
		i++;
	}
	printf("%s", array_from_chars);

	int m = 0;
	do {
        /* Read each line of CSV content. */
		char array_from_chars_to_line[BUFSIZ];
		memset(array_from_chars_to_line, 0, BUFSIZ);
		int n = 0;
		while ((ch = array_from_chars[m]) && ch != '\n') {
			array_from_chars_to_line[n] = ch;
			m++;
			n++;
		}
		m++;        /* At end of line: go to next line. */
		int j = 0;  /* Starting pos of array_from_chars_to_line to read from. */

        /* Parse the contents of each line to individual values. */
		char name[NAME_LEN];
		write_chars_to_val(array_from_chars_to_line, name, &j);
        printf("j after name: %d\n", j);
		char phonenumber[PHONENUMBER_LEN];
		write_chars_to_val(array_from_chars_to_line, phonenumber, &j);
        printf("j after phonenumber: %d\n", j);
		char year_of_birth[YEAR_OF_BIRTH_LEN];
		write_chars_to_val(array_from_chars_to_line, year_of_birth, &j);
        printf("j after y.o.b.: %d\n", j);

        printf("name: %s\n", name);
        printf("phonenumber: %s\n", phonenumber);
        printf("y.o.b.: %s\n", year_of_birth);

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
	} while (array_from_chars[m] != '\0');
	fclose(fp);
	return 0;
}

void write_chars_to_val(char chars[], char value[], int *j)
{
	int k = 0;
	// while (chars[*j] != ',' && chars[*j] != '\0') {
	while (chars[*j] != ',' && chars[*j] != '\0') {
        if (chars[*j] == '\n') {
            return;
        }
		if (chars[*j] != '"') {
			value[k] = chars[*j];
			k++;
		}
		*j += 1;
	}
	*j += 1; /* Pos for next value to be read from array_from_chars. */
}

void edit_entry(Entry **entry)
{
	Entry *edit_this = select_entry(*entry);
	if (edit_this != NULL) {
		set_entry_data(edit_this);
    } else {
		printf("No matching entry found.\n");
    }
}
