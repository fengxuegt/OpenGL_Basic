//
// Created by fengxuegt on 2025/7/17.
//
#define STB_IMAGE_IMPLEMENTATION
#include "../application/include/stb_image.h"

#include "texture.h"
Texture::Texture() {

}

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
}

Texture::Texture(const std::string path, int unit) {
    mTextureUnit = unit;
    int channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data =  stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);


    // 创建纹理并绑定纹理单元
    glGenTextures(1, &mTexture);
    glActiveTexture(GL_TEXTURE0 + mTextureUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // glGenerateMipmap(GL_TEXTURE_2D);
    // 传输纹理数据

    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + mTextureUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);

}


