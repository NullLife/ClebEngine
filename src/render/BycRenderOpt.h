//
//  BycRenderOpt.h
//  BycRun
//
//  Created by FengMap on 2018/1/24.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycRenderOpt_h
#define BycRenderOpt_h

#include "BycDefinitions.h"

class BycRenderOpt {
public:
    BycRenderOpt();  
    ~BycRenderOpt();
    
    GLuint _vao;
    
    size_t _start;
    size_t _count;
};

#endif /* BycRenderOpt_h */
