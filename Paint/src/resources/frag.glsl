#version 430 core
    in vec3 texcoord;  
    uniform vec3 icolor;
    void main() 
    {
        gl_FragColor = vec4(icolor,0); 
    }