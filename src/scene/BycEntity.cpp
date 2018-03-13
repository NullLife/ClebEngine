//
//  BycEntity.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycEntity.h"

#include "BycStringUtils.h"
#include "BycModelData.h"

#include "BycTransform.h"

#include "BycMesh.h"
#include "BycMaterial.h"

BycEntity* BycEntity::create(BycModelData* modelData) {
    if (modelData==nullptr || modelData->getData().empty())
        return nullptr;
    
    BycEntity* entity = new BycEntity();
    for (BycModelData::ChildModel* cm : modelData->getData()) {
        BycMesh* mesh = new BycMesh();
        
        BycMesh::Vertices vertices;
        BycMesh::Indices  indices;
        
        // Vertices.
        BycMesh::VertexDeclaration vdel;
        
        if (!cm->_vertices.empty())
            vdel.addField(BycMesh::VertexPacketField::VERTEX_3F);
        if (!cm->_normals.empty())
            vdel.addField(BycMesh::VertexPacketField::NORMAL_3F);
        if (!cm->_tangents.empty())
            vdel.addField(BycMesh::VertexPacketField::TANGENT_3F);
        if (!cm->_texCoords.empty())
            vdel.addField(BycMesh::VertexPacketField::TEX_COORD_3F);
    
        size_t verticeNum = cm->_vertices.size();
        for (int i=0; i<verticeNum; ++i) {
            if (vdel.getWrapping() == BycMesh::VertexPacketWrapping::CROSS) {
                if (!cm->_vertices.empty()) {
                    vertices.push_back(cm->_vertices[i].x);
                    vertices.push_back(cm->_vertices[i].y);
                    vertices.push_back(cm->_vertices[i].z);
                }
                if (!cm->_normals.empty()) {
                    vertices.push_back(cm->_normals[i].x);
                    vertices.push_back(cm->_normals[i].y);
                    vertices.push_back(cm->_normals[i].z);
                }
                if (!cm->_tangents.empty()) {
                    vertices.push_back(cm->_tangents[i].x);
                    vertices.push_back(cm->_tangents[i].y);
                    vertices.push_back(cm->_tangents[i].z);
                }
                if (!cm->_texCoords.empty()) {
                    vertices.push_back(cm->_texCoords[i].x);
                    vertices.push_back(cm->_texCoords[i].y);
                    vertices.push_back(cm->_texCoords[i].z);
                }
            }
        }
        
        // Indices.
        indices.insert(indices.begin(), cm->_indices.begin(), cm->_indices.end());
        
        mesh->setVertexDeclaration(vdel);
        mesh->setVertices(vertices);
        mesh->setIndices(indices);
        
        entity->addMesh(mesh);
    }
    return entity;
}

BycEntity::BycEntity() : _name(""), _mtl(nullptr) {
    _trans = new BycTransform();
}

BycEntity::~BycEntity() {
    if (_mtl != nullptr) {
        delete _mtl;
        _mtl = nullptr;
    }
    
    delete _trans;
}

void BycEntity::setName(const String& name) {
    _name = name;
}

const String& BycEntity::getName() const {
    return _name;
}

void BycEntity::setMaterial(BycMaterial* mtl) {
    _mtl = mtl;
}

BycMaterial* BycEntity::getMaterial() {
    return _mtl;
}

void BycEntity::addMesh(BycMesh* mesh) {
    addMeshAndMaterial(mesh, nullptr);
}

void BycEntity::addMeshAndMaterial(BycMesh* mesh, BycMaterial* mtl) {
    BycSubEntity* sub = new BycSubEntity();
    sub->setParent(this);
    sub->setMesh(mesh);
    sub->setMaterial(mtl);
    _subEntities.push_back(sub);
}

BycTransform* BycEntity::getTransform() {
    return _trans;
}

const BycEntity::SubEntityArr& BycEntity::getSubEntityArray() {
    return _subEntities;
}

//==================== SubEntity ====================//
BycSubEntity::BycSubEntity() :
BycDrawable(),
_name(""), _parent(nullptr),
_mesh(nullptr), _mtl(nullptr),
_vao(0), _verBuf(0), _idxBuf(0),
_isBinded(false) {
}

BycSubEntity::~BycSubEntity() {
    if (_mesh != nullptr) {
        delete _mesh;
        _mesh = nullptr;
    }
    if (_mtl != nullptr) {
        delete _mtl;
        _mtl = nullptr;
    }
}

void BycSubEntity::setName(const String& name) {
    _name = name;
}

const String& BycSubEntity::getName() {
    return _name;
}

void BycSubEntity::setParent(BycEntity* parant) {
    _parent = parant;
}

BycEntity* BycSubEntity::getParent() {
    return _parent;
}

void BycSubEntity::setMesh(BycMesh* mesh) {
    _mesh = mesh;
}

void BycSubEntity::setMaterial(BycMaterial* mtl) {
    _mtl = mtl;
}

BycMesh* BycSubEntity::getMesh() {
    return _mesh;
}

BycMaterial* BycSubEntity::getMaterial() {
    return _mtl;
}

const Mat4& BycSubEntity::getModelMatrix() {
    return _parent->getTransform()->getMatrix();
}

void BycSubEntity::getRenderOpt(BycRenderOpt& opt) {
    assert(_vao != 0);
    opt._vao = _vao;
    
    opt._start = 0;
    opt._count = _mesh->getIndices().size();
}

void BycSubEntity::commitData() {
    if (_vao != 0 && _verBuf !=0) {
        glBindVertexArray(_vao);
        return;
    }
    
    glGenVertexArrays(1, &_vao);
    assert(_vao > 0);
    
    glBindVertexArray(_vao);
    
    _commitMesh();
}

void BycSubEntity::bindData() {
    if (!_isBinded)
        _bindMesh();
}

void BycSubEntity::_commitMesh() {
    // Vertice.
    const BycMesh::Vertices& vertices = _mesh->getVertices();
    if (vertices.empty())
        return;
    
    glGenBuffers(1, &_verBuf);
    assert(_verBuf != 0);
    size_t vertexSize = sizeof(float) * vertices.size();
    glBindBuffer(GL_ARRAY_BUFFER, _verBuf);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertices[0], GL_STATIC_DRAW);
    
    // Indices.
    const BycMesh::Indices& indices = _mesh->getIndices();
    if (indices.empty())
        return;
    
    glGenBuffers(1, &_idxBuf);
    assert(_idxBuf != 0);
    
    size_t indicesSize = sizeof(unsigned int)*indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idxBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, &indices[0], GL_STATIC_DRAW);
}

void BycSubEntity::_bindMesh() {
    assert(_vao > 0);
    glBindVertexArray(_vao);
    const BycMesh::VertexDeclaration& decl = _mesh->getVertexDeclaration();
    const BycMesh::VertexPacketWrapping wrapping = decl.getWrapping();
    if (wrapping == BycMesh::VertexPacketWrapping::CROSS) {
        size_t offset = 0;
        
        const int fieldCount = decl.getFieldCount();
        const size_t vertexStride = decl.getVertexStride();
        for (int i=0; i<fieldCount; ++i) {
            int stride = decl.getFieldStride(decl.getField(i));
            glVertexAttribPointer(i,
                                  (GLsizei) BycStringUtils::getFieldCommponents(decl.getField(i)),
                                  GL_FLOAT,
                                  GL_FALSE,
                                  (GLsizei) vertexStride,
                                  GL_BUFFER_OFFSET(offset));
            
            glEnableVertexAttribArray(i);
            
            offset += stride;
        }
    }
    
    _isBinded = true;
}




