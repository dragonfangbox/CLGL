#include <stdio.h>
#include <unistd.h>

#include "src/keycodes.h"
#include "src/colors.h"
#include "src/input.h"
#include "src/term.h"
#include "src/window.h"

#define ROWS 50
#define COLS 80

int main() {
	CLGL_init();
	CLGL_setRawMode();

	CLGL_createInputBox(5, 5, 5, 5);
	CLGL_createInputBox(15, 5, 5, 5);
	CLGL_createInputBox(25, 5, 5, 5);
	CLGL_jumpToPrev();

	CLGL_setTermSize(ROWS, COLS);

	char str[128];

	int c;
	while((c = CLGL_getKeyboardInput())) {
		if(c == 'q') {
			break;
		} else if(c == UP_ARROW) {
			CLGL_jumpToPrev();
		} else if(c == DOWN_ARROW) {
			CLGL_jumpToNext();
		} else if(c == 'w') {
			CLGL_getString(str, sizeof(str));
		}
	}

	CLGL_restoreTermSet();

	return 0;
}
