#include <stdio.h>

#include "keycodes.h"
#include "input.h"

// some sort of function to get input needs to be made
// that prints what you type because of raw mode.
// and mabye a get keyboard input func that just returns 
// what the keyboard presses??
// outline for what i want (inside main)
//
// int quit = 0
// while(!quit) {
//		int x = getinput()
//		switch(x) {
//			(a bunch of cases depending on what)
//			case: q 
//				quit = 1;
//				break;
//			case: enter
//				getstring(); (to gather information from an input box)
//				break
//		}
// }

// returns the keycode of the pressed key
int CLGL_getKeyboardInput() {
	char c = getc(stdin);
	if(c == '\x1B') {
		c = getc(stdin);
		if(c == '[') {
			c = getc(stdin);
			switch(c) {
				case 'A':
					return UP_ARROW;
					break;
				case 'B':
					return DOWN_ARROW;
					break;
				case 'C':
					return RIGHT_ARROW;
					break;
				case 'D':
					return LEFT_ARROW;
					break;
			}
		}
	}

	return c;
}

void CLGL_getString(char* str, int len) {
	char c;
	int count = 0;
	while((c = getc(stdin))) {
		if(c == '\r' || c == '\n' || c == '\0' || count > len) {
			break;
		}

		printf("%c", c);
		count++;
	}

	for(int i = 0; i < count; i++) {
		printf("\b \b");
	}
}
