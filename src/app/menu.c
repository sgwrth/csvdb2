#include <stdio.h>
#include "../core/entry.h"
#include "./menu.h"

void print_main_menu(Entry **begin)
{
    printf("***\n");
    printf("MENU\n");
    printf("What do you want to do?\n");
    printf("[1] Add new entry\n");
    if (*begin != NULL) {
        printf("[2] Show all entries\n");
        printf("[3] Edit entry\n");
        printf("[0] Save and quit\n");
    } else {
        printf("[0] Quit\n");
    }
    printf("Please enter: ");
}
