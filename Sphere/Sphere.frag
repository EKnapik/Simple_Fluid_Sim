#version 120

varying vec3 center;
varying vec4 pos;



vec3 phong() {
    vec3 nor = normalize(pos.xyz-center);
    vec3 lightPos = vec3(5.5, 8.0, 5.0);
    vec3 lightDir = normalize(lightPos - pos.xyz);
    vec3 lightCol = vec3(1.0, 0.9, 0.7);
    float diffCoeff, ambCoeff;
    float diff;
    vec3 amb;
    vec3 brdf;
    vec3 material = vec3(0.34, 0.73, 0.86);
    ambCoeff = 0.1;
    diffCoeff = 0.8;
    // This is calling some self reflection where the soft shadow
    // miss layers this, the ordering or priority should be fixed here
    amb = ambCoeff*vec3(1.0, 1.0, 1.0);
    diff = diffCoeff*clamp(dot(nor,lightDir), 0.0, 1.0);
    brdf = material*lightCol*(diff);
    brdf += amb;
    return brdf;
}



void main() {
    
    // a nice aqua color
    gl_FragColor = vec4(0.34, 0.73, 0.86, 1.0);
    // gl_FragColor = vec4(phong(), 1.0);
}



