//
// Created by fengxuegt on 2025/7/13.
//

#include "shader.h"

#include <fstream>
#include <sstream>
#include "../wrapper/include/checkerror.h"
#include <iostream>

Shader::Shader() {

}

std::string Shader::readFileToString(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filePath);
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

void Shader::checkShader(GLuint target, std::string type) {
    int success;
    char infoLog[512];
    if (type == "COMPILE") {
        GL_LW_CALL(glGetShaderiv(target, GL_COMPILE_STATUS, &success));
        if (!success) {
            glGetShaderInfoLog(target, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    } else if (type == "LINK") {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(target, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    } else {
        std::cout << "Unknown shader type: " << type << std::endl;
    }
}

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
    std::string vertexStr = readFileToString(vertexPath);
    const char* vertexCode = vertexStr.c_str();

    std::string fragmentStr = readFileToString(fragmentPath);
    const char* fragmentCode = fragmentStr.c_str();

    // std::cout << vertexCode << std::endl;
    // std::cout << fragmentCode << std::endl;


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL_LW_CALL(glShaderSource(vertexShader, 1, &vertexCode, NULL));
    GL_LW_CALL(glShaderSource(fragmentShader, 1, &fragmentCode, NULL));
    GL_LW_CALL(glCompileShader(vertexShader));
    checkShader(vertexShader, "COMPILE");
    GL_LW_CALL(glCompileShader(fragmentShader));
    checkShader(fragmentShader, "COMPILE");
    mProgram = glCreateProgram();
    GL_LW_CALL(glAttachShader(mProgram, vertexShader));
    GL_LW_CALL(glAttachShader(mProgram, fragmentShader));
    GL_LW_CALL(glLinkProgram(mProgram));
    checkShader(mProgram, "LINK");
    GL_LW_CALL(glDeleteShader(vertexShader));
    GL_LW_CALL(glDeleteShader(fragmentShader));
}



Shader::~Shader() {

}

void Shader::setFloat(std::string name, float value) {
    glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::setUniform(std::string name, float value) {
    glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::begin() {
    glUseProgram(mProgram);
}

void Shader::end() {
    glUseProgram(0);
}

