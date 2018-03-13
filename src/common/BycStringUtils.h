//
//  BycStringUtils.h
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycStringUtils_h
#define BycStringUtils_h

#include <string>
#include <vector>

class BycStringUtils {
public:
    static std::string toString(unsigned int index);
    static int getFieldCommponents(const std::string& field);
    
    /** Delete empty line and empty chars.
     */
    static void trim(std::string& str, bool left = true, bool right = true);
    
    static bool toInt(const std::string& str, int* val);
    
    static bool toFloat(const std::string& str, float* val);
    
    static int parseInt(const std::string& str, int defaultVal = 0);
    
    static void split(std::vector<std::string>& result, const std::string& str, const std::string& pattern);
};

#endif /* BycStringUtils_h */
