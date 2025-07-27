#include "./buf.h"
#include <stdio.h>

void clr_buf(FILE *fp) {
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n')
		/* Do nothing. */ ;
}
