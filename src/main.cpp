#include "window.h"
#include "calc.h"
#include <iostream>
#include <string>
#include "variables.h"

int main()
{
	try {
		initscr();
		noecho();
		refresh();
		MWIN mainWindow;
		HWIN headerWindow;
		IWIN inputWindow;
                vars variables;
		std::string input;
		do {
			input = inputWindow.stringInput();
			calc calc1(input, &variables);
			mainWindow.print(calc1);
			headerWindow.update();
		} while (true);
	} catch (std::string error) {
		endwin();
		std::cout << error << std::endl;
	}
	return 0;
}
