#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include <iostream>
#include <fstream>
#include "../config/config.h"

class vars
{
private:
        std::vector<std::string> names;
        std::vector<std::string> values;
public:
        vars();
        std::string searchVars(std::string);
};

#endif
