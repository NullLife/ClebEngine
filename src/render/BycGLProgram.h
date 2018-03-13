//
//  BycGLProgram.h
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLProgram_h
#define BycGLProgram_h

#include "BycDefinitions.h"

class BycGLShader;

class BycGLProgram {
public:
    typedef Vector<BycGLShader*> GLShaderArr;
    
    BycGLProgram();  
    ~BycGLProgram();
    
    // Attach shader.
    void attach(BycGLShader* shader);
    
    /// Create shader.
    BycGLShader* createShader(GLenum shaderType);
    BycGLShader* createShader(GLenum shaderType, String filePath);
    
    /// Active program.
    void active();
    
    /// Get program id.
    const GLuint getId();
    
    void bindParam();
    
    void commitParamDataToGPU();
      
private:
    void _compileAndLink();
    void _destroyShaders();
    void _destroy();
    
    GLShaderArr _shaders;
    
    bool _linked;
    GLuint _id;
};

#endif /* BycGLProgram_h */
