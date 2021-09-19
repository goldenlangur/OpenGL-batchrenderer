#version 330 core
layout (location = 0) in vec3 v_pos;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec2 v_uv;
layout (location = 3) in float v_tex_index;

out vec3 e_pos;
out vec4 e_color;
out vec2 e_uv;
out float e_tex_index;

uniform mat4 u_proj_mat;
uniform mat4 u_view_mat;

void main()
{
    gl_Position = u_proj_mat * u_view_mat * vec4(v_pos.x, v_pos.y, v_pos.z, 1.0);
    //gl_Position = u_view_mat * vec4(v_pos.x, v_pos.y, v_pos.z, 1.0);

    e_color = v_color;
    e_uv = v_uv;
    e_pos = v_pos;
    e_tex_index  = v_tex_index;
}