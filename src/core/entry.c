#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../app/output.h"
#include "../core/file.h"
#include "../core/input.h"
#include "../utils/buf.h"
#include "./entry.h"

int is_set_name(Entry *entry)
{
	if ((strncmp(entry->name, "[undefined]", sizeof("[undefined]")) != 0)) {
		return 1;
    }
	return 0;
}

int is_set_phonenumber(Entry *entry)
{
	if ((strncmp(entry->phonenumber, "[undefined]", sizeof("[undefined]")) != 0)) {
		return 1;
    }
	return 0;
}

int is_set_year_of_birth(Entry *entry)
{
	if (entry->year_of_birth != 0) {
		return 1;
    }
	return 0;
}

void set_name(Entry *entry)
{
	int is_set = is_set_name(entry);
	if (is_set == 1) {
		printf("Current name: %s\n", entry->name);
        char *name_of_val = "name";
		char edit_yes_no = ask_if_enter_new_val(name_of_val);
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
		char *name_of_val = "phonenumber";
		char edit_yes_no = ask_if_enter_new_val(name_of_val);
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
