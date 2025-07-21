//
// Created by fengxuegt on 2025/7/13.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>

#include "core.h"
class Shader {
public:
    Shader();
    Shader(std::string vertexPath, std::string fragmentPath);

    ~Shader();

    void setFloat(std::string name, float value);
    void setUniform(std::string name, float value);
    void setMat4(std::string name, glm::mat4 matrix);

    void begin();
    void end();
    GLuint getProgram() {
        return mProgram;
    }

private:
    std::string readFileToString(const std::string& filePath);
    void checkShader(GLuint target, std::string type);
      GLuint mProgram{0};

};



#endif //SHADER_H
