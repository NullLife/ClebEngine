//
//  BycGLShaderParamField.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/25.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "./BycGLShaderParamField.h"

int BycGLShaderParamField::getFieldComponents(FieldDataType dataType) {
    switch (dataType) {
        case FLOAT1:
        case INT1:
        case UINT1:
        case DOUBLE1:
            return 1;
            
        case FLOAT2:
        case INT2:
        case UINT2:
        case DOUBLE2:
            return 2;
        
        case FLOAT3:
        case INT3:
        case UINT3:
        case DOUBLE3:
            return 3;

        case FLOAT4:
        case INT4:
        case UINT4:
        case DOUBLE4:
            return 4;

        case MATRIX_3X3:
            return 9;
        case MATRIX_4X4:
            return 16;
            
        default:
            return 0;
    }
}

bool BycGLShaderParamField::isFloat(FieldDataType dataType) {
    switch (dataType) {
        case FLOAT1:
        case FLOAT2:
        case FLOAT3:
        case FLOAT4:
        case MATRIX_3X3:
        case MATRIX_4X4:
            return true;
        default:
            return false;
    }
}

bool BycGLShaderParamField::isDouble(FieldDataType dataType) {
    switch (dataType) {
        case DOUBLE1:
        case DOUBLE2:
        case DOUBLE3:
        case DOUBLE4:
            return true;
            
        default:
            return false;
    }
}

bool BycGLShaderParamField::isInt(FieldDataType dataType) {
    switch (dataType) {
        case INT1:
        case INT2:
        case INT3:
        case INT4:
            
        case UINT1:
        case UINT2:
        case UINT3:
        case UINT4:
            return true;
            
        default:
            return false;
    }
}



String BycGLShaderParamField::toString(const FieldContent& content) {
    return sFieldNameKV.at(content);
}

String BycGLShaderParamField::toString(const FieldDataType& dataType) {
    return sDataTypeNameKV.at(dataType);
}

HashMap<int, String> BycGLShaderParamField::sFieldNameKV = {
    { MODEL_MATRIX, "u_modelMatrix" },
    { VIEW_MATRIX, "u_viewMatrix" },
    { PROJECTION_MATRIX, "u_projectionMatrix" },
    { MVP_MATRIX, "u_mvpMatrix" },
    
    { SAMPLER_2D, "u_diffuseTex" },
    
    { LIGHT_TYPE, "u_light.type" },
    { LIGHT_POSITION, "u_light.position" },
    { LIGHT_DIRECTION, "u_light.direction" },
    { LIGHT_CUTOFF, "u_light.cutoff" },
    { LIGHT_ATTENUATION, "u_light.attenuation" },
    { LIGHT_INTENSITY, "u_light.intensity" },
    { LIGHT_DIFFUSE_COLOR, "u_light.diffuse_color" },
    { LIGHT_SPECULAR_COLOR, "u_light.specular_color" },
    { CAMERA_POSITION, "u_camera_position" }
};

HashMap<int, String> BycGLShaderParamField::sDataTypeNameKV = {
    { FLOAT1, "_1f" },
    { FLOAT2, "_2f" },
    { FLOAT3, "_3f" },
    { FLOAT4, "_4f" },
    
    { DOUBLE1, "_1d" },
    { DOUBLE2, "_2d" },
    { DOUBLE3, "_3d" },
    { DOUBLE4, "_4d" },
    
    { INT1, "_1i" },
    { INT2, "_2i" },
    { INT3, "_3i" },
    { INT4, "_4i" },
    
    { UINT1, "_1ui" },
    { UINT2, "_2ui" },
    { UINT3, "_3ui" },
    { UINT4, "_4ui" },
    
    { MATRIX_3X3, "_3x3f" },
    { MATRIX_4X4, "_4x4f" }
};

