#version 330

uniform sampler2DRect particles0; // position
uniform sampler2DRect particles1; // velocity

uniform float width;
uniform float height;
uniform float time;

in vec2 vertTexCoord;

layout(location = 0) out vec4 posOut;
//layout(location = 1) out vec4 velOut;

float rand(vec2 A){
    const vec2 s = vec2(12.9898, 78.233);
    float tmp = dot(A,s);
    return fract(sin(tmp) * 43758.5453 + time);
}

void main() {
    
    vec4 texel0 = texture(particles0, vertTexCoord);
    //vec4 texel1 = texture(particles1, vertTexCoord);
    
    vec2 pos = texel0.xy;
    vec2 vel = texel0.zw;
    
    vec2 dx = vec2(1. , 0.);
    int nIter = 10;
    vec3 l = vec3(0.);
    vec3 r = vec3(0.);
    
    vec2 texPos = vec2(pos.x, height-pos.y);
    for(int i = 1; i<nIter; i++){
        l += texture(particles1, texPos - i*dx).rgb;
        r += texture(particles1, texPos + i*dx).rgb;
    }
    float left = l.x + l.y + l.z;
    float right = r.x + r.y + r.z;
    
    pos.x += (left-right)/(2.*nIter);
    
    float vy = 0.;
    vec2 dy = vec2(0., 1.);
    vec3 fy = vec3(0.);
    int nItery = 3;
    for(int i = 1; i<nItery; i++){
        fy += texture(particles1, texPos + i*dy).rgb;
    }
    
    vy = (fy.r + fy.g + fy.b)*2./nItery;
    
    pos.y += vel.y + vy;
        
    if(pos.y < 0.){
        pos.y = height;
        pos.x = width * rand(pos.xy);
    }
    
    posOut = vec4(pos, vel);
    //velOut = vec4(vel, vec2(0.0));
}

