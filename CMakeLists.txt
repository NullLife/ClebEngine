cmake_minimum_required(VERSION 3.5)
project(ClebEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#=================================//

#定义头文件目录
set(include_ext_assimp ./src/external/include/assimp)
set(include_ext_gl ./src/external/include/GL)
set(include_ext_glfw ./src/external/include/GLFW)
set(include_ext_glm ./src/external/include/glm)
set(include_ext_soil ./src/external/include/SOIL/src)

set(include_app ./src/app)
set(include_common ./src/common)
set(include_demos ./demos)
set(include_render ./src/render)
set(include_scene ./src/scene)


include_directories(
        ./
        ${include_app}
        ${include_common}
        ${include_demos} ${include_demos}/deferred
        ${include_render}
        ${include_scene}

        ${include_ext_assimp} ${include_ext_assimp}/Compiler
        ${include_ext_gl}
        ${include_ext_glfw}
        ${include_ext_glm} ${include_ext_glm}/detail ${include_ext_glm}/gtc ${include_ext_glm}/gtx ${include_ext_glm}/simd
        ${include_ext_soil} ${include_ext_soil}/original
)

#================================#

file(GLOB root_src_list ./*.c ./*.cc ./*.cpp)
file(GLOB_RECURSE demos_src_list ./demos/*.c ./demos/*.cc ./demos/*.cpp)
file(GLOB_RECURSE app_src_list ./src/app/*.c ./src/app/*.cc ./src/app/*.cpp)
file(GLOB_RECURSE common_src_list ./src/common/*.c ./src/common/*.cc ./src/common/*.cpp)
file(GLOB_RECURSE render_src_list ./src/render/*.c ./src/render/*.cc ./src/render/*.cpp)
file(GLOB_RECURSE scene_src_list ./src/scene/*.c ./src/scene/*.cc ./src/scene/*.cpp)

#=================================#
# 可执行文件
add_executable(ClebEngine
        ${root_src_list}
        ${demos_src_list}
        ${app_src_list}
        ${common_src_list}
        ${render_src_list}
        ${scene_src_list})

find_library(lib_IOKit IOKit)
find_library(lib_Cocoa Cocoa)
find_library(lib_CoreVideo CoreVideo)
find_library(lib_OpenGL OpenGL)

set(external_libs_dir ./src/external/lib)

find_library(lib_GLEW GLEW ${external_libs_dir} NO_DEFAULT_PATH)
message(lib_GLEW: ${lib_GLEW})
find_library(lib_glfw3 glfw3 ${external_libs_dir} NO_DEFAULT_PATH)
message(lib_glfw3: ${lib_glfw3})
find_library(lib_SOIL SOIL ${external_libs_dir} NO_DEFAULT_PATH)
message(lib_SOIL: ${lib_SOIL})
find_library(lib_assimpd assimpd.3.2.0 ${external_libs_dir} NO_DEFAULT_PATH)
message(lib_assimpd: ${lib_assimpd})

set(extra_libs
        ${lib_GLEW} ${lib_glfw3} ${lib_SOIL} ${lib_assimpd}
        ${lib_IOKit} ${lib_Cocoa} ${lib_CoreVideo} ${lib_OpenGL}
        )

#链接库
target_link_libraries(ClebEngine ${extra_libs})
