#include "calcpp.hpp"


int main() {
	calcpp::expression mycalc;
	mycalc.addSym("pi", "3.14");
	mycalc.addSym("e", "2.71");
	mycalc.setExprStr("x:=7");
	mycalc.solve();
	mycalc.setExprStr("x");
	std::cout << mycalc.solve();
}
