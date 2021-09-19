#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "graphics/graphics.h"

texture_t texture_load_from_file(const char* path)
{
    stbi_set_flip_vertically_on_load(1);
    texture_t tex;
    tex.data = stbi_load(path, &tex.width, &tex.height, &tex.num_channels, 0);
    if(tex.data == NULL)
        printf("[ERROR]: Failed to open file! : %s\n", path);
    tex.from_file = 1;

    return tex;
}

void texture_init(texture_t* texture)
{
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    if(texture->data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}
void texture_update(texture_t* texture)
{
    glTextureSubImage2D(texture->id, 0, 0, 0, texture->width, texture->height, GL_RGBA, GL_UNSIGNED_BYTE, texture->data);
}
void texture_bind(texture_t* texture, int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}
void texture_destroy(texture_t* texture)
{
    glDeleteTextures(1, &texture->id);
    if(texture->from_file)
        stbi_image_free(texture->data);
}
