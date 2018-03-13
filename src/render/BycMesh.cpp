//
//  BycMesh.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycMesh.h"

#include "BycStringUtils.h"

BycMesh::BycMesh() : _name("") {

}

BycMesh::BycMesh(const BycMesh::Vertices& vertices, const BycMesh::Indices& indices) :
_name(""),
_vertices(vertices), _indices(indices) {
}

BycMesh::~BycMesh() {
    _vertices.clear();
    _indices.clear();
    
    _vertices.shrink_to_fit();
    _indices.shrink_to_fit();
}

void BycMesh::setUniqueName(const String& name) {
    _name = name;
}

const String& BycMesh::getUniqueName() const {
    return _name;
}

void BycMesh::setVertexDeclaration(const VertexDeclaration& decl) {
    _declaration = decl;
}
const BycMesh::VertexDeclaration& BycMesh::getVertexDeclaration() const {
    return _declaration;
}

void BycMesh::setVertices(const BycMesh::Vertices vertices) {
    _vertices = vertices;
}
void BycMesh::setIndices(const BycMesh::Indices indices) {
    _indices = indices;
}

const BycMesh::Vertices& BycMesh::getVertices() const {
    return _vertices;
}

const BycMesh::Indices& BycMesh::getIndices() const {
    return _indices;
}

//====================== VertexDeclaration ======================//

BycMesh::VertexDeclaration::VertexDeclaration(BycMesh::VertexPacketWrapping wrapping) : _wrapping(wrapping) {
}

BycMesh::VertexDeclaration::~VertexDeclaration() {
    _fields.clear();
}

const BycMesh::VertexPacketWrapping BycMesh::VertexDeclaration::getWrapping() const {
    return _wrapping;
}

bool BycMesh::VertexDeclaration::addField(BycMesh::VertexPacketField field) {
    String name = sVPFieldKV.at(field);
    auto iter = std::find(_fields.begin(), _fields.end(), name);
    if (iter != _fields.end()) {
        return false;
    }
    _fields.push_back(name);
    return true;
}

bool BycMesh::VertexDeclaration::addCustomFieldName(const String& fieldName) {
    auto iter = std::find(_fields.begin(), _fields.end(), fieldName);
    if (iter != _fields.end()) {
        return false;
    }
    _fields.push_back(fieldName);
    return true;
}

const int BycMesh::VertexDeclaration::getFieldCount() const {
    return (int)_fields.size();
}

const int BycMesh::VertexDeclaration::getFieldStride(const String& field) const {
    return sizeof(float) * BycStringUtils::getFieldCommponents(field);
}

const size_t BycMesh::VertexDeclaration::getVertexStride() const {
    size_t stride = 0;
    for (const String& field : _fields) {
        stride += getFieldStride(field);
    }
    return stride;
}

const String& BycMesh::VertexDeclaration::getField(int index) const {
    return _fields[index];
}

BycMesh::VPFieldKV BycMesh::sVPFieldKV = {
    { BycMesh::VertexPacketField::VERTEX_3F, "a_vertex3f" },
    { BycMesh::VertexPacketField::NORMAL_3F, "a_normal3f" },
    { BycMesh::VertexPacketField::TANGENT_3F, "a_tangent3f" },
    { BycMesh::VertexPacketField::TEX_COORD_2F, "a_texCoord2f" },
    { BycMesh::VertexPacketField::TEX_COORD_3F, "a_texCoord3f" }
};


