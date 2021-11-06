#include "calc.h"
#include <vector>
#include "window.h"

calc::calc(std::string st) : st(st)
{
        if (st == "quit")
		throw std::string("Calc++ Terminated");
	if (parse() == 0)
		an = solve(0, parsed.size());
}

int calc::parse()
{
	parsed.reserve(st.length());
	int index = 0;
	int i = 0;
	while (i < st.length()) {
		if (st[i] >= '0' && st[i] <= '9' || st[i] == '.') {
			parsed.push_back("");
			while (i < st.length() && st[i] >= '0' && st[i] <= '9' || st[i] == '.') {
				parsed[index] += st[i];
				i++;
			}
			index++;
		} else if (st[i] >= 'a' && st[i] <= 'z') {
			parsed.push_back("");
			while (i < st.length() && st[i] >= 'a' && st[i] <= 'z') {
				parsed[index] += st[i];
			 	i++;
			}
                        parsed[index] = variables.searchVars(parsed[index]);
			index++;
		} else if (st[i] == '(' || st[i] == ')' || st[i] == '+' || st[i] == '*' || st[i] == '/') {
			parsed.push_back("");
			parsed[index] += st[i];
			index++;
			i++;
		} else if (st[i] == ' ') {
			while (st[i] == ' ' && i < st.length()) {
				i++;
			}
		} else if (st[i] >= 'A' && st[i] <= 'Z') {
			an = std::string("Variables and functions are only lowercase");
			return 1;
		} else if (st[i] == '-') {
      parsed.push_back("");
      parsed[index] += st[i];
      if (i != 0)
        if (!(st[i-1] == '(' || st[i-1] == ')' || st[i-1] == '+' || st[i-1] == '*' || st[i-1] == '/' || st[i-1] == '-'))
            index++;
      i++;
		} else {
			an = std::string("Cannot find operator: ") += st[i];
			return 1;
		}		
	}
	return 0;
}

std::string calc::solve(int lower, int upper)
{
	int pCount = 0;
	int start;
	int i;
	std::vector <std::string> tmp;
	for (i = lower; i < upper; i++) {
		if (parsed[i] == "(") {
			if (pCount == 0)
				start = i;
			pCount++;
		} 
		if (parsed[i] == ")") {
			pCount--;
			if (pCount == 0) {
				tmp.push_back(solve(start + 1, i));
			}	
		} else if (pCount == 0) {
			tmp.push_back(parsed[i]);
		}
	}
	for (i = tmp.size()-1; i >= 0; i--) {
		if (tmp[i] == "*") {
			tmp[i] = std::to_string(std::stold(tmp[i-1]) * std::stold(tmp[i+1]));
			tmp.erase(tmp.begin() + i - 1);
			tmp.erase(tmp.begin() + i + 1);
		}
	}
	for (i = tmp.size()-1; i >= 0; i--) {
		if (tmp[i] == "/") {
			tmp[i] = std::to_string(std::stold(tmp[i-1]) / std::stold(tmp[i+1]));
			tmp.erase(tmp.begin() + i - 1);
			tmp.erase(tmp.begin() + i + 1);
		}
	}
	for (i = tmp.size()-1; i >= 0; i--) {
		if (tmp[i] == "+") {
			tmp[i] = std::to_string(std::stold(tmp[i-1]) + std::stold(tmp[i+1]));
			tmp.erase(tmp.begin() + i - 1);
			tmp.erase(tmp.begin() + i + 1);
		}
	}
	for (i = tmp.size()-1; i >= 0; i--) {
		if (tmp[i] == "-") {
			tmp[i] = std::to_string(std::stold(tmp[i-1]) - std::stold(tmp[i+1]));
			tmp.erase(tmp.begin() + i - 1);
			tmp.erase(tmp.begin() + i + 1);
		}
	}
	return tmp[0];
}	

std::string calc::getst() const
{
	return st;
}

std::string calc::getan() const
{
	return an;
}


