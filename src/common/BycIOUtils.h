//
//  BycIOUtils.h
//  BycRun
//
//  Created by FengMap on 2017/12/30.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycIOUtils_h
#define BycIOUtils_h

#include "./BycDefinitions.h"

#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"

#include "./BycModelData.h"

class BycIOUtils {
public:
    static unsigned char* readImage(const String& path, int* width, int* height, int* channels, int force_channels);
    static String readFile(const String& path);
    
    static void readModelFile(const String& path, BycModelData& modelData);
    
private:
    static void processAiNode(const aiScene* ai_scene, aiNode* ai_node, BycModelData& modelData);
    static void processAiMesh(const aiScene* ai_scene, aiMesh* ai_mesh, BycModelData& modelData);
    static void processAiMaterial(aiMaterial *mtl, const aiTextureType type, const String &typeName);
};

#endif /* BycIOUtils_h */
