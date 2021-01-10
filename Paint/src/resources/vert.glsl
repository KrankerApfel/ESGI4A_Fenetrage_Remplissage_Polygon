 #version 430 core
    in vec3 pos;
    out vec3 texcoord;
    void main()
    {
        gl_Position = vec4(pos.x, pos.y,pos.z, 1);
        texcoord = gl_Position.xyz;
    }
