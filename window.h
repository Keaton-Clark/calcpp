
#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <iostream>
#include "calc.h"

WINDOW *startMainWindow();
WINDOW *startInputWindow();
WINDOW *startHeaderWindow();

void updateHeaderWindow(WINDOW *);

class MWIN
{
private:
	int inputDimensions[4];
	int index = 0;
	int index2 = 0;
	WINDOW *mainWindow;

public:
	MWIN();
	void print(calc);
	void log(std::string);
};

class IWIN
{
private:
	int inputDimensions[4];
	WINDOW *inputWindow;
	

public:
	IWIN();
	std::string stringInput();
	
};

class HWIN
{
private:
	int headerDimensions[4];
	WINDOW *headerWindow;
	int getBattery();
	std::vector<std::string> mode;

public:
	HWIN();
	void update();
};
#endif