//
//  BycMesh.h
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycMeshes_h
#define BycMeshes_h

#include "BycDefinitions.h"

class BycMesh {
public:
    /// Vertex data wrapping.
    enum VertexPacketWrapping {
        CROSS = 0,        // One buffer: {[vertex, tex_coord, normal, ...], [vertex, tex_coord, normal, ...], ...}
        ALIGH,            // One buffer: {[vertices], [tex_coords], [normals], ...}
        SEPARATION        // Many buffers: {vertices}, {tex_coords}, {normals}, ...
    };
    
    enum VertexPacketField {
        VERTEX_3F = 0,
        NORMAL_3F,
        TANGENT_3F,
        TEX_COORD_2F,
        TEX_COORD_3F
    };
    
    typedef Vector<String> VPFieldArr;
    typedef HashMap<int, String> VPFieldKV;
    
    static VPFieldKV sVPFieldKV;
    
    
    /// Define Vertex construction. [POINT, TEXTURE_COORDINATE, NORMAL, ...]
    struct VertexDeclaration {
    public:
        VertexDeclaration(VertexPacketWrapping wrapping = CROSS);
        ~VertexDeclaration();
        
        const VertexPacketWrapping getWrapping() const;
        
        /// Add field in vertex struction. It will be failure when the field is already existed.
        bool addField(VertexPacketField field);
        /// Add custom field in vertex struction. It will be failure when the field is already existed.
        bool addCustomFieldName(const String& fieldName);
        
        const int getFieldCount() const;
        const int getFieldStride(const String& field) const;
        
        const size_t getVertexStride() const;
        
        const String& getField(int index) const;
        
    private:
        VertexPacketWrapping _wrapping;
        VPFieldArr _fields;
    };
    
    /// Define the container of base data.
    typedef Vector<float> Vertices;
    typedef Vector<unsigned int> Indices;
    
    BycMesh();
    BycMesh(const Vertices& vertices, const Indices& indices);
    ~BycMesh();
    
    /// If it no unique name, then will be release right now when it is used.
    void setUniqueName(const String& name);
    const String& getUniqueName() const;
    
    void setVertexDeclaration(const VertexDeclaration& decl);
    const VertexDeclaration& getVertexDeclaration() const;
    
    void setVertices(const Vertices vertices);
    void setIndices(const Indices indices);
    
    const Vertices& getVertices() const;
    const Indices& getIndices() const;
    
private:
    String _name;

    VertexDeclaration _declaration;
    
    Vertices _vertices;
    Indices _indices;
};

#endif /* BycMesh_h */
