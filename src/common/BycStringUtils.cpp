//
//  BycStringUtils.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycStringUtils.h"

#include <sstream>

std::string BycStringUtils::toString(unsigned int index) {
    return std::to_string(index);
}

int BycStringUtils::getFieldCommponents(const std::string& field) {
    auto iter = field.end() - 2;
    return *iter - 48;
}

void BycStringUtils::trim(std::string& str, bool left, bool right) {
    static const std::string delims = " \t\r";
    
    if(left)
        str.erase(0, str.find_first_not_of(delims)); // trim left
    
    if(right)
        str.erase(str.find_last_not_of(delims)+1); // trim right
}

bool BycStringUtils::toInt(const std::string& str, int* val) {
    int n = sscanf(str.c_str(), "%d", val);
    if (n == 0 || n == EOF) {
        return false;
    }
    return true;
}


bool BycStringUtils::toFloat(const std::string& str, float* val) {
    int n = sscanf(str.c_str(), "%f", val);
    if (n == 0 || n == EOF) {
        return false;
    }
    return true;
}

int BycStringUtils::parseInt(const std::string& str, int defaultVal) {
    std::stringstream ss(str);
    int ret = defaultVal;
    if( !(ss >> ret) )
        return defaultVal;
    return ret;
}

void BycStringUtils::split(std::vector<std::string>& result, const std::string& str, const std::string& pattern)
{
    size_t index = 0;
    size_t pos = 0;
    while (pos != -1)
    {
        pos = str.find(pattern, index);
        result.push_back(str.substr(index, pos-index));
        index = pos + 1;
    }
}
