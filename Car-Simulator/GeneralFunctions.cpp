#include "GeneralFunctions.h"
#include <iostream>
#include <thread>
#include <regex>
#include <string>

float GeneralFunctions::ConvertCommaToFloat(std::string String) {
    if (String.find(',')) {
        std::replace(String.begin(), String.end(), ',', '.');
        return stof(String);
    }
    else {
        std::cerr << "No Comma found in String" << String << std::endl;
        return 0.0;
    }
}
