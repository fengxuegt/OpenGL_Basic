//
// Created by fengxuegt on 2025/7/17.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include "core.h"
#include <string>

class Texture {
public:
    Texture();
    ~Texture();
    void Bind();

    Texture(const std::string path, int unit);


private:
    GLuint mTexture;
    int mWidth, mHeight;
    int mTextureUnit;

};



#endif //TEXTURE_H
