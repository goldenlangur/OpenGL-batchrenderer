#include "pch.h"

#include "graphics/graphics.h"

const char* glsl_load_from_file(const char* path)
{
    char *buffer = 0;
    long length;
    FILE *f = fopen(path, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
        buffer[length] = '\0';
    }else
    {
        printf("[ERROR]: Failed to open file!\n");
        exit(0);
    }
    
    if (buffer)  
        return buffer; 
    else 
    {
        printf("[ERROR]: Failed write file to string!\n"); 
        exit(0);
    }
}
void shader_init(shader_t* shader)
{
    uint32_t v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &shader->v_shader_src, NULL);
    glCompileShader(v_shader);

    int succes;
    char compile_log[512];
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &succes);
    if(!succes)
    {
        glGetShaderInfoLog(v_shader, 512, NULL, compile_log);
        printf("%s %s\n", "[ERROR]: Failed to compile VERTEX shader!", compile_log);
    }

    uint32_t f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &shader->f_shader_src, NULL);
    glCompileShader(f_shader);

    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &succes);
    if(!succes)
    {
        glGetShaderInfoLog(f_shader, 512, NULL, compile_log);
        printf("%s %s\n", "[ERROR]: Failed to compile FRAGMENT shader!", compile_log);
    }
    shader->id = glCreateProgram();
    glAttachShader(shader->id,  v_shader);
    glAttachShader(shader->id, f_shader);
    glLinkProgram(shader->id);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
    glUseProgram(shader->id);
    
}
void shader_set_uniform_mat4(shader_t* shader, const char* name, mat4_t matrix)
{
    int location = glGetUniformLocation(shader->id, name);
    glUniformMatrix4fv(location, 1, GL_TRUE, &matrix.data[0][0]);
}
void shader_use(shader_t* shader)
{
    glUseProgram(shader->id);
}
void shader_destroy(shader_t* shader)
{
    glDeleteProgram(shader->id);
}