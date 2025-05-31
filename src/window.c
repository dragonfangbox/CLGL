#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "window.h"
#include "Types.h"
#include "colors.h"
#include "LL.h"

// add some way to gather input,
// mabye some sort of input box???
//
// now time to add 

static struct {
	int rows;
	int cols;
} oldTermSettings;

typedef struct {
	uint id;
	vec2 pos;
} inputBox;

static uint globalID = 0;
static uint cursorID = 0;
static linkedList inputBoxes;
	
static void drawRect(int row, int col, int width, int height) {
	printf("\033[%d;%dH", row, col);

	// top line
	printf("\033[%d;%dH+", row, col);
	for(int i = 0; i < width; i++) {
		printf("-");
	}
	printf("+");

	// vertical columns
	for(int i = 0; i < height; i++) {
		printf("\033[%d;%dH|", row + i + 1, col);
		printf("\033[%d;%dH|", row + i + 1, col + width + 1);
	}

	// bottom line
	printf("\033[%d;%dH+", row + height + 1, col);
	for(int i = 0; i < width; i++) {
		printf("-");
	}
	printf("+");
}

void CLGL_init() {
	initLL(&inputBoxes, NULL);
}

void CLGL_clearWindow() {
	printf("\033[2J\033[H");
	// sets cursor transparent and enables alt buffer
//	printf("\033[?25l");
}

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

	destroyLL(&inputBoxes); 
}

void CLGL_drawCAtPos(int row, 
					int col, 
					char v,
					enum colorList color) {
	printf("\033[%d;%dH\033[1;34;%dm%c", row, col, color, v);
	fflush(stdout);
}

void CLGL_drawSAtPos(int row, 
					int col, 
					char* v,
					enum colorList color) {
	printf("\033[%d;%dH\033[1;34;%dm%s", row, col, color, v);
	fflush(stdout);
}

void CLGL_createInputBox(int row, int col, int width, int height) {
	drawRect(row, col, width, height);

	inputBox* box = malloc(sizeof(inputBox));
	if(box == NULL) {
		printf("error mallocing for inputbox creation");
	}
	box->id = globalID;
	box->pos.y = row;
	box->pos.x = col;
	
	if(globalID == 0) {
		inputBoxes.head->value = box;
		globalID++;
		return;
	}

	globalID++;
	appendLL(&inputBoxes, box);
}

void CLGL_createBox(int row, int col, int width, int height) {
	drawRect(row, col, width, height);
}

void CLGL_jumpToNext() {
	node* currentNode = inputBoxes.head;
	uint currentIndex = 0;

	if(cursorID == globalID - 1) {
		cursorID = 0;
	} else {
		cursorID++;
	}

	while(currentNode != NULL) {
		inputBox* currentBox = (inputBox*)currentNode->value;
		if(currentIndex == cursorID) {
			printf("\033[%d;%dH", currentBox->pos.y, currentBox->pos.x);
			break;
		}

		currentNode = currentNode->next;
		currentIndex++;
	}
}

void CLGL_jumpToPrev() {
	node* currentNode = inputBoxes.head;
	uint currentIndex = 0;

	if(cursorID == 0) {
		cursorID = globalID - 1;
	} else {
		cursorID--;
	}

	while(currentNode != NULL) {
		inputBox* currentBox = (inputBox*)currentNode->value;
		if(currentIndex == cursorID) {
			printf("\033[%d;%dH", currentBox->pos.y, currentBox->pos.x);
			break;
		}

		currentNode = currentNode->next;
		currentIndex++;
	}
}
