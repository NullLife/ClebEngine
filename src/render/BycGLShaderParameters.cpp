//
//  BycGLShaderParameters.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycGLShaderParameters.h"

#include "BycStringUtils.h"

#include "BycParamsDataSource.h"

//====================================//

BycGLShaderParameters::UniformParam::UniformParam(BycGLShaderParamField::FieldContent content,
                                                  BycGLShaderParamField::FieldDataType dataType,
                                                  int index) :
_index(-1),
_location(-1),
_cursor(0),
_content(content), _dataType(dataType) {
    String str = "";
    if (index >= 0) {
        str = "_" + BycStringUtils::toString(index);
    }
    _name = BycGLShaderParamField::toString(content) + BycGLShaderParamField::toString(dataType) + str;
}

const String& BycGLShaderParameters::UniformParam::getName() {
    return _name;
}

void BycGLShaderParameters::UniformParam::setLocation(GLint loc) {
    _location = loc;
}

const GLint BycGLShaderParameters::UniformParam::getLocation() {
    return _location;
}

void BycGLShaderParameters::UniformParam::setCursor(size_t cursor) {
    _cursor = cursor;
}

const size_t BycGLShaderParameters::UniformParam::getCursor() {
    return _cursor;
}

const BycGLShaderParamField::FieldContent BycGLShaderParameters::UniformParam::getContent() {
    return _content;
}

const BycGLShaderParamField::FieldDataType BycGLShaderParameters::UniformParam::getDataType() {
    return _dataType;
}

//====================================//

BycGLShaderParameters::BycGLShaderParameters() : _isBinded(false) {
}

BycGLShaderParameters::~BycGLShaderParameters() {
    _paramKV.clear();

    _intData.clear();
    _floatData.clear();
    _doubleData.clear();
    _intData.shrink_to_fit();
    _floatData.shrink_to_fit();
    _doubleData.shrink_to_fit();
}

void BycGLShaderParameters::addUniformParameter(BycGLShaderParamField::FieldContent content,
                                                BycGLShaderParamField::FieldDataType dataType,
                                                int index) {
    UniformParam param(content, dataType, index);

    auto iter = _paramKV.find(param.getName());
    if (iter != _paramKV.end()) {
#ifdef DEBUG
        printf("\n%s\n", "Can't add the same uniform parameter.");
        assert(false);
#endif
        return;
    }

    if (BycGLShaderParamField::isFloat(dataType)) {
        param.setCursor(_floatData.size());
        _floatData.resize(_floatData.size() + BycGLShaderParamField::getFieldComponents(dataType));
    } else if (BycGLShaderParamField::isInt(dataType)) {
        param.setCursor(_intData.size());
        _intData.resize(_intData.size() + BycGLShaderParamField::getFieldComponents(dataType));
    } else if (BycGLShaderParamField::isDouble(dataType)) {
        param.setCursor(_doubleData.size());
        _doubleData.resize(_doubleData.size() + BycGLShaderParamField::getFieldComponents(dataType));
    }

    _paramKV.insert(UniformParamKV::value_type(param.getName(), param));
}

void BycGLShaderParameters::_bindParams(GLuint programId) {
    if (_isBinded)
        return;

    auto iter = _paramKV.begin();
    while (iter != _paramKV.end()) {
        iter->second.setLocation(glGetUniformLocation(programId, iter->first.c_str()));
        ++iter;
    }
    _isBinded = true;
}

void BycGLShaderParameters::setUniformValue(const BycGLShaderParamField::FieldContent& content, int* data, int count) {
    String name = BycGLShaderParamField::toString(content) + "_" + BycStringUtils::toString(count) + "i";
    auto iter = _paramKV.find(name);
    if (iter == _paramKV.end()) {
        assert(false);
        return;
    }
    UniformParam& param = iter->second;
    size_t cursor = param.getCursor();
    if ((cursor + count) > _intData.size()) {
        assert(false);
        return;
    }

    memcpy(&_intData[cursor], data, sizeof(int) * count);
}

void BycGLShaderParameters::setUniformValue(const BycGLShaderParamField::FieldContent& content, float* data, int count) {
    String comps = BycStringUtils::toString(count);
    if (count == 9) {
        comps = "3x3";
    } else if (count == 16) {
        comps = "4x4";
    }
    String name = BycGLShaderParamField::toString(content) + "_" + comps + "f";
    auto iter = _paramKV.find(name);
    if (iter == _paramKV.end()) {
        assert(false);
        return;
    }
    UniformParam& param = iter->second;
    size_t cursor = param.getCursor();
    if ((cursor + count) > _floatData.size()) {
        assert(false);
        return;
    }

    memcpy(&_floatData[cursor], data, sizeof(float) * count);
}
void BycGLShaderParameters::setUniformValue(const BycGLShaderParamField::FieldContent& content, double* data, int count) {
    String name = BycGLShaderParamField::toString(content) + "_" + BycStringUtils::toString(count) + "d";
    auto iter = _paramKV.find(name);
    if (iter == _paramKV.end()) {
        assert(false);
        return;
    }
    UniformParam& param = iter->second;
    size_t cursor = param.getCursor();
    if ((cursor + count) > _doubleData.size()) {
        assert(false);
        return;
    }

    memcpy(&_doubleData[cursor], data, sizeof(double) * count);
}

void BycGLShaderParameters::updateLocalParams(BycParamsDataSource* dataSource) {
    auto iter = _paramKV.begin();
    while (iter != _paramKV.end()) {
        UniformParam& param = iter->second;

        const BycGLShaderParamField::FieldContent& content = param.getContent();
        switch (content) {
            case BycGLShaderParamField::FieldContent::MVP_MATRIX: {
                
                Mat4 mvp = dataSource->getProjectionMatrix() * dataSource->getViewMatrix() * dataSource->getModelMatrix();

                setUniformValue(content, &mvp[0][0], 16);
            }
                break;
        }
        ++iter;
    }
}

void BycGLShaderParameters::_updateParamsToGPU() {
    auto iter = _paramKV.begin();
    while (iter != _paramKV.end()) {
        UniformParam& param = iter->second;
        if (param.getLocation() < 0) {
            ++iter;
            continue;
        }

        GLboolean transpose = GL_FALSE;
        const BycGLShaderParamField::FieldDataType& dataType = param.getDataType();
        switch (dataType) {
            case BycGLShaderParamField::FLOAT1:
                CHECK_GL_ERROR(glUniform1fv(param.getLocation(), 1, getFloatPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::FLOAT2:
                CHECK_GL_ERROR(glUniform2fv(param.getLocation(), 1, getFloatPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::FLOAT3:
                CHECK_GL_ERROR(glUniform3fv(param.getLocation(), 1, getFloatPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::FLOAT4:
                CHECK_GL_ERROR(glUniform4fv(param.getLocation(), 1, getFloatPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::INT1:
                CHECK_GL_ERROR(glUniform1iv(param.getLocation(), 1, getIntPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::INT2:
                break;
            case BycGLShaderParamField::INT3:
                break;
            case BycGLShaderParamField::INT4:
                break;
            case BycGLShaderParamField::DOUBLE1:
                CHECK_GL_ERROR(glUniform1dv(param.getLocation(), 1, getDoublePointer(param.getCursor())));
                break;
            case BycGLShaderParamField::DOUBLE2:
                CHECK_GL_ERROR(glUniform2dv(param.getLocation(), 1, getDoublePointer(param.getCursor())));
                break;
            case BycGLShaderParamField::DOUBLE3:
                CHECK_GL_ERROR(glUniform3dv(param.getLocation(), 1, getDoublePointer(param.getCursor())));
                break;
            case BycGLShaderParamField::DOUBLE4:
                CHECK_GL_ERROR(glUniform4dv(param.getLocation(), 1, getDoublePointer(param.getCursor())));
                break;

            case BycGLShaderParamField::MATRIX_3X3:
                CHECK_GL_ERROR(glUniformMatrix3fv(param.getLocation(), 1, transpose, getFloatPointer(param.getCursor())));
                break;
            case BycGLShaderParamField::MATRIX_4X4:
                CHECK_GL_ERROR(glUniformMatrix4fv(param.getLocation(), 1, transpose, getFloatPointer(param.getCursor())));
                break;

            default:
                break;
        }
        ++iter;
    }
}

float* BycGLShaderParameters::getFloatPointer(size_t cursor) {
    return &_floatData[cursor];
}
int* BycGLShaderParameters::getIntPointer(size_t cursor) {
    return &_intData[cursor];
}
double* BycGLShaderParameters::getDoublePointer(size_t cursor) {
    return &_doubleData[cursor];
}


