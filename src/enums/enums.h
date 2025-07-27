#ifndef ENUMS_H
#define ENUMS_H

enum Db {
	OPEN = 'o',
	NEW = 'n'
};

enum Option {
	ADD_NEW_ENTRY = '1',
	SHOW_ALL_ENTRIES = '2',
	EDIT_ENTRY = '3',
	SAVE_AND_QUIT = '0'
};

enum Open_file {
	UNDEFINED = 'u',
	TRY_AGAIN = 't',
	CREATE_NEW = 'c',
	QUIT = 'q'
};

enum Insert_pos {
	AT_FRONT = 'f',
	AT_BACK = 'b'
};

#endif
