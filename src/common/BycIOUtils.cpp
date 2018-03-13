//
//  BycIOUtils.cpp
//  BycRun
//
//  Created by FengMap on 2017/12/30.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#include "BycIOUtils.h"

#include <SOIL.h>

#include <fstream>
#include <sstream>
#include <assert.h>


unsigned char* BycIOUtils::readImage(const std::string &path, int* width, int* height, int* channels, int force_channels) {
    // Read image data.
    unsigned char *data = SOIL_load_image(path.c_str(), width, height, channels, force_channels);
    return data;
}


std::string BycIOUtils::readFile(const String& path) {
    // Open the file.
    std::ifstream file;
    file.open(path.c_str(), std::ios::in | std::ios::binary);
    
    if (!file.is_open()) {
        printf("======== BycIOUtils::read ======== \n Can not open the file: %s\n", path.c_str());
        assert(false);
    }
    
    // Read whole file into buffer
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    return buffer.str();
}

void BycIOUtils::readModelFile(const String& path, BycModelData& modelData) {
    // For assimp lib to read file.
    int assimpVertComps = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_FlipUVs;
    Assimp::Importer import;
    const aiScene *ai_scene = import.ReadFile(path, assimpVertComps);
    
    if (!ai_scene || ai_scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !ai_scene->mRootNode) {
        printf("========== ReadModelFile errors ============ \n %s \n", import.GetErrorString());
        return;
    }
    
    processAiNode(ai_scene, ai_scene->mRootNode, modelData);
}


void BycIOUtils::processAiNode(const aiScene* ai_scene, aiNode* ai_node, BycModelData& modelData) {
    // Process meshes of current node.
    for (unsigned int i = 0; i < ai_node->mNumMeshes; i++) {
        aiMesh *ai_mesh = ai_scene->mMeshes[ai_node->mMeshes[i]];
        processAiMesh(ai_scene, ai_mesh, modelData);
    }
    // Process node recursively.
    for (unsigned int i = 0; i < ai_node->mNumChildren; i++) {
        processAiNode(ai_scene, ai_node->mChildren[i], modelData);
    }
}

void BycIOUtils::processAiMesh(const aiScene* ai_scene, aiMesh* ai_mesh, BycModelData& modelData) {
    if (ai_mesh->mNumVertices <= 0)
        return;
    
    BycModelData::ChildModel* childModel = new BycModelData::ChildModel();
    
    const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
    Vector<float> vertices;
    for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
        const aiVector3D pos = ai_mesh->mVertices[i];
        const aiVector3D nor = ai_mesh->mNormals[i];
        const aiVector3D tangent = ai_mesh->mTangents[i];
        const aiVector3D texCoord = ai_mesh->HasTextureCoords(0)? ai_mesh->mTextureCoords[0][i] : aiZeroVector;
        
        childModel->_vertices.push_back(Vec3(pos.x, pos.y, pos.z));
        childModel->_normals.push_back(Vec3(nor.x, nor.y, nor.z));
        childModel->_tangents.push_back(Vec3(tangent.x, tangent.y, tangent.z));
        childModel->_texCoords.push_back(Vec3(texCoord.x, texCoord.y, texCoord.z));
    }
    
    for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i) {
        aiFace ai_face = ai_mesh->mFaces[i];
        for (unsigned int j = 0; j < ai_face.mNumIndices; ++j) {
            childModel->_indices.push_back(ai_face.mIndices[j]);
        }
    }
    
    modelData._addChildModel(childModel);
}

void BycIOUtils::processAiMaterial(aiMaterial *mtl, const aiTextureType type, const String &typeName) {
    
}
