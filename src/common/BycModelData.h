//
//  BycModelData.h
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycModelData_h
#define BycModelData_h

#include "./BycDefinitions.h"

class BycModelData {
public:
    struct ChildModel {
        Vector<Vec3> _vertices;
        Vector<Vec3> _normals;
        Vector<Vec3> _tangents;
        Vector<Vec3> _texCoords;
        
        Vector<unsigned int> _indices;

        Vector<String> _images;
    };
    
    BycModelData();
    ~BycModelData();
    
    void _addChildModel(ChildModel* model);
    
    const Vector<ChildModel*>& getData();
      
private:
    Vector<ChildModel*> _data;
};

#endif /* BycModelData_h */
