#version 150

in vec3 currVert;
in vec2 uvVert;
out vec2 texCoord;

void main() {
    gl_Position = vec4(currVert, 1.0);
    texCoord = uvVert;
}