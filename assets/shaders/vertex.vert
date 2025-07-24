#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aUV;
out vec3 color;
out vec2 uv;
uniform float time;
uniform mat4 transformMat;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
    vec4 position = vec4(aPosition, 1.0f);
    gl_Position = projectionMatrix * viewMatrix * transformMat * position;
    color = aColor;
    uv = aUV;
}