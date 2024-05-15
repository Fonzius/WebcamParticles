#version 330

/*
 Original Edge Detection Shader by Gijs on Shadertoy
 link: https://www.shadertoy.com/view/td2yDm
*/

uniform sampler2DRect fboTexture;
uniform vec2 resolution;

out vec4 fragColor;
in vec4 vertColor;

void main() {
    // I suggest playing around with this value
    
    vec2 coord = gl_FragCoord.xy;
   
    float h = 0.5;
        
    vec4 o = texture(fboTexture, (coord + vec2( 0, 0)));
    vec4 n = texture(fboTexture, (coord + vec2( 0, h)));
    vec4 e = texture(fboTexture, (coord + vec2( h, 0)));
    vec4 s = texture(fboTexture, (coord + vec2( 0,-h)));
    vec4 w = texture(fboTexture, (coord + vec2(-h, 0)));
    
    vec4 dy = (n - s)*.5;
    vec4 dx = (e - w)*.5;
    
    vec4 edge = sqrt(dx*dx + dy*dy);
    //vec4 angle = atan(dy, dx);
   
    fragColor = vec4(vec3(step(0.01, edge.g)), 1.);
    
   
    // Below is another way to make an edge detector,
    // It is invariant under intensity-scalings of the image
    // and linear illumination differences.
    // This should make it more "human-sight" like
   /*
    vec4 laplacian = n + e + s + w - 4.0 * o;
    float edge = abs(laplacian.x/o.x + laplacian.y/o.y + laplacian.z/o.z);
    fragColor = vec4(vec3(step(0.5, edge)), 1.);
     */
    
    
    
}
