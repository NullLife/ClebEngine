//
//  BycLight.h
//  BycRun
//
//  Created by FengMap on 2018/3/4.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycLight_h
#define BycLight_h

#include "BycDefinitions.h"

class BycLight {
public:
    enum LightType {
        DIRECTION = 0,
        POINT,
        SPOT
    };
    
    
    virtual ~BycLight();
    
    const String& getName() const;
    const LightType getLightType() const;
    
    /// Set intensity of light.
    void setIntensity(float intensity);
    const float getIntensity() const;
    
    /// Set diffuse color.
    void setDiffuseColor(const Vec4& color);
    const Vec4& getDiffuseColor() const;
    
    /// Set specular color.
    void setSpecularColor(const Vec4& color);
    const Vec4& getSpecularColor() const;
    
    /// Set attenuation of light.
    void setAttenuation(float constant, float linear, float quadratic, float range);
    const Vec4& getAttenuation() const;
    
    /// Returns the absolute upper range of the light.
    const float getAttenuationRange() const;
    
    /// Returns the constant factor in the attenuation formula.
    const float getAttenuationConstant() const;
    
    /// Returns the linear factor in the attenuation formula.
    const float getAttenuationLinear() const;
    
    /// Returns the quadric factor in the attenuation formula.
    const float getAttenuationQuadric() const;

      
protected:
    BycLight(const LightType type, const String& name);
    
    String _name;
    LightType _type;
    
    /// Light lux.
    float _intensity;
    
    /// Diffuse color.
    Vec4 _diffuseColor;
    
    /// Highlight(specular) color.
    Vec4 _specularColor;
    
    /// Vec4f
    Vec4 _atten;
};

#endif /* BycLight_h */
