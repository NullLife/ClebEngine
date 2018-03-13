//
//  BycGLShader.h
//  BycRun
//
//  Created by FengMap on 2018/1/20.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLShader_h
#define BycGLShader_h

#include "BycDefinitions.h"
#include "BycGLShaderParamField.h"

class BycGLShaderParameters;

class BycGLShader {
public:
    BycGLShader();

    BycGLShader(const GLenum shaderType, const String &filePath);

    ~BycGLShader();

    /// Set unique name. The name will be using in cach.
    void setUniqueName(const String &name);

    const String &getUniqueName() const;

    /// Set shader type. eg: VertexShader.
    void setType(const GLenum type);

    const GLenum getType() const;

    /// Set shader language. eg: glsl.
    void setLanguage(const String &language);

    const String &getLanguage() const;

    /// Set shader language version. eg: 410
    void setLanguageVersion(const String &version);

    const String &getLanguageVersion() const;

    /// Get the shader id. 0 is invalid.
    const GLuint getId() const;

    /// Compile the shader.
    const bool _compile(bool force = false);

    BycGLShaderParameters *getParameters();

    void addUniformParameter(BycGLShaderParamField::FieldContent content,
                             BycGLShaderParamField::FieldDataType dataType,
                             int index = -1);

private:
    String _name;
    String _filePath;
    String _language;
    String _version;

    GLenum _type;
    GLuint _id;

    BycGLShaderParameters *_params;

    bool _compiled;
};

#endif /* BycGLShader_h */
