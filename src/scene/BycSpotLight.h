//
//  BycSpotLight.h
//  BycRun
//
//  Created by FengMap on 2018/3/5.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycSpotLight_h
#define BycSpotLight_h

#include "BycLight.h"

class BycSpotLight : public BycLight {
public:
    BycSpotLight(const String& name);  
    ~BycSpotLight();
    
    /// Set cutoff for spot light.
    void setCutoff(float rad);
    const float getCutoff() const;

      
private:  
    /// Spot light.
    float _cutoff;
};

#endif /* BycSpotLight_h */
