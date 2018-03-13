//
//  BycDeferredLightApp.cpp
//  BycRun
//
//  Created by FengMap on 2018/1/30.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#include "BycDeferredLightApp.h"

#include "BycIOUtils.h"
#include "BycTransform.h"

#include "BycSceneManager.h"
#include "BycComponent.h"
#include "BycEntity.h"
#include "BycPointLight.h"

#include "BycMaterial.h"
#include "BycPass.h"
#include "BycGLShader.h"
#include "BycGLShaderParameters.h"
#include "BycGLTextureUnitState.h"

static String sBycResPath = "/Users/yangbin/ClionProjects/ClebEngine/demos/resources";

BycDeferredLightApp::BycDeferredLightApp(const String &name) : BycSuperApp(name) {
}

BycDeferredLightApp::~BycDeferredLightApp() {
}

void BycDeferredLightApp::initScene() {
    // Set ambient light color.
    _sceneManager->setAmbientLightColor(Vec4(0.5f, 0.5f, 0.5f, 1.0f));

    // Add point light.
    BycPointLight *pl0 = _sceneManager->addPointLight("PL_0");
    pl0->setPosition(Vec3(-1.f, 3.f, -2.f));

    // Get or create component.
    BycComponent *comp = _sceneManager->getComponent("deferred");

    Vector<String> planeImgs;
    planeImgs.push_back("/textures/bricks.jpg");
    BycEntity *planeEntity = loadEntity("/models/plane.obj",
                                        {
                                                "diffuseTex",
                                                "/shaders/base_tex_vs.glsl",
                                                "/shaders/base_tex_fs.glsl",
                                                planeImgs
                                        }
    );
    planeEntity->getTransform()->setScale(Vec3(5.0f));
    comp->addEntity(planeEntity);


    Vector<String> cubeImgs;
    cubeImgs.push_back("/textures/wood.png");
    BycEntity *cubeEntity = loadEntity("/models/cube.obj",
                                       {
                                               "diffuseTex",
                                               "/shaders/base_tex_vs.glsl",
                                               "/shaders/base_tex_fs.glsl",
                                               cubeImgs
                                       }
    );
    cubeEntity->getTransform()->setPosition(Vec3(0, 1.001f, 0));
    comp->addEntity(cubeEntity);
}

BycEntity *BycDeferredLightApp::loadEntity(const String &name, EntityMtlThings things) {
    BycModelData modelData;
    BycIOUtils::readModelFile(sBycResPath + name, modelData);
    BycEntity *entity = BycEntity::create(&modelData);
    assert(entity);

    entity->setName(name);

    initMaterial(entity, things);

    return entity;
}

void BycDeferredLightApp::initMaterial(BycEntity *entity, EntityMtlThings things) {
    // Create material.
    BycMaterial *mtl = new BycMaterial();
    entity->setMaterial(mtl);

    // Create pass.
    BycPass *pass = mtl->createPass(things._passName);

    // Create shaders.
    BycGLShader *verShader  = pass->createShader(GL_VERTEX_SHADER, sBycResPath + things._verShaderName);
    BycGLShader *fragShader = pass->createShader(GL_FRAGMENT_SHADER, sBycResPath + things._fragShaderName);

    verShader->addUniformParameter(BycGLShaderParamField::FieldContent::MVP_MATRIX,
                                   BycGLShaderParamField::FieldDataType::MATRIX_4X4);

    fragShader->addUniformParameter(BycGLShaderParamField::FieldContent::SAMPLER_2D,
                                    BycGLShaderParamField::FieldDataType::INT1);

    const BycSceneManager::LightArr &lights = _sceneManager->getLights();
    for (int                        i       = 0; i < lights.size(); ++i) {
        BycLight                  *l   = lights[i];
        const BycLight::LightType type = l->getLightType();
        switch (type) {
            case BycLight::LightType::DIRECTION:
                break;

            case BycLight::LightType::POINT:
                fragShader->addUniformParameter(BycGLShaderParamField::FieldContent::CAMERA_POSITION,
                                                BycGLShaderParamField::FieldDataType::FLOAT3);
                break;

            case BycLight::LightType::SPOT:
                break;
        }
    }

    Vector<int> imageIndices;
    for (int                        i       = 0; i < things._images.size(); ++i) {
        fragShader->getParameters()->setUniformValue(BycGLShaderParamField::FieldContent::SAMPLER_2D, &i, 1);
        // Add images.
        int index = mtl->addImage(sBycResPath + things._images[i]);
        imageIndices.push_back(index);

        // Create texture unit state.
        BycGLTextureUnitState *texState = pass->createGLTextureUnitState("Diffused-Bricks");
        texState->setTextureType(GL_TEXTURE_2D);
        texState->setUnit(i);

        texState->setImages(imageIndices);
    }
}
