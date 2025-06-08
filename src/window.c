#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Types.h"
#include "colors.h"
#include "LL.h"
#include "window.h"

// add some way to gather input,
// mabye some sort of input box???
//
// now time to add 

typedef struct {
	uint id;
	vec2 pos;
	vec2 size;
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
	// enables alt buffer
	printf("\033[?1049h");
}

void CLGL_clearWindow() {
	printf("\033[2J\033[H");
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
	box->size.y = row;
	box->size.x = col;
	
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
			printf("\033[%d;%dH", currentBox->pos.y + currentBox->size.y % 2,
								  currentBox->pos.x + 1);

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

			printf("\033[%d;%dH", currentBox->pos.y + currentBox->size.y % 2,
								  currentBox->pos.x + 1);

			break;
		}

		currentNode = currentNode->next;
		currentIndex++;
	}
}

void CLGL_exit() {
	destroyLL(&inputBoxes);
}
