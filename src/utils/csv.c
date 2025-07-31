#include "../enums/enums.h"
#include "./csv.h"

void parse_entry_val_from_slice(char csv_line[], char value[], int *csv_line_pos)
{
	int value_pos = 0;
	while (csv_line[*csv_line_pos] != COMMA && csv_line[*csv_line_pos] != '\0') {
		if (csv_line[*csv_line_pos] != QUOTES) {
			value[value_pos] = csv_line[*csv_line_pos];
			value_pos++;
		}
		*csv_line_pos += 1;
	}
	*csv_line_pos += 1; /* Pos for next value to be read from array_from_chars. */
}
