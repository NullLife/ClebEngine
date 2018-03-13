//
// Created by yangbin on 2018/3/11.
//

#ifndef CLEBENGINE_BYCFBO_H
#define CLEBENGINE_BYCFBO_H

#include "BycDefinitions.h"

class BycFBO {
public:
    BycFBO(const String& name, int width, int height);
    ~BycFBO();

    const String& getName() const;

    int getWidth() const;
    int getHeight() const;

    void bind();
    void unbind();

    GLenum check();

private:
    String _name;
    float _width, _height;

    GLuint _id;
};


#endif //CLEBENGINE_BYCFBO_H
