//
//  BycGLShaderParamField.h
//  BycRun
//
//  Created by FengMap on 2018/1/25.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLShaderParamField_h
#define BycGLShaderParamField_h

#include "BycDefinitions.h"

class BycGLShaderParamField {
public:
    /** Define field type.
     */
    enum FieldContent {        
        MODEL_MATRIX,
        VIEW_MATRIX,
        PROJECTION_MATRIX,
        MVP_MATRIX,
        
        SAMPLER_2D,
        
        LIGHT_TYPE,
        LIGHT_POSITION,
        LIGHT_DIRECTION,
        LIGHT_CUTOFF,
        LIGHT_ATTENUATION,
        LIGHT_INTENSITY,
        LIGHT_DIFFUSE_COLOR,
        LIGHT_SPECULAR_COLOR,
        
        CAMERA_POSITION
    };
    
    enum FieldDataType {
        FLOAT1 = 0,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        
        DOUBLE1,
        DOUBLE2,
        DOUBLE3,
        DOUBLE4,
        
        INT1,
        INT2,
        INT3,
        INT4,
        
        UINT1,
        UINT2,
        UINT3,
        UINT4,
        
        MATRIX_3X3,
        MATRIX_4X4
    };
    
    static int getFieldComponents(FieldDataType dataType);
    static bool isFloat(FieldDataType dataType);
    static bool isDouble(FieldDataType dataType);
    static bool isInt(FieldDataType dataType);
    
    static String toString(const FieldContent& content);
    static String toString(const FieldDataType& dataType);
    
private:
    static HashMap<int, String> sFieldNameKV;
    static HashMap<int, String> sDataTypeNameKV;
};

#endif /* BycGLShaderParamField_h */
