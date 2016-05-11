#version 120

attribute vec4 vPosition;

uniform vec3 trans;

varying vec4 pos;
varying vec4 norm;

void main() {

    
    // Model transformations
    // float scale = 0.066;
    float scale = 0.1;
    
    // Camera parameters
    vec3 cPosition = vec3(0.0, 1.0, 5.0);
    vec3 cLookAt = vec3(0.0, 0.0, -1.0);
    vec3 upVec = vec3(0.0, 1.0, 0.0); // can be modified with roll matrix
    
    // View volume boundaries
    float left = -1.0;
    float right = 1.0;
    float top = 1.0;
    float bottom = -1.0;
    float near = 1.0;
    float far = -1.0;
    
    mat4 xlateMat = mat4( 1.0,     0.0,     0.0,     0.0,
                         0.0,     1.0,     0.0,     0.0,
                         0.0,     0.0,     1.0,     0.0,
                         trans.x, trans.y, trans.z, 1.0 );
    
    mat4 scaleMat = mat4( scale,  0.0,     0.0,     0.0,
                         0.0,      scale, 0.0,     0.0,
                         0.0,      0.0,     scale, 0.0,
                         0.0,      0.0,     0.0,     1.0 );
    
    // Create view matrix
    vec3 nVec = normalize( cPosition - cLookAt);
    vec3 uVec = normalize( cross(upVec, nVec) );
    vec3 vVec = normalize( cross(nVec, uVec) );
    
    
    mat4 viewMat = mat4( uVec.x, vVec.x, nVec.x, 0.0,
                        uVec.y, vVec.y, nVec.y, 0.0,
                        uVec.z, vVec.z, nVec.z, 0.0,
                        -dot(uVec, cPosition),
                        -dot(vVec, cPosition),
                        -dot(nVec, cPosition), 1.0 );
    
    // Create projection matrix
    mat4 projMat = mat4( (2.0*near)/(right-left), 0.0, 0.0, 0.0,
                        0.0, ((2.0*near)/(top-bottom)), 0.0, 0.0,
                        ((right+left)/(right-left)),
                        ((top+bottom)/(top-bottom)),
                        ((-1.0*(far+near)) / (far-near)), -1.0,
                        0.0, 0.0, ((-2.0*far*near)/(far-near)), 0.0 );
    
    // Transformation order:
    //    scale, rotate Z, rotate Y, rotate X, translate
    mat4 modelMat = xlateMat * scaleMat;
    mat4 modelViewMat = viewMat * modelMat;
    
    
    gl_Position =  projMat * viewMat * modelMat * vPosition;
    
    norm =  viewMat * modelMat * normalize(-vPosition+vec4(trans, 0.0));
    pos = viewMat * modelMat * vPosition;
}