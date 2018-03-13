//
//  BycMaterial.h
//  BycRun
//
//  Created by FengMap on 2018/1/21.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycMaterial_h
#define BycMaterial_h

#include "BycDefinitions.h"

class BycPass;

class BycMaterial {
public:
    typedef Vector<String> ImageResArr;
    typedef Vector<BycPass*> PassArr;
    
    BycMaterial();
    ~BycMaterial();
    
    void setSpecularIntensity(float intensity);
    float getSpecularIntensity();
    
    void setShininess(float shininess);
    float getShininess();
    
    BycPass* createPass(const String& name);
    
    // Add image path. If return -1, then fail to add it.
    int addImage(const String& image);
    
    // Get image path.
    const String& getImage(const int index) const;
    
    BycPass* getPass(int index);
      
private:
    String _name;
    
    Vec4 _defaultColor;
    
    float _specularIntensity;
    float _shininess;
    
    ImageResArr _images;
    
    PassArr _passes;
};

#endif /* BycMaterial_h */
