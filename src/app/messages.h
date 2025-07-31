#ifndef MESSAGES_H
#define MESSAGES_H

/* db.c */
#define OPEN_CREATE_DB "[O]pen DB or create [n]ew?  Please enter: "

/* entry.c */
#define PLACEHOLDER "[undefined]"
#define CURRENT_NAME "Current name: "
#define PROMPT_FOR_NAME "Please enter name: "
#define CURRENT_PHONENUMBER "Current phonenumber: "
#define PROMPT_FOR_PHONENUMBER "Please enter phonenumber: "
#define CURRENT_YOB "Current year of birth: "
#define PROMPT_FOR_YOB "Please enter year of birth: "
#define PROMPT_FOR_SEARCH_NAME "Enter search name: "
#define ENTER_CONTACT "### Enter Contact\n"
#define NO_MATCH_FOUND "No matching entry found.\n"

/* file.c */
#define NO_MATCH_FOUND "No matching entry found.\n"
#define NO_FILE_FOUND "Error: file not found\n"

/* input.c */
#define ENTER_NEW_PCT_S "Do you want to enter a new %s?  [Y]es or [n]o: "
#define ENTER_FILENAME_PCT_D "Enter filename (max. %d characters): "
#define CURRENT_FILENAME "Current filename: %s\n"
#define KEEP_IT_YES_NO "Keep it?  [Y]es or [n]o: \n"
#define INSERT_BACK_FRONT "Insert at [f]ront or [b]ack?  Please enter: "
#define ADD_ANOTHER_YES_NO "Do you want to add another entry?  [Y]es or [n]o: "

/* menu.c */
#define SEPARATOR "***\n"
#define MENU_TITLE "MENU\n"
#define DO_WHAT "What do you want to do?\n"
#define OPT_1_NEW_ENTRY "[1] Add new entry\n"
#define OPT_2_SHOW_ENTRIES "[2] Show all entries\n"
#define OPT_3_EDIT_ENTRY "[3] Edit entry\n"
#define OPT_0_SAVE_QUIT "[0] Save and quit\n"
#define OPT_0_QUIT "[0] Quit\n"
#define PROMPT_FOR_INPUT "Please enter: "
#define OPT_T_TRY_AGAIN "[T]ry again\n"
#define OPT_C_CREATE_DB "[C]reate a new db\n"
#define OPT_Q_QUIT "[Q]uit the program?\n"

/* output.c */
#define TABLE_HEADER "NAME                     |PHONENUMBER              |Y.O.B.\n"
#define TABLE_HRLINE "-------------------------|-------------------------|------\n"

#endif
