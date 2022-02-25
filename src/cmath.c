#include "cmath.h"
#include <stdbool.h>
#include <stdio.h>

char** exprtok(char*);
char** genpf(char**);
bool isNum(char);
bool isAlph(char);
bool isFunc(char*);
bool isOp(char*);
int prec(char*);

expr* newexpr(char* foo) {
	expr* out = malloc(sizeof(expr));
	out->str=foo;
	out->postfix = genpf(exprtok(foo));
	return out;
}

char** genpf(char** foo) {
	char** out = (char**)malloc(sizeof(foo)*sizeof(char**));
	char** bar = (char**)malloc(sizeof(foo)*sizeof(char**));
	int i = 0;
	int n = 0;
	char* str;
	while (str = *foo++) {
		if (isOp(str)) {
			if (n == 0 || prec(str)>prec(bar[n-1])) {
				bar[n] = str;
				n++;
			} else {
				while (n != 0 && prec(bar[n-1]) >= prec(str)){
					out[i] = bar[n-1];
					i++;
					n--;
				}
				bar[n] = str;
				n++;
				
			}
		} else if (str[strlen(str)] == '(') {
			bar[n] = str;
			n++;
		} else if (*str == ')') {
			while (n != 0 && *bar[n-1] != '(') {
				out[i] = bar[n-1];
				i++;
				n--;
			}
			n--;
		} else {
			out[i] = str;
			i++;
		}
	}
	while (n != 0) {
		out[i] = bar[n-1];
		n--;
		i++;
	}
	free(bar);
	out[i] = NULL;
	return out;
	
}

char** exprtok(char* foo) {
	char** out = (char**)malloc(sizeof(char*) * strlen(foo));
	char* bar = (char*)malloc(sizeof(char) * strlen(foo));
	int x = 0, i = 0;
	char c = *foo++;
	while (c) {
		if (isNum(c)) {
			i = 0;
			while (isNum(c)) {
				bar[i] = c;
				c = *foo++;
				i++;
			}
			out[x] = malloc(sizeof(char) * i);
			strncpy(out[x], bar, i);
			x++;
		} else if (isAlph(c)) {
			i = 0;
			while (isAlph(c)) {
				bar[i] = c;
				c = *foo++;
				i++;
			}
			if (c == '(') {
				bar[i] = c;
				i++;
				c = *foo++;
			}
			out[x] = malloc(sizeof(char) * i+1);
			strncpy(out[x], bar, i);
			x++;
		} else if (c == ' ') {
			c = *foo++;
		} else {
			out[x] = (char*)malloc(sizeof(char));
			out[x][0] = c;
			c = *foo++;
			x++;
		}
	}
	free(bar);
	out[x] = NULL;
	return out;
}

bool isNum(char foo) {
	return foo >= '0' && foo <= '9';
}
bool isAlph(char foo) {
	return foo >= 'A' && foo <= 'Z' || foo >= 'a' && foo <= 'z';
}
bool isFunc(char* foo) {
	return foo[strlen(foo) - 1] == '(';
}
bool isOp(char* foo) {
	return foo[0] == '+' || foo[0] == '-' || foo[0] == '*' || foo[0] == '/';
}
int prec(char* foo) {
	if(*foo == '/' || *foo == '*')
			return 2;
	else if(*foo == '+' || *foo == '-')
			return 1;
	else
			return -1;
	
}
