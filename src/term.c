#include <stdio.h>
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "term.h"

static struct {
	int rows;
	int cols;
} oldTermSettings;

void CLGL_setTermSize(int rows, int cols) {
	oldTermSettings.rows = CLGL_getTermRows();
	oldTermSettings.cols = CLGL_getTermCols();

	struct winsize ws;
	ws.ws_row = rows;
	ws.ws_col = cols;
	ws.ws_ypixel = 0;
	ws.ws_xpixel = 0;

	int res = ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws);	
	if(res == -1) {
		printf("ioctl failed\n");
	}
}

int CLGL_getTermRows() {
	struct winsize ws;
	int res = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);	
	if(res == -1) {
		printf("ioctl failed\n");
	}

	return ws.ws_row;
}

int CLGL_getTermCols() {
	struct winsize ws;
	int res = ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);	
	if(res == -1) {
		printf("ioctl failed\n");
	}

	return ws.ws_col;
}

void CLGL_restoreTermSet() {
	struct winsize ws;
	ws.ws_row = oldTermSettings.rows;
	ws.ws_col = oldTermSettings.cols;
	ws.ws_ypixel = 0;
	ws.ws_xpixel = 0;

	int res = ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws);	
	if(res == -1) {
		printf("ioctl failed\n");
	}
	printf("\033[?25h\033[?1049l");
}
