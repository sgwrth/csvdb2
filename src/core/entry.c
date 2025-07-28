#include <stdio.h>
#include <string.h>
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
