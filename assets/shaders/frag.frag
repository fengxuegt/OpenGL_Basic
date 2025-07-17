#version 330 core
in vec3 color;
in vec2 uv;
out vec4 outColor;
uniform float time;
uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;
void main() {
    float intensity = (sin(time) + 1.0 ) / 2.0;
    vec4 grassColor = texture(grassSampler, uv);
    vec4 landColor = texture(landSampler, uv);
    float weight = texture(noiseSampler, uv).r;
    vec3 finalColor = (grassColor * weight + landColor * (1.0f - weight)).rgb;
    outColor = vec4(finalColor, 1.0f);
}