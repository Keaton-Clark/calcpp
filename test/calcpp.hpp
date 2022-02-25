#ifndef CALCPP_HPP
#define CALCPP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

std::ostream &operator<<(std::ostream &output, const std::vector<std::string> &vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		output << vector[i] << "\t";
	}
	output << "\n";
	return output;
}

namespace calcpp {
	namespace detail {
		bool isOperator(const char c) {
			return	('+' == c) || ('-' == c) ||
				('*' == c) || ('/' == c) ||
				('^' == c) || ('<' == c) ||
				('>' == c) || ('=' == c) ||
				(',' == c) || ('!' == c) ||
				('(' == c) || (')' == c) ||
				('[' == c) || (']' == c) ||
				('{' == c) || ('}' == c) ||
				('%' == c) || (':' == c) ||
				('?' == c) || ('&' == c) ||
				('|' == c) || (';' == c) ;
		}			
		bool isDigit(const char c) {
			return (('0' <= c) && (c <= '9')) || c == '.';
		}	
		bool isLetter(const char c)
		{
			return	(('a' <= c) && (c <= 'z')) ||
				(('A' <= c) && (c <= 'Z')) ;
		}
		bool isLBracket(const char c)
		{
			return ('(' == c) || ('[' == c) || ('{' == c);
		}
		bool isRBracket(const char c)
		{
			return (')' == c) || (']' == c) || ('}' == c);
		}
		bool isBracket(const char c)
		{
			return isLBracket(c) || isRBracket(c);
		}
		bool isSign(const char c)
		{
			return ('+' == c) || ('-' == c);
		}
	}
	class expression {
		public:
			expression(){};
			/**
			 * Overloaded constructor when a string is passed in. Sets the expressionString and calls parse().
			 * @param expressionString the string to be parsed and evaluated
			 */
			expression(std::string exprStr) : exprStr{exprStr} {parse();}
			/**
			 * Sets or updates the expressionString and calls parse().
			 * @param expressionString the string to be parsed and evaluated
			 */
			void setExprStr(std::string expression) {exprStr = expression; prsdExprStr.clear(); parse();}
			void addSym(std::string sym, std::string symVal) {syms.push_back(sym); symVals.push_back(symVal);}
			std::string getExprStr() {return exprStr;};
			std::vector<std::string> getPrsdExprStr() {return prsdExprStr;};
			std::string solve(){
				std::cout << prsdExprStr;
				return solveSubStr(prsdExprStr);
			};
		private:
			std::string exprStr; //Expression String e.g. "sin(x*220)"
			std::vector<std::string> prsdExprStr; //Parsed Expression String e.g. "sin(","x","*","220",")"
			std::vector<std::string> syms; //Vector of variables/symbols e.g. "pi", "e"
			std::vector<std::string> symVals; //Vector of variable/symbol values e.g. "3.14", "2.71"
			/**
			 * Parses the expressionString into a vector of strings held by parsedExpressionString
			 * @return bool if successful
			 */
			bool parse() {
				int prsdExprStrIndx = 0;
				int exprStrIndx = 0;
				while (exprStrIndx < exprStr.length()){
					if (detail::isLetter(exprStr[exprStrIndx])) { //keeps letters together
						prsdExprStr.push_back("");
						while (detail::isLetter(exprStr[exprStrIndx])){
							prsdExprStr[prsdExprStrIndx] += exprStr[exprStrIndx];
							exprStrIndx++;
						}
						if (detail::isLBracket(exprStr[exprStrIndx])) { //keeps an L bracket after a string of letters e.g. "sin("
							prsdExprStr[prsdExprStrIndx] += exprStr[exprStrIndx];
							exprStrIndx++;
						} else {
							prsdExprStr[prsdExprStrIndx] = getSymVal(prsdExprStr[prsdExprStrIndx]);	
						}
						prsdExprStrIndx++;
					} else if (detail::isDigit(exprStr[exprStrIndx])) { //keeps digits together
						prsdExprStr.push_back("");
						while (detail::isDigit(exprStr[exprStrIndx])){
							prsdExprStr[prsdExprStrIndx] += exprStr[exprStrIndx];
							exprStrIndx++;
						}
						prsdExprStrIndx++;
					} else if (exprStr[exprStrIndx] == ' ') { //disregards whitespaces
						exprStrIndx++;
					} else if (detail::isOperator(exprStr[exprStrIndx])) { //keeps operators seperate
						prsdExprStr.push_back("");
						prsdExprStr[prsdExprStrIndx] += exprStr[exprStrIndx];
						exprStrIndx++;
						if (exprStr[exprStrIndx] == '=' && exprStr[exprStrIndx-1] == ':'){ //keeps ":=" together
							prsdExprStr[prsdExprStrIndx] += '=';
							exprStrIndx++;
						}
						prsdExprStrIndx++;
					} else {
						std::cout << "cannot find operator: " << exprStr[exprStrIndx] << std::endl;
						return false;
					}
				}
				return true;
			}
			std::string solveSubStr(std::vector<std::string> subPrsdExprStr) {
				size_t start; 
				int pCount = 0; //counting parenthesis
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "(") {
						if (pCount == 0) 
							start = i;
						pCount++;
					} else if (subPrsdExprStr[i] == ")") {
						pCount--;
						if (pCount == 0) {
							subPrsdExprStr[start] = solveSubStr(std::vector<std::string>(subPrsdExprStr.begin() + start + 1, subPrsdExprStr.begin() + i));
							subPrsdExprStr.erase(subPrsdExprStr.begin() + start + 1, subPrsdExprStr.begin() + i + 1);
						}	
					}
				}
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "^") {
						std::cout << subPrsdExprStr;
						subPrsdExprStr[i] = std::to_string(std::pow(std::stold(subPrsdExprStr[i-1]), std::stold(subPrsdExprStr[i+1])));
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i + 1);
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i - 1);
						i--;
					}
				}
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "*") {
						std::cout << subPrsdExprStr;
						subPrsdExprStr[i] = std::to_string(std::stold(subPrsdExprStr[i-1]) * std::stold(subPrsdExprStr[i+1]));
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i + 1);
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i - 1);
						i--;
					}
				}
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "/") {
						std::cout << subPrsdExprStr;
						subPrsdExprStr[i] = std::to_string(std::stold(subPrsdExprStr[i-1]) / std::stold(subPrsdExprStr[i+1]));
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i + 1);
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i - 1);
						i--;
					}
				}
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "+") {
						std::cout << subPrsdExprStr;
						subPrsdExprStr[i] = std::to_string(std::stold(subPrsdExprStr[i-1]) + std::stold(subPrsdExprStr[i+1]));
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i + 1);
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i - 1);
						i--;
					}
				}
				for (size_t i = 0; i < subPrsdExprStr.size(); i++) {
					if (subPrsdExprStr[i] == "-") {
						std::cout << subPrsdExprStr;
						subPrsdExprStr[i] = std::to_string(std::stold(subPrsdExprStr[i-1]) - std::stold(subPrsdExprStr[i+1]));
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i + 1);
						subPrsdExprStr.erase(subPrsdExprStr.begin() + i - 1);
						i--;
					}
				}
				if (subPrsdExprStr[1] == ":=") {
					addSym(subPrsdExprStr[0], subPrsdExprStr[2]);
					return std::string("Variable set"); 
				}
				return subPrsdExprStr[0];
			}
			std::string getSymVal(std::string sym) {
				for (size_t i = 0; i < syms.size(); i++) {
					if (syms[i] == sym)
						return symVals[i];
				}
				return sym;
			}
	};
}
#endif // CALCPP_HPP
