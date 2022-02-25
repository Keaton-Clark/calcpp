#include "ui.h"

ui* initui() {
	initscr();
	noecho();
	refresh();
	ui* out = (ui*)malloc(sizeof(ui));
	out->mwin = newwin(LINES - (HEADERHEIGHT + INPUTHEIGHT), COLS, HEADERHEIGHT, 0);
	wborder(out->mwin, ' ', ' ', BORDER, BORDER, BORDER, BORDER, BORDER, BORDER);
	out->hwin = newwin(HEADERHEIGHT, COLS, 0, 0);
	out->iwin = newwin(INPUTHEIGHT, COLS, LINES - INPUTHEIGHT, 0);
	uiref(out);
	return out;
}

void uiref(ui* foo) {
	wrefresh(foo->hwin);
	wrefresh(foo->mwin);
	wrefresh(foo->iwin);
}

char* getinput(ui* foo) {
	char ch;
	char* out = (char*)malloc(sizeof(char)*COLS);
	int x = 0;
	wmove(foo->iwin, x, 0);
	wdeleteln(foo->iwin);
	wrefresh(foo->iwin);
	do {
		ch = getch();
		if (ch >= 32 && ch <= 126) {
			waddch(foo->iwin, ch);
			x++;
		} else if (ch == 127) {
			mvwdelch(foo->iwin, 0, x-1);
			x--;	
		} else if (ch == 0x1b) {
			ch = getch();
			if (ch == 0x5b) {
				ch = getch();
				switch (ch) {
					case 0x41:
						break;//up
					case 0x42:
						break;//down
					case 0x43:
						wmove(foo->iwin, 0, ++x);
						break;//right
					case 0x44:
						wmove(foo->iwin, 0, --x);
						break;//left
				}
			}
		}

		uiref(foo);
	} while (ch != 10);
	mvwinstr(foo->iwin, 0, 0, out);
	return out;
}
