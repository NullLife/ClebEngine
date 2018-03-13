//
//  BycPass.h
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycPass_h
#define BycPass_h

#include "../common/BycDefinitions.h"

class BycGLShader;
class BycParamsDataSource;
class BycMaterial;
class BycGLTextureUnitState;

class BycPass {
public:
    typedef Vector<BycGLShader*> GLShaderArr;
    typedef Vector<BycGLTextureUnitState*> GLTexUnitStateArr;
    
    BycPass();  
    ~BycPass();
    
    void setName(const String& name);
    const String& getName() const;
    
    void setParent(BycMaterial* mtl);
    BycMaterial* getParent();
    
    BycGLShader* createShader(GLenum shaderType, const String& path);
    void addShader(BycGLShader* shader);
    
    void updateGLShaderParameters(BycParamsDataSource* dataSource);
    
    const GLShaderArr& getShaders();
    
    BycGLTextureUnitState* createGLTextureUnitState(const String& name);
    
    const GLTexUnitStateArr& getGLTextureUnitStates();
    
private:
    void destroyedShaders();
    
    String _name;
    
    BycMaterial* _parent;
    
    GLShaderArr _shaders;
    
    GLTexUnitStateArr _texUnitStates;
};

#endif /* BycPass_h */
