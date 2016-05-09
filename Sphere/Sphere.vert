#version 120

attribute vec4 vPosition;

uniform vec3 trans;

void main() {

    
    // Model transformations
    float scale = 0.5;
    // Fix the trans because of camera error
    vec3 transMod = vec3(trans.x, -trans.y, -trans.z);
    
    // Camera parameters
    vec3 cPosition = vec3(0.0, 0.0, 3.0);
    vec3 cLookAt = vec3(0.0, 0.0, 0.0);
    vec3 rightVec = vec3(1.0, 0.0, 0.0); // can be modified with roll matrix
    
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
                         transMod.x, transMod.y, transMod.z, 1.0 );
    
    mat4 scaleMat = mat4( scale,  0.0,     0.0,     0.0,
                         0.0,      scale, 0.0,     0.0,
                         0.0,      0.0,     scale, 0.0,
                         0.0,      0.0,     0.0,     1.0 );
    
    // Create view matrix
    vec3 nVec = normalize( cLookAt - cPosition );
    vec3 uVec = normalize( cross (nVec, rightVec) );
    vec3 vVec = normalize( cross (uVec, nVec) );
    
    
    mat4 viewMat = mat4( vVec.x, vVec.y, vVec.z, 0.0,
                        uVec.x, uVec.y, uVec.z, 0.0,
                        nVec.x, nVec.y, nVec.z, 0.0,
                        dot(vVec, cPosition),
                        dot(uVec, cPosition),
                        dot(nVec, cPosition), 1.0 );
    
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
}