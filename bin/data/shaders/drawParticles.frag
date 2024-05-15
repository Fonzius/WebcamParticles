#version 330

uniform vec2 resolution;
uniform sampler2DRect fboTexture;


in vec4 vertColor;
out vec4 outColor;

void main()
{
    if (dot(gl_PointCoord - 0.5, gl_PointCoord - 0.5) > 0.25)
        discard;
    else
        outColor = vec4(vec3(1.), 0.1);
}
