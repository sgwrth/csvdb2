#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./app/db.h"
#include "./core/entry.h"
#include "./core/file.h"
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
int read_from_file(Entry**);
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

void edit_entry(Entry **entry)
{
	Entry *edit_this = select_entry(*entry);
	if (edit_this != NULL) {
		set_entry_data(edit_this);
    } else {
		printf("No matching entry found.\n");
    }
}
