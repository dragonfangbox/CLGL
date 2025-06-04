#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include "src/colors.h"
#include "src/input.h"
#include "src/term.h"
#include "src/window.h"

#define ROWS 50
#define COLS 80

int main() {
	CLGL_init();

	CLGL_clearWindow();

	CLGL_setTermSize(ROWS, COLS);

	while(1) {
		CLGL_clearWindow();
		CLGL_createInputBox(5, 5, 15, 3);
	//	CLGL_createInputBox(15, 5, 5, 2);
	//	CLGL_createInputBox(25, 5, 5, 2);

		CLGL_jumpToPrev();

		char str[50];
		CLGL_getString(str);
		printf("\n\n\n%s", str);
	}



	CLGL_restoreTermSet();

	return 0;
}
