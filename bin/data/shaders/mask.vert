#version 330

uniform mat4 projection;
uniform mat4 modelview;
in vec4 position;
in vec4 color;

out vec4 vertColor;

void main(){
    
    vertColor = color;
    
    vec4 eyePos = modelview * position;
    gl_Position = position;
}
