//
//  BycEntity.h
//  BycRun
//
//  Created by FengMap on 2018/1/19.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycEntity_h
#define BycEntity_h

#include "BycDrawable.h"
#include "BycRenderOpt.h"

class BycSubEntity;
class BycMaterial;
class BycMesh;
class BycTransform;

class BycModelData;

/** Entity.
 */
class BycEntity {
public:
    /// Create entity by model data.
    static BycEntity* create(BycModelData* modelData);
    
    BycEntity();  
    virtual ~BycEntity();
    
    typedef Vector<BycSubEntity*> SubEntityArr;
    
    /// Set name.
    void setName(const String& name);
    const String& getName() const;
    
    /// Set global material.
    void setMaterial(BycMaterial* mtl);
    BycMaterial* getMaterial();
    
    /// Add mesh.
    void addMesh(BycMesh* mesh);
    void addMeshAndMaterial(BycMesh* mesh, BycMaterial* mtl);
    
    /// Get transform.
    BycTransform* getTransform();
    
    const SubEntityArr& getSubEntityArray();
    
protected:
    String _name;
    
    BycMaterial* _mtl;
    
    SubEntityArr _subEntities;
    
    BycTransform* _trans;
};


class BycSubEntity : public BycDrawable {
    friend class BycEntity;
public:
    void setName(const String& name);
    const String& getName();
    
    void setParent(BycEntity* parant);
    BycEntity* getParent();
    
    void setMesh(BycMesh* mesh);
    void setMaterial(BycMaterial* mtl);
    
    virtual BycMesh* getMesh();
    virtual BycMaterial* getMaterial();
    
    virtual const Mat4& getModelMatrix();
    
    virtual void getRenderOpt(BycRenderOpt& opt);
    
    virtual void commitData();
    virtual void bindData();
    
private:
    BycSubEntity();
    ~BycSubEntity();
    
    void _commitMesh();
    void _bindMesh();
    
    String _name;
    BycEntity* _parent;
    
    BycMesh* _mesh;
    BycMaterial* _mtl;
    
    /// Request.
    GLuint _vao;
    GLuint _verBuf;
    GLuint _idxBuf;
    
    bool _isBinded;
};

#endif /* BycEntity_h */
