#ifndef term
#define term

void CLGL_setTermSize(int rows, int cols);
int CLGL_getTermRows();
int CLGL_getTermCols();
void CLGL_restoreTermSet();

#endif
