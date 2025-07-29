#ifndef MENU_H
#define MENU_H
#include "../core/entry.h"

char pick_opt(Entry**);
char *enter_search_name();
char ask_if_enter_new_val(char*);
char *get_filename(char*);
enum Insert_pos get_insert_pos();
int get_num_of_inserts();
char enter_another();

#endif
