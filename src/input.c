#include <stdio.h>

#include "input.h"

int CLGL_getString(char* str) {
	if(!fgets(str, 50, stdin)) {
		return 0;
	}
	return 1;
}
