//
//  BycGLShaderParameters.h
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLShaderParameters_h
#define BycGLShaderParameters_h

#include "BycGLShaderParamField.h"

class BycParamsDataSource;

class BycGLShaderParameters {
    friend class BycGLShader;
public:
    /** Uniform parameter.
     */
    struct UniformParam {
    public:
        UniformParam(BycGLShaderParamField::FieldContent content,
                     BycGLShaderParamField::FieldDataType dataType,
                     int index = -1);
        
        /// Hide method.
        void _setName(const String& name);
        const String& getName();
        
        void setLocation(GLint loc);
        const GLint getLocation();
        
        void setCursor(size_t cursor);
        const size_t getCursor();
        
        const BycGLShaderParamField::FieldContent getContent();
        const BycGLShaderParamField::FieldDataType getDataType();
        
    private:
        String _name;            // Name.
        int _index;              // For array index.
        
        GLint _location;         // Location in shader. -1 is invalid.
        size_t _cursor;          // Cursor for read data.
        
        BycGLShaderParamField::FieldContent _content;
        BycGLShaderParamField::FieldDataType _dataType;
    };
    
    typedef HashMap<String, UniformParam> UniformParamKV;
    
    /// Add uniform field.
    void addUniformParameter(BycGLShaderParamField::FieldContent conent,
                             BycGLShaderParamField::FieldDataType dataType,
                             int index = -1);
    
    // Set uniform value.
    void setUniformValue(const BycGLShaderParamField::FieldContent& conent, int* data, int count);
    void setUniformValue(const BycGLShaderParamField::FieldContent& conent, float* data, int count);
    void setUniformValue(const BycGLShaderParamField::FieldContent& conent, double* data, int count);
    
    /// Bind uniform parameters with shaders.
    void _bindParams(GLuint programId);
    
    /// Update values of uniform parameters in CPU.
    void updateLocalParams(BycParamsDataSource* dataSource);
    
    /// Update values of uniform parameters in GPU.
    void _updateParamsToGPU();
    
    float* getFloatPointer(size_t cursor);
    int* getIntPointer(size_t cursor);
    double* getDoublePointer(size_t cursor);
    
private:
    BycGLShaderParameters();
    ~BycGLShaderParameters();
    
    typedef Vector<int> IntUniformArr;
    typedef Vector<float> FloatUniformArr;
    typedef Vector<double> DoubleUniformArr;
    
    UniformParamKV _paramKV;
    
    IntUniformArr _intData;
    FloatUniformArr _floatData;
    DoubleUniformArr _doubleData;
    
    bool _isBinded;
};

#endif /* BycGLShaderParameters_h */
