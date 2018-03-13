//
//  BycDefinitions.h
//  BycRun
//
//  Created by FengMap on 2017/12/27.
//  Copyright © 2017年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycDefinitions_h
#define BycDefinitions_h

#include "../external/include/GL/glew.h"
#include "../external/include/glm/glm.hpp"
#include "../external/include/glm/gtc/matrix_transform.hpp"
#include "../external/include/glm/gtc/quaternion.hpp"

#include "BycStringUtils.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

//----------------------------//

#ifndef String
#define String std::string
#endif

#ifndef Vector
#define Vector std::vector
#endif

#ifndef SharedPtr
#define SharedPtr std::shared_ptr
#endif

#ifndef HashMap
#define HashMap std::unordered_map
#endif

#ifndef OrderHashMap
#define OrderHashMap std::map
#endif

////////////////////////////

#define GL_BUFFER_OFFSET(i) ((char *)NULL + (i))

#ifndef CHECK_GL_ERROR
#define CHECK_GL_ERROR(glFunc) { \
    glFunc; \
    int e = glGetError(); \
    if (e != 0) { \
        const char * errorString = ""; \
        switch(e) { \
        case GL_INVALID_ENUM:       errorString = "GL_INVALID_ENUM";        break; \
        case GL_INVALID_VALUE:      errorString = "GL_INVALID_VALUE";       break; \
        case GL_INVALID_OPERATION:  errorString = "GL_INVALID_OPERATION";   break; \
        case GL_INVALID_FRAMEBUFFER_OPERATION:  errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";   break; \
        case GL_OUT_OF_MEMORY:      errorString = "GL_OUT_OF_MEMORY";       break; \
        default:                                                            break; \
        } \
        char msgBuf[4096]; \
        Vector<String> tokens; \
        BycStringUtils::split(tokens, #glFunc, "("); \
        sprintf(msgBuf, "OpenGL error 0x%04X %s in %s at line %i for %s\n", e, errorString, __PRETTY_FUNCTION__, __LINE__, tokens[0].c_str()); \
        printf("\n\n%s\n\n", msgBuf); \
    } \
}
#endif

////////////////////////////
#define MATH_GLM

#ifdef MATH_GLM
#define Vec2 glm::vec2
#define Vec3 glm::vec3
#define Vec4 glm::vec4

#define Mat3 glm::mat3
#define Mat4 glm::mat4

#define Quaternion glm::quat
#endif

#define AXIS_X Vec3(1.0f, 0.0f, 0.0f)
#define AXIS_Y Vec3(0.0f, 1.0f, 0.0f)
#define AXIS_Z Vec3(0.0f, 0.0f, 1.0f)

////////////////////////////

//----------------------------//

#endif /* BycDefinitions_h */
