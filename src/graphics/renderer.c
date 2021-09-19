#include "pch.h"
#include "graphics/graphics.h"

void renderer_init(renderer_t* renderer)
{
    renderer->index_count = 0;

    renderer->tex_slot_index = 0;

    vertex_t new_vertices[MAX_VERTEX_COUNT];
    renderer->quad_vertices_base = new_vertices;

    shader_init(&renderer->quad_shader);

    //Create vao, vbo, ibo
    glGenVertexArrays(1, &renderer->quad_vao);
    glBindVertexArray(renderer->quad_vao);

    glGenBuffers(1, &renderer->quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * MAX_VERTEX_COUNT, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (const void*)offsetof(vertex_t, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (const void*)offsetof(vertex_t, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (const void*)offsetof(vertex_t, uv));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (const void*)offsetof(vertex_t, tex_index));
    glEnableVertexAttribArray(3);

    uint32_t index_offset;
    for (int i = 0; i < MAX_INDEX_COUNT; i+=6)
    {
        renderer->quad_indices[i + 0] = 0 + index_offset; 
        renderer->quad_indices[i + 1] = 1 + index_offset; 
        renderer->quad_indices[i + 2] = 2 + index_offset; 
        renderer->quad_indices[i + 3] = 2 + index_offset; 
        renderer->quad_indices[i + 4] = 3 + index_offset; 
        renderer->quad_indices[i + 5] = 0 + index_offset; 
        index_offset+=4;
    }
    
    glGenBuffers(1, &renderer->quad_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->quad_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderer->quad_indices), renderer->quad_indices, GL_DYNAMIC_DRAW); 
}

void renderer_batch_flush(renderer_t* renderer)
{
    glBindVertexArray(renderer->quad_vao);
    glDrawElements(GL_TRIANGLES, renderer->index_count, GL_UNSIGNED_INT, 0);   

    renderer->index_count = 0;
}
void renderer_batch_begin(renderer_t* renderer)
{
    renderer->quad_vertices_ptr = renderer->quad_vertices_base;
}
void renderer_batch_end(renderer_t* renderer)
{
    GLsizeiptr size = (uint8_t*)renderer->quad_vertices_ptr - (uint8_t*)renderer->quad_vertices_base;
    glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, renderer->quad_vertices_base);
}

void renderer_draw_quad(renderer_t* renderer, vec3_t position, vec2_t size, vec4_t color, float tex_id)
{
    if(renderer->index_count >= MAX_INDEX_COUNT || renderer->tex_slot_index >= MAX_TEXTURE_SLOTS)
    {
        printf("Too many quads or textures, starting new batch...\n");
        renderer_batch_end(renderer);
        renderer_batch_flush(renderer);
        renderer_batch_begin(renderer);
        
    }
    renderer->quad_vertices_ptr->position = vec3_new(position.x, position.y, position.z);
    renderer->quad_vertices_ptr->color = color;
    renderer->quad_vertices_ptr->uv = vec2_new(0.0f,0.0f);
    //renderer->quad_vertices_ptr->tex_index = tex_index;
    renderer->quad_vertices_ptr++;

    renderer->quad_vertices_ptr->position = vec3_new(position.x + size.x, position.y, position.z);
    renderer->quad_vertices_ptr->color = color;
    renderer->quad_vertices_ptr->uv = vec2_new(1.0f,0.0f);
    //renderer->quad_vertices_ptr->tex_index = tex_index;
    renderer->quad_vertices_ptr++;

    renderer->quad_vertices_ptr->position = vec3_new(position.x + size.x, position.y + size.y, position.z);
    renderer->quad_vertices_ptr->color = color;
    renderer->quad_vertices_ptr->uv = vec2_new(1.0f,1.0f);
    //renderer->quad_vertices_ptr->tex_index = tex_index;
    renderer->quad_vertices_ptr++;

    renderer->quad_vertices_ptr->position = vec3_new(position.x, position.y + size.y, position.z);
    renderer->quad_vertices_ptr->color = color;
    renderer->quad_vertices_ptr->uv = vec2_new(0.0f,1.0f);
    //renderer->quad_vertices_ptr->tex_index = tex_index;
    renderer->quad_vertices_ptr++;

    renderer->index_count+=6;
}

void renderer_destroy(renderer_t* renderer)
{
   shader_destroy(&renderer->quad_shader);
   glDeleteBuffers(1, &renderer->quad_vbo);
   glDeleteBuffers(1, &renderer->quad_ibo);
   glDeleteVertexArrays(1, &renderer->quad_vao);
}
void renderer_clear(renderer_t* renderer)
{
    glClearColor(renderer->clear_color.x, renderer->clear_color.y, renderer->clear_color.z, renderer->clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}


