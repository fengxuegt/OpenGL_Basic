#include <iostream>
#include <orthographicCamera.h>
#include <perspectiveCamera.h>
#include <shader.h>

#include "core.h"
#include "checkerror.h"
#include "application.h"
#include "texture.h"
#include "camera.h"
#include "cameracontrol.h"
#include "trackballcameracontrol.h"

#include "stb_image.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseCallBack(GLFWwindow* window, int button, int action, int mods);
void cursorCallBack(GLFWwindow* window, double xpos, double ypos);
void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

Camera *camera = nullptr;
CameraControl *cameraControl = nullptr;


Shader *shader = nullptr;
Texture *grassTexture = nullptr;
Texture *landTexture = nullptr;
Texture *noiseTexture = nullptr;
GLuint allvao;
void prepareVBO() { // 练习VbO的生成与释放
    GLuint vbo;
    GL_LW_CALL(glGenBuffers(1, &vbo));
    GLuint vbos[3];
    GL_LW_CALL(glGenBuffers(3, vbos));

    GL_LW_CALL(glDeleteBuffers(1, &vbo));
    GL_LW_CALL(glDeleteBuffers(3, vbos));

}

void preparesinglevbo() {
    GLuint vbo;
    GL_LW_CALL(glGenBuffers(1, &vbo));
    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_LW_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void preparesingleVao() {
    // position vbo
    GLuint posvbo;
    GL_LW_CALL(glGenBuffers(1, &posvbo));
    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
    GL_LW_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    // color vbo
    GLuint colorvbo;
    GL_LW_CALL(glGenBuffers(1, &colorvbo));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
    float colors[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    GL_LW_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GLuint vao;
    GL_LW_CALL(glGenVertexArrays(1, &vao));
    GL_LW_CALL(glBindVertexArray(vao));
    GL_LW_CALL(glEnableVertexAttribArray(0));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
    GL_LW_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
    GL_LW_CALL(glEnableVertexAttribArray(1));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
    GL_LW_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0));
    GL_LW_CALL(glBindVertexArray(0));
}


void prepareInterLeavedVao() {
    GLuint allvbo;
    GL_LW_CALL(glGenBuffers(1, &allvbo));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, allvbo));
    float vertices[] = {
        -0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 左上（红）
         0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,  1.0f, 1.0f,// 右上（绿）
         0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,  1.0f, 0.0f,// 右下（蓝）
        -0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.0f,  0.0f, 0.0f// 左下（黄）
    };

    GL_LW_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    uint32_t eboarray[] = {
        0, 1, 2,
        0, 2, 3,
    };
    GLuint ebo;
    glGenBuffers(1, &ebo);



    GL_LW_CALL(glGenVertexArrays(1, &allvao));
    GL_LW_CALL(glBindVertexArray(allvao));
    GL_LW_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_LW_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(eboarray), eboarray, GL_STATIC_DRAW));
    GL_LW_CALL(glEnableVertexAttribArray(0));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, allvbo));
    GLuint posLocation = glGetAttribLocation(shader->getProgram(), "pos");
    GL_LW_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0));
    GL_LW_CALL(glEnableVertexAttribArray(1));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, allvbo));
    GL_LW_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3*sizeof(float))));

    GL_LW_CALL(glEnableVertexAttribArray(2));
    GL_LW_CALL(glBindBuffer(GL_ARRAY_BUFFER, allvbo));
    GL_LW_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6*sizeof(float))));

    GL_LW_CALL(glBindVertexArray(0));
}

void prepareShader() {
    shader = new Shader("assets/shaders/vertex.vert", "assets/shaders/frag.frag");
}
void prepareTexture() {
    grassTexture = new Texture ("assets/textures/goku.jpg", 0);
    landTexture = new Texture ("assets/textures/land.jpg", 1);
    noiseTexture = new Texture ("assets/textures/noise.jpg", 2);
}
glm::mat4 viewMatrix = glm::mat4(1.0f);
void prepareCamera() {
    // camera = new PerspectiveCamera(60.0f,
    //     (float)LWAPP->getWidth() / (float)LWAPP->getHeight(),
    //     0.1f,
    //     100.0f);
    float size = 6.0f;
    camera = new OrthographicCamera(-size, size, size, -size, size, -size);

    cameraControl = new TrackBallCameraControl();
    cameraControl->setCamera(camera);
}


glm::mat4 transformMat = glm::mat4(1.0f);

void preTransform() {
    // 先平移再叠加旋转
    // transformMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));

    // 先旋转，再叠加平移
    // transformMat = glm::rotate(transformMat, glm::radians(90.0f), glm::vec3(0, 0, 1));

    // 先缩放，后平移
    // transformMat = glm::scale(transformMat, glm::vec3(0.1f, 1.0f, 1.0f));

}

void doTransform() {
    // 不断旋转的目标
    // float angle = 0.1f;
    // transformMat = glm::rotate(transformMat, angle, glm::vec3(0.0f, 0.0f, 1.0f));

    // 先平移再叠加旋转
    // float angle = 0.1f;
    // transformMat = glm::rotate(transformMat, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

    // 先旋转，再叠加平移
    // transformMat = glm::translate(transformMat, glm::vec3(0.01f, 0.0f, 0.0f));

    // 先缩放，后平移
    // transformMat = glm::translate(transformMat, glm::vec3(0.01f, 0.0f, 0.0f));
}

void render() {
    GL_LW_CALL(glClear(GL_COLOR_BUFFER_BIT));
    shader->begin();
    shader->setFloat("time", glfwGetTime());
    GL_LW_CALL(glBindVertexArray(allvao));
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    grassTexture->Bind();
    landTexture->Bind();
    noiseTexture->Bind();
    shader->setUniform("grassSampler", 0);
    shader->setUniform("landSampler", 1);
    shader->setUniform("noiseSampler", 2);
    shader->setMat4("transformMat", transformMat);
    shader->setMat4("viewMatrix", camera->getViewMatrix());
    GL_LW_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    glBindVertexArray(0);
    shader->end();
}

void prepare() {
    GL_LW_CALL(glClearColor(0.5f, 0.5f, 0.05f, 1.0f));
    prepareShader();
    prepareInterLeavedVao();
    prepareTexture();
    prepareCamera();
}

int main() {
    LWAPP->setFrameBufferSizeCallback(frameBufferSizeCallback);
    LWAPP->setKeyCallBack(keyCallBack);
    LWAPP->setMouseCallBack(mouseCallBack);
    LWAPP->setCursorCallBack(cursorCallBack);
    LWAPP->setScrollCallBack(scrollCallBack);
    if (!LWAPP->init()) {
        return -1;
    }

    prepare();
    preTransform();
    while (LWAPP->update()) {
        doTransform();
        cameraControl->update();
        render();
    }

    LWAPP->destroy();
    return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    std::cout << "Framebuffer size: " << width << " x " << height << std::endl;
}
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    cameraControl->onKey(key, scancode, action, mods);
}
void mouseCallBack(GLFWwindow* window, int button, int action, int mods) {
    double xPos, ypos;
    glfwGetCursorPos(window, &xPos, &ypos);
    cameraControl->onMouse(button, action, xPos, ypos);
}

void cursorCallBack(GLFWwindow* window, double xpos, double ypos) {
    cameraControl->onCursor(xpos, ypos);
}

void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "scrollCallback " <<  yoffset << std::endl;
    cameraControl->onScroll(yoffset);
}