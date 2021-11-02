#include "display.h"
#include <iostream>
#include <string>

int main() {
    try
    {
        startDisplay();
        char c;
        int index = 0;
        do
        {
            c = getch();
            printw("%c", c);
            index++;
        } while (c != 'q');
        
        endwin();
    }
    catch(std::string error)
    {
        endwin();
        std::cout << error << std::endl;
    }
}
