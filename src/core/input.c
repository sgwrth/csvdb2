#include "../app/menu.h"
#include "../app/messages.h"
#include "../enums/enums.h"
#include "../core/entry.h"
#include "../const/constants.h"
#include "../utils/buf.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
		printf(ENTER_NEW_PCT_S, name_of_val);
		scanf("%c", &edit_yes_no);
		clr_buf(stdin);
        return edit_yes_no;
	} while (edit_yes_no != YES && edit_yes_no != NO);
}

char *get_filename(char *filename)
{
    if (filename == NULL) {
        filename = malloc(MAX_FILENAME_LEN);
        printf(ENTER_FILENAME_PCT_D, MAX_FILENAME_LEN);
        scanf("%s", filename);
        clr_buf(stdin);
    } else {
        printf(CURRENT_FILENAME, filename);
        printf(KEEP_IT_YES_NO);
        char keep_filename;
        scanf("%c", &keep_filename);
        clr_buf(stdin);
        if (keep_filename == YES) {
            return filename;
        }
        printf(ENTER_FILENAME_PCT_D, MAX_FILENAME_LEN);
        scanf("%s", filename);
        clr_buf(stdin);
    }
	return filename;
}

enum Insert_pos get_insert_pos()
{
	char pos;
	do {
		printf(INSERT_BACK_FRONT);
		scanf("%c", &pos);
		clr_buf(stdin);
	} while (pos != AT_FRONT && pos != AT_BACK);
	if (pos == AT_FRONT)
		return AT_FRONT;
	return AT_BACK;
}

char enter_another()
{
	char another_entry;
	do {
		printf(ADD_ANOTHER_YES_NO);
		scanf("%c", &another_entry);
		clr_buf(stdin);
	} while (another_entry != YES && another_entry != NO);
	return another_entry;
}
