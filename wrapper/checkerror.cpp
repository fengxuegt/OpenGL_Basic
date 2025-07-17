//
// Created by fengxuegt on 2025/7/11.
//

#include "checkerror.h"
#include "glad/glad.h"
#include <string>
#include <assert.h>
#include <iostream>
void checkError() {
    std::string errorMsg;
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        switch (err) {
            case GL_INVALID_ENUM:
                errorMsg = "INVALID_ENUM";
            break;
            case GL_INVALID_VALUE:
                errorMsg = "INVALID_VALUE";
            break;
            case GL_INVALID_OPERATION:
                errorMsg = "INVALID_OPERATION";
            break;
            case GL_OUT_OF_MEMORY:
                errorMsg = "OUT_OF_MEMORY";
            break;
            default:
                errorMsg = "UNKNOWN_ERROR";
            break;
        }
        std::cerr << errorMsg << std::endl;
        assert(false);
    }
}