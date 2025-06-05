#include <stdio.h>

#include "input.h"

int CLGL_getString(char* str) {
	printf("\033[?25h");
	if(!fgets(str, 50, stdin)) {
		printf("\033[?25l");
		return 0;
	}
	printf("\033[?25l");
	return 1;
}
