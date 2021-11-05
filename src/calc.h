#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <vector>
#include <string>

class calc
{
private:
	std::string st;
	std::string an;
	std::vector<std::string> parsed;
	int parse();
	std::string solve(int, int);

public:
	calc(std::string);
	std::string getst() const;
	std::string getan() const;
};

class var
{
private:
	std::string name;
	std::string value;
public:
	var(std::string, std::string);
	std::string getVal();
	std::string setVal();
};



#endif