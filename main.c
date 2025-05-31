#include <stdio.h>
#include <unistd.h>

#include "src/colors.h"
#include "src/window.h"

#define ROWS 50
#define COLS 80

int main() {
	CLGL_init();

	CLGL_clearWindow();

	CLGL_setTermSize(ROWS, COLS);

	CLGL_createInputBox(5, 5, 5, 2);
	CLGL_createInputBox(15, 5, 5, 2);
	CLGL_createInputBox(25, 5, 5, 2);

	getchar();

	CLGL_restoreTermSet();

	return 0;
}
