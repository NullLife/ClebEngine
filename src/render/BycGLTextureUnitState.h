//
//  BycGLTextureUnitState.h
//  BycRun
//
//  Created by FengMap on 2018/2/18.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycGLTextureUnitState_h
#define BycGLTextureUnitState_h

#include "BycDefinitions.h"

class BycImage;
class BycPass;
class BycGLTexture;
class BycSceneManager;

class BycGLTextureUnitState {
public:
    enum FilterType {
        MIN,
        MAG,
        MIP
    };
    enum FilterOption {
        NEAR,
        LINEAR,
        FO_NONE
    };
    enum WrapOption {
        REPEAT = GL_REPEAT,
        MIRROR = GL_MIRRORED_REPEAT,
        CLAMP = GL_CLAMP_TO_EDGE,
        WO_NONE
    };
    struct UVWWrap {
        WrapOption u, v, w;
    };
    
    BycGLTextureUnitState();  
    ~BycGLTextureUnitState();
    
    /// Set name.
    void setName(const String& name);
    const String& getName() const;
    
    void setParent(BycPass* parent);
    BycPass* getParent();
    
    /// Set texture type.
    void setTextureType(GLenum texType);
    const GLenum getTextureType() const;

    /// Set alias.
    void setAlias(const String& alias);
    const String& getAlias() const;
    
    /// Set texture filter.
    void setFiltering(FilterType type, FilterOption opt);
    void setFiltering(FilterOption minFilter, FilterOption magFilter, FilterOption mipFilter);
    const FilterOption& getFiltering(FilterType type);
    
    // Set wrap.
    void setWrap(WrapOption wrap);
    void setWrap(WrapOption u, WrapOption v, WrapOption w);
    void setWrap(const UVWWrap& uvw);
    const UVWWrap& getUVWWrap();

    /// Attachment. (GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1...)
    void setAttachment(GLenum attachment);
    const GLenum getAttachment() const;
    
    /// Set images indices.
    void setImages(const Vector<int>& indices);
    
    /// Set texture unit.
    void setUnit(int unit);
    int getUnit();
    
    bool load(BycSceneManager* manager);
    
    BycGLTexture* getTexture();
    
private:
    bool load2DTexture(BycSceneManager* manager);
    
    BycPass* _parent;
    
    String _name;
    String _alias;
    
    GLenum _type;
    GLenum _attachment;
    
    UVWWrap _uvw;
    
    int _unit;
    
    FilterOption _minFilter;
    FilterOption _magFilter;
    FilterOption _mipFilter;
    
    Vector<int> _imageIndices;
    
    BycGLTexture* _tex;
    
    bool _isLoaded;
};

#endif /* BycGLTextureUnitState_h */
