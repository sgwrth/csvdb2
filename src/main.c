#include "./app/db.h"
#include "./core/entry.h"
#include "./core/file.h"
#include "./core/input.h"
#include "./enums/enums.h"

int main()
{
	Entry *begin = NULL;
	enum Db open_or_new_db = decide_on_db();
	if (open_or_new_db == OPEN)
		read_from_file(&begin);
	char option;
	do {
		option = pick_opt(&begin);
		exec_opt(option, &begin);
	} while (option != SAVE_AND_QUIT );
	return 0;
}
