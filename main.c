#ifdef __unix__
	#include <termios.h>
	#include <asm-generic/ioctls.h>
	#include <sys/ioctl.h>
#endif

#include <stdio.h>
#include <unistd.h>

#include "src/colors.h"
#include "src/window.h"

#define ROWS 50
#define COLS 80

int main() {
	CLGL_clearWindow();

	printf("ROWS: %d\n", CLGL_getTermRows());
	printf("COLS: %d\n", CLGL_getTermCols());
	
	CLGL_setTermSize(ROWS, COLS);

	printf("ROWS: %d\n", CLGL_getTermRows());
	printf("COLS: %d\n", CLGL_getTermCols());
	
		CLGL_drawCAtPos(20,20, '|', GREEN);
		sleep(1);
		CLGL_drawCAtPos(20,20, '/', GREEN);
		sleep(1);
		CLGL_drawCAtPos(20,20, '-', GREEN);
		sleep(1);
		CLGL_drawCAtPos(20,20, '\\', GREEN);
		sleep(1);
		CLGL_drawCAtPos(20,20, '|', GREEN);

	getchar();

	CLGL_restoreTermSet();

	printf("ROWS: %d\n", CLGL_getTermRows());
	printf("COLS: %d\n", CLGL_getTermCols());

	return 0;
}
