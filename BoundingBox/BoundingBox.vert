#version 120

attribute vec4 vPosition;

void main() {
    
    // Camera parameters
    vec3 cPosition = vec3(0.0, 1.0, 3.0);
    vec3 cLookAt = vec3(0.0, 0.0, -1.0);
    vec3 upVec = vec3(0.0, 1.0, 0.0); // can be modified with roll matrix
    
    // View volume boundaries
    float left = -1.0;
    float right = 1.0;
    float top = 1.0;
    float bottom = -1.0;
    float near = 1.0;
    float far = -1.0;
    
    
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
    gl_Position =  projMat * viewMat * vPosition;
}