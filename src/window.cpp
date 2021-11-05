#include "window.h"
#include "config.h"
#include <fstream>

MWIN::MWIN()
{
	int mainDimensions[4] = {LINES - (HEADERHEIGHT + INPUTHEIGHT), COLS, HEADERHEIGHT, 0};
	mainWindow = newwin(mainDimensions[0], mainDimensions[1], mainDimensions[2], mainDimensions[3]);
	wborder(mainWindow, ' ', ' ', BORDER, BORDER, BORDER, BORDER, BORDER, BORDER);
	wrefresh(mainWindow);
}

void MWIN::print(calc printCalc)
{
	mvwaddstr(mainWindow, ++index, 0, printCalc.getst().data());
	mvwprintw(mainWindow, ++index, 2, "%s", printCalc.getan().data());
	wrefresh(mainWindow);
	return;
}

IWIN::IWIN()
{
	int inputDimensions[4] = {INPUTHEIGHT, COLS, LINES - INPUTHEIGHT, 0};
	inputWindow = newwin(inputDimensions[0], inputDimensions[1], inputDimensions[2], inputDimensions[3]);
	wrefresh(inputWindow);
}

std::string IWIN::stringInput()
{
	char ch;
	int x = 0;
	int y = 0;
	std::string inputString;

	wmove(inputWindow, y, x);
	wdeleteln(inputWindow);
	wrefresh(inputWindow);

	do
	{
		ch = getch();
		getyx(inputWindow, y, x);
		if (true)
		{
			//wprintw(inputWindow, "%d", ch);
		}
		if (ch == 27)
		{
			ch = getch();
			if (ch == 126)
				wdelch(inputWindow);
			else
				ch = getch();
			switch (ch)
			{
			case 65:
				wprintw(inputWindow, "move up");
				break;
			case 66:
				wprintw(inputWindow, "move down");
				break;
			case 67:
				wmove(inputWindow, y, ++x);
				break;
			case 68:
				wmove(inputWindow, y, --x);
				break;
			}
		}
		else if (ch >= 32 && ch <= 126)
		{
			winsch(inputWindow, ch);
			inputString.insert(x, 1, ch);
			wmove(inputWindow, y, ++x);
		}
		else if (ch == 127 && x != 0)
		{
			mvwdelch(inputWindow, y, x - 1);
			inputString.erase(x-1, 1);
		}
		wrefresh(inputWindow);
	} while (ch != 10);
	wrefresh(inputWindow);
	return inputString;

}

HWIN::HWIN()
{	
	int headerDimensions[4] = {1, COLS, 0, 0};
	headerWindow = newwin(headerDimensions[0], headerDimensions[1], headerDimensions[2], headerDimensions[3]);
	update();
}

void HWIN::update()
{
	wchgat(headerWindow, -1, A_REVERSE, 0, NULL);
	wattrset(headerWindow, A_REVERSE);
	mvwprintw(headerWindow, 0, COLS - 11, "%s", "RADS");
	mvwprintw(headerWindow, 0, COLS - 4, "%d%c", getBattery(), '%');
	mvwprintw(headerWindow, 0, 0, "%s", "");
	wrefresh(headerWindow);
}

int HWIN::getBattery()
{
	std::ifstream battery;
	int bat;
	battery.open("/sys/class/power_supply/BAT0/capacity");
	if (battery.is_open())
	{
		battery >> bat;
		battery.close();
		return bat;
	}
	else
	{
		return -1;
	}
}
