//
//  BycImage.h
//  BycRun
//
//  Created by FengMap on 2018/1/22.
//  Copyright © 2018年 huaisukongshe@163.com. All rights reserved.
//

#ifndef BycImage_h
#define BycImage_h

#include <string>

class BycImage {
public:
    BycImage();  
    ~BycImage();
    
    void setWidth(int width);
    void setHeight(int height);
    
    const int getWidth() const;
    const int getHeight() const;

    const bool loadImage(const std::string& path);
    
    const int getChannels() const;
    
    const unsigned char* getBuffer();
    
private:
    int _originWidth;
    int _originHeight;
    
    int _rqWidth;
    int _rqHeight;
    
    int _channels;
    
    unsigned char* _buffer;
};

#endif /* BycImage_h */
