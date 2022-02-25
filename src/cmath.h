#ifndef CMATH_H 
#define CMATH_H 
#include <stdlib.h>
#include <string.h>
typedef struct {
	char* str;
	char** postfix;
	char* ans;
} expr;
expr* newexpr(char* str);
#endif
