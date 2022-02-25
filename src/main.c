#include "ui.h"
#include "cmath.h"
int main() {
	expr* myexpr = newexpr("calc(7+7)*2");
	char* str;
	while(str = *myexpr->postfix++)
		printf("%s\n", str);
	//ui* UI = initui();
	//do {
	//	printw("%s", getinput(UI));
	//	uiref(UI);
	//} while (true);
}
