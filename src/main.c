#include "main.h"

typedef struct game_data_t
{
    window_t window;
    renderer_t renderer;
    camera_t camera;
} game_data_t;

void game_init(game_data_t *game_data)
{
    game_data->window.width = 1280;
    game_data->window.height = 720;
    game_data->window.title = "Hello World";
    game_data->window.vsync = 1;

    game_data->renderer.clear_color = vec4_new(1.0f, 1.0f, 1.0f, 1.0);
    game_data->renderer.quad_shader.v_shader_src = glsl_load_from_file("assets/shaders/basic.vert");
    game_data->renderer.quad_shader.f_shader_src = glsl_load_from_file("assets/shaders/basic.frag");

    game_data->camera.near = 0.1f;
    game_data->camera.far = 100;
    game_data->camera.size = 10.0f;
    game_data->camera.position = vec3_new(0, 0, 0);
    game_data->camera.aspect = (float)game_data->window.width / (float)game_data->window.height;
    game_data->camera.proj_mat = mat4_ortho_aspect(game_data->camera.aspect, game_data->camera.size, game_data->camera.far, game_data->camera.near);
}

void game_start(game_data_t *game_data)
{
}

void game_update(game_data_t *game_data)
{
    //Update Camera controller
    float cam_speed = 0.4f;
    if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_W) == GLFW_PRESS)
        game_data->camera.position.y += cam_speed;
    else if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_S) == GLFW_PRESS)
        game_data->camera.position.y -= cam_speed;

    if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_A) == GLFW_PRESS)
        game_data->camera.position.x -= cam_speed;
    else if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_D) == GLFW_PRESS)
        game_data->camera.position.x += cam_speed;

    if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        game_data->camera.size -= cam_speed;
        game_data->camera.proj_mat = mat4_ortho_aspect(game_data->camera.aspect, game_data->camera.size, game_data->camera.far, game_data->camera.near);
    }
    else if (glfwGetKey(game_data->window.glfw_window_p, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        game_data->camera.size += cam_speed;
        game_data->camera.proj_mat = mat4_ortho_aspect(game_data->camera.aspect, game_data->camera.size, game_data->camera.far, game_data->camera.near);
    }
}
void game_render(game_data_t *game_data)
{
    if (game_data->window.resized)
    {
        game_data->camera.aspect = (float)game_data->window.width / (float)game_data->window.height;
        game_data->camera.proj_mat = mat4_ortho_aspect(game_data->camera.aspect, game_data->camera.size, game_data->camera.far, game_data->camera.near);
    }
    game_data->camera.view_mat = mat4_translate(mat4_ident(1.0f), vec3_new(-game_data->camera.position.x, -game_data->camera.position.y, -game_data->camera.position.z));

    shader_use(&game_data->renderer.quad_shader);

    int loc = glGetUniformLocation(game_data->renderer.quad_shader.id, "u_textures");
    glUniform1iv(loc, 16, (int *)game_data->renderer.tex_slots);

    shader_set_uniform_mat4(&game_data->renderer.quad_shader, "u_proj_mat", game_data->camera.proj_mat);
    shader_set_uniform_mat4(&game_data->renderer.quad_shader, "u_view_mat", game_data->camera.view_mat);

    float inc = 0.5f;
    for (float x = 0; x < 100; x += 1 + inc)
    {
        for (float y = 0; y < 99; y += 1 + inc)
        {
            float color = (x / 100 + y / 100) / 2;
            renderer_draw_quad(&game_data->renderer, vec3_new(x + inc, y + inc, 0), vec2_new(1, 1), vec4_new(1 - x / 100, 1 - y / 100, color, 1), 0);
        }
    }
}
void game_destroy(game_data_t *game_data)
{
}

int main(void)
{
    //Contains all data for the game
    game_data_t game_data;

    game_init(&game_data);

    window_init(&game_data.window);
    renderer_init(&game_data.renderer);

    game_start(&game_data);

    while (!game_data.window.closed)
    {
        print_fps();

        //Update everything engine
        window_update(&game_data.window);
        renderer_clear(&game_data.renderer);

        renderer_batch_begin(&game_data.renderer);
        game_render(&game_data);
        renderer_batch_end(&game_data.renderer);
        renderer_batch_flush(&game_data.renderer);

        game_update(&game_data);
    }
    game_destroy(&game_data);

    renderer_destroy(&game_data.renderer);
    window_destroy(&game_data.window);
    return 0;
}
