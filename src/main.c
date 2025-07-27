#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./app/db.h"
#include "./enums/enums.h"
#include "./utils/buf.h"

#define NAME_LEN 25
#define PHONENUMBER_LEN 25
#define YEAR_OF_BIRTH_LEN 4

/*
enum Db {
	OPEN = 'o',
	NEW = 'n'
};

enum Option {
	ADD_NEW_ENTRY = '1',
	SHOW_ALL_ENTRIES = '2',
	EDIT_ENTRY = '3',
	SAVE_AND_QUIT = '0'
};

enum Open_file {
	UNDEFINED = 'u',
	TRY_AGAIN = 't',
	CREATE_NEW = 'c',
	QUIT = 'q'
};

enum Insert_pos {
	AT_FRONT = 'f',
	AT_BACK = 'b'
};
*/

typedef struct Entry_struct Entry;
struct Entry_struct {
	char name[NAME_LEN];
	char phonenumber[PHONENUMBER_LEN];
	int year_of_birth;
	Entry *next;
};

// char decide_on_db();
char pick_opt(Entry**);
void exec_opt(char, Entry**);
// void clr_buf(FILE*);
int is_set_name(Entry*);
int is_set_phonenumber(Entry*);
int is_set_year_of_birth(Entry*);
void ask_if_enter_new_val(char*, char*);
void set_name(Entry*);
void set_phonenumber(Entry*);
void set_year_of_birth(Entry*);
void set_entry_data(Entry*);
char enter_another();
void insert_at_front(Entry**);
void insert_at_back(Entry**);
void print_entries(Entry*);
void print_entry(Entry*);
enum Insert_pos get_insert_pos();
int get_num_of_inserts();
void insert_entry(Entry**);
char *enter_search_name();
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

/*
char decide_on_db()
{
	char open_or_new_db;
	do {
		printf("[O]pen DB or create [n]ew?  Please enter: ");
		scanf("%c", &open_or_new_db);
		clr_buf(stdin);
	} while (open_or_new_db != OPEN && open_or_new_db != NEW);
	return open_or_new_db;
}
*/

char pick_opt(Entry **begin)
{
	char option;
	do {
		printf("***\n");
		printf("MENU\n");
		printf("What do you want to do?\n");
		printf("[1] Add new entry\n");
		if (*begin != NULL) {
			printf("[2] Show all entries\n");
			printf("[3] Edit entry\n");
			printf("[0] Save and quit\n");
		} else
			printf("[0] Quit\n");
		printf("Please enter: ");
		scanf("%c", &option);
		clr_buf(stdin);
	} while (option != ADD_NEW_ENTRY
			&& option != SHOW_ALL_ENTRIES
			&& option != EDIT_ENTRY
			&& option != SAVE_AND_QUIT
	);
	return option;
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

// void clr_buf(FILE *fp) {
// 	int ch;
// 	while ((ch = fgetc(fp)) != EOF && ch != '\n')
// 		/* Do nothing. */ ;
// }

int is_set_name(Entry *entry)
{
	int is_set = 0;
	if ((strncmp(entry->name, "[undefined]", sizeof("[undefined]")) != 0))
		is_set = 1;
	return is_set;
}

int is_set_phonenumber(Entry *entry)
{
	int is_set = 0;
	if ((strncmp(entry->phonenumber, "[undefined]", sizeof("[undefined]")) != 0))
		is_set = 1;
	return is_set;
}

int is_set_year_of_birth(Entry *entry)
{
	int is_set = 0;
	if (entry->year_of_birth != 0)
		is_set = 1;
	return is_set;
}

void ask_if_enter_new_val(char *name_of_val, char *edit_yes_no)
{
	do {
		printf("Do you want to enter a new %s?  [Y]es or [n]o: ", name_of_val);
		scanf("%c", edit_yes_no);
		clr_buf(stdin);
	} while (*edit_yes_no != 'y' && *edit_yes_no != 'n');
}

void set_name(Entry *entry)
{
	int is_set = is_set_name(entry);
	if (is_set == 1) {
		printf("Current name: %s\n", entry->name);
		char edit_yes_no;
		char *name_of_val = malloc(sizeof("name"));
		strcpy(name_of_val, "name");
		ask_if_enter_new_val(name_of_val, &edit_yes_no);
		free(name_of_val);
		if (edit_yes_no == 'y') {
			printf("Please enter name: ");
			fgets(entry->name, sizeof(entry->name), stdin);
			entry->name[strcspn(entry->name, "\n")] = 0;
		}
	} else {
		printf("Please enter name: ");
		fgets(entry->name, sizeof(entry->name), stdin);
		entry->name[strcspn(entry->name, "\n")] = 0;
	}
}

void set_phonenumber(Entry *entry)
{
	int is_set = is_set_phonenumber(entry);
	if (is_set == 1) {
		printf("Current phonenumber: %s\n", entry->phonenumber);
		char edit_yes_no;
		char *name_of_val = malloc(sizeof("phonenumber"));
		strcpy(name_of_val, "phonenumber");
		ask_if_enter_new_val(name_of_val, &edit_yes_no);
		free(name_of_val);
		if (edit_yes_no == 'y') {
			printf("Please enter phonenumber: ");
			fgets(entry->phonenumber, sizeof(entry->phonenumber), stdin);
			entry->phonenumber[strcspn(entry->phonenumber, "\n")] = 0;
		}
	} else {
		printf("Please enter phonenumber: ");
		fgets(entry->phonenumber, sizeof(entry->phonenumber), stdin);
		entry->phonenumber[strcspn(entry->phonenumber, "\n")] = 0;
	}
}

void set_year_of_birth(Entry *entry)
{
	int is_set = is_set_year_of_birth(entry);
	if (is_set == 1) {
		printf("Current year of birth: %d\n", entry->year_of_birth);
		char edit_yes_no;
		do {
			printf("Do you want to enter a new year of birth?  [Y]es or [n]o: ");
			scanf("%c", &edit_yes_no);
			clr_buf(stdin);
		} while (edit_yes_no != 'y' && edit_yes_no != 'n');
		if (edit_yes_no == 'y') {
			int year_of_birth;
			printf("Please enter year of birth: ");
			scanf("%d", &year_of_birth);
			clr_buf(stdin);
			entry->year_of_birth = year_of_birth;
		}
	} else {
		int year_of_birth;
		printf("Please enter year of birth: ");
		scanf("%d", &year_of_birth);
		clr_buf(stdin);
		entry->year_of_birth = year_of_birth;
	}
}

void set_entry_data(Entry *entry)
{
	set_name(entry);
	set_phonenumber(entry);
	set_year_of_birth(entry);
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
	if (pos == AT_FRONT ) {
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

char *enter_search_name()
{
	char *search_str = malloc(NAME_LEN);
	printf("Enter search name: ");
	fgets(search_str, NAME_LEN, stdin);
	
	char *temp_str = malloc(NAME_LEN);    /* Delete '\n' at end of string. */
	memset(temp_str, 0, NAME_LEN);        /* Remove garbage values in temp_str. */
	strncpy(temp_str, search_str, strlen(search_str) - 1);

	free(search_str);
	return temp_str;
}

Entry *select_entry(Entry *entry)
{
	Entry *selector = entry;
	char *search_name = enter_search_name();
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
		printf("no matching entry found.\n");
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
		if (try_again_or_quit == CREATE_NEW)
			return NULL;
		else if (try_again_or_quit == QUIT)
			exit(0);
		fp = fopen(get_filename(), "r");
	}
	return fp;
}

int read_from_file(Entry **begin)
{
	FILE *fp = open_file();
	if (fp == NULL)
		return 0;
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
		char phonenumber[PHONENUMBER_LEN];
		write_chars_to_val(array_from_chars_to_line, phonenumber, &j);
		char year_of_birth[YEAR_OF_BIRTH_LEN];
		write_chars_to_val(array_from_chars_to_line, year_of_birth, &j);

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
	while (chars[*j] != ',' && chars[*j] != '\0') {
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
	if (edit_this != NULL)
		set_entry_data(edit_this);
	else
		printf("No matching entry found.\n");
}
