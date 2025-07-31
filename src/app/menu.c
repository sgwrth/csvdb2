#include "../app/messages.h"
#include "../core/entry.h"
#include <stdio.h>
#include "./menu.h"

void print_main_menu(Entry **begin)
{
    printf(SEPARATOR);
    printf(MENU_TITLE);
    printf(DO_WHAT);
    printf(OPT_1_NEW_ENTRY);
    if (*begin != NULL) {
        printf(OPT_2_SHOW_ENTRIES);
        printf(OPT_3_EDIT_ENTRY);
        printf(OPT_0_SAVE_QUIT);
    } else {
        printf(OPT_0_QUIT);
    }
    printf(PROMPT_FOR_INPUT);
}

void print_file_not_found_menu()
{
    printf(OPT_T_TRY_AGAIN),
    printf(OPT_C_CREATE_DB);
    printf(OPT_Q_QUIT);
}
