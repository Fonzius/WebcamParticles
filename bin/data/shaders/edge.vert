#version 330

uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 inColor;

out vec4 vertColor;

void main() {
    vertColor = inColor;

    gl_Position = modelViewProjectionMatrix * position;
}

