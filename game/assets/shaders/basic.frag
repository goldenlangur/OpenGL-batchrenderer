#version 330 core
out vec4 f_color;

in vec3 e_pos;
in vec4 e_color;
in vec2 e_uv;
in float e_tex_index;

//uniform sampler2D u_textures[6];

void main()
{
    //int tex_index = int(e_tex_index);
    //f_color = texture(u_textures[tex_index], e_uv) * e_color;
    f_color = e_color;
}