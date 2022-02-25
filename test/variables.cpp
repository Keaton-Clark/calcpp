#include "variables.h"

vars::vars() {
        std::ifstream file;
        std::string tmp1, tmp2;
        file.open("config/constants.txt");
        if (file.is_open()) {
                while (file >> tmp1){
                        file >> tmp2;
                        names.push_back(tmp1);
                        values.push_back(tmp2);
                }
        }
        file.close();
        return;
}

std::string vars::searchVars(std::string search) {
        for (int x = 0; x < names.size(); x++) {
                if (names[x] == search)
                        return values[x];
        }
        return "nil";
}

void vars::setValue(std::string name, std::string value) {
        names.push_back(name);
        values.push_back(value);
}
