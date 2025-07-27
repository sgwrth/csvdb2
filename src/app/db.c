#include "./db.h"
#include <stdio.h>
#include "../enums/enums.h"
#include "../utils/buf.h"

char decide_on_db()
{
	char open_or_new_db;
	do {
		printf("[O]pen DB or create [n]ew?  Please enter: ");
		scanf("%c", &open_or_new_db);
		clr_buf(stdin);
	} while (open_or_new_db != OPEN && open_or_new_db != NEW);
	return open_or_new_db;
}
