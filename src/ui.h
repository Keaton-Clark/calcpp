#ifndef UI_H 
#define UI_H
#include <ncurses.h>
#include <stdlib.h>
#include "config.h"
typedef struct {
	WINDOW* mwin;
	WINDOW* iwin;
	WINDOW* hwin;
} ui;
char* getinput(ui*);
ui* initui();
void uiref(ui*);
#endif //UI_H
