#ifndef window
#define window

#include "colors.h"

void CLGL_clearWindow();

void CLGL_setTermSize(int rows, int cols);
int CLGL_getTermRows();
int CLGL_getTermCols();
void CLGL_restoreTermSet();

void CLGL_drawCAtPos(int row, 
					int col, 
					char v,
					enum colorList color);

void CLGL_drawSAtPos(int row, 
					int col, 
					char* v,
					enum colorList color);
#endif
