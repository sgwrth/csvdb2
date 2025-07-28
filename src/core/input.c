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
