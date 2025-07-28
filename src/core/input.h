#ifndef MENU_H
#define MENU_H
#include "../core/entry.h"

char pick_opt(Entry **begin);
char *enter_search_name();
char ask_if_enter_new_val(char *name_of_val);
char *get_filename();
enum Insert_pos get_insert_pos();
int get_num_of_inserts();
char enter_another();

#endif
