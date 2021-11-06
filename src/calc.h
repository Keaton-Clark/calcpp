#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <vector>
#include <string>
#include "variables.h"

class calc
{
private:
	std::string st;
	std::string an;
	std::vector<std::string> parsed;
	int parse();
	std::string solve(int, int);
        vars variables;
public:
	calc(std::string);
	std::string getst() const;
	std::string getan() const;
};


#endif
