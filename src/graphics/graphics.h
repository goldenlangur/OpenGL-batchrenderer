#pragma once
//--------------------------------------------------//
typedef struct window_t
{
    int width, height;
    const char* title;

    int closed, vsync, resized;
    
    GLFWwindow* glfw_window_p;
}window_t;

void window_init(window_t* window);
void window_update(window_t* window);
void window_destroy(window_t* window);

//--------------------------------------------------//

typedef struct shader_t
{
    uint32_t id;
    const char* v_shader_src;
    const char* f_shader_src;
} shader_t;

const char* glsl_load_from_file(const char* path);
void shader_init(shader_t* shader);
void shader_use(shader_t* shader);
void shader_destroy(shader_t* shader);
void shader_set_uniform_mat4(shader_t* shader, const char* name, mat4_t matrix);

//--------------------------------------------------//
typedef struct texture_t
{
    unsigned int id;

    int width, height, num_channels;
    unsigned char* data;

    int from_file;
}texture_t;

texture_t texture_load_from_file(const char* path);
void texture_init(texture_t* texture);
void texture_bind(texture_t* texture, int index);
void texture_destroy(texture_t* texture);
void texture_update(texture_t* texture);
//texture_t texture_blank();
//--------------------------------------------------//
typedef struct vertex_t
{
    vec3_t position;
    vec4_t color;
    vec2_t uv;
    float tex_index;
} vertex_t;
//--------------------------------------------------//
typedef struct camera_t
{
    mat4_t proj_mat;
    mat4_t view_mat;

    vec3_t position;
    
    float size;
    float aspect;
    float near, far;
}camera_t;
//--------------------------------------------------//

#define MAX_QUAD_COUNT 10000
#define MAX_VERTEX_COUNT MAX_QUAD_COUNT*4
#define MAX_INDEX_COUNT MAX_QUAD_COUNT*6
#define MAX_TEXTURE_SLOTS 16

typedef struct renderer_t
{
    uint32_t quad_vao;
    uint32_t quad_vbo;
    uint32_t quad_ibo;

    vertex_t* quad_vertices_base;
    vertex_t* quad_vertices_ptr;
    uint32_t quad_indices[MAX_INDEX_COUNT];
    

    vertex_t quad_vertex_buffer_base;
    vertex_t quad_vertex_buffer_base_p;

    uint32_t tex_slots[MAX_TEXTURE_SLOTS];
    uint32_t tex_slot_index;

    uint32_t index_count;

    shader_t quad_shader;

    vec4_t clear_color;
}renderer_t;

void renderer_init(renderer_t* renderer);
void renderer_destroy(renderer_t* renderer);

void renderer_clear(renderer_t* renderer);

void renderer_batch_flush(renderer_t* renderer);
void renderer_batch_begin(renderer_t* renderer);
void renderer_batch_end(renderer_t* renderer);

void renderer_draw_quad(renderer_t* renderer, vec3_t position, vec2_t size, vec4_t color, float tex_id);
//void renderer_draw_tile(vec3_t position, vec3_t size, vec4_t color,float tex_index, float tile_nr, float tile_size);