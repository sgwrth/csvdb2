#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../app/menu.h"
#include "../enums/enums.h"
#include "../core/entry.h"
#include "../utils/buf.h"
#include "./input.h"

char pick_opt(Entry **begin)
{
	char option;
	do {
        print_main_menu(begin);
		scanf("%c", &option);
		clr_buf(stdin);
	} while (option != ADD_NEW_ENTRY
			&& option != SHOW_ALL_ENTRIES
			&& option != EDIT_ENTRY
			&& option != SAVE_AND_QUIT
	);
	return option;
}

char *enter_search_name()
{
	char *search_str = malloc(NAME_LEN);
	fgets(search_str, NAME_LEN, stdin);
	
	char *temp_str = malloc(NAME_LEN);    /* Delete '\n' at end of string. */
	memset(temp_str, 0, NAME_LEN);        /* Remove garbage values in temp_str. */
	strncpy(temp_str, search_str, strlen(search_str) - 1);

	free(search_str);
	return temp_str;
}

char ask_if_enter_new_val(char *name_of_val)
{
    char edit_yes_no;
	do {
		printf("Do you want to enter a new %s?  [Y]es or [n]o: ", name_of_val);
		scanf("%c", &edit_yes_no);
		clr_buf(stdin);
        return edit_yes_no;
	} while (edit_yes_no != 'y' && edit_yes_no != 'n');
}

char *get_filename()
{
	char *filename = malloc(12);
	printf("Enter filename (max. 12 characters): ");
	scanf("%s", filename);
	clr_buf(stdin);
	return filename;
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
