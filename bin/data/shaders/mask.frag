#version 330

uniform vec2 resolution;
uniform sampler2DRect fboTexture;

out vec4 fragColor;
in vec4 vertColor;

void main()
{
    vec2 coord = gl_FragCoord.xy / resolution;
    
    vec4 color = vertColor * texture(fboTexture, coord);
    
    fragColor = vec4(1.0);
}
