#include "pch.h"

#include "graphics/graphics.h"

void window_init(window_t* window)
{
    //Initialize GLFW and create GLFWwindow*
    if(!glfwInit())
        printf("%s\n", "[ERROR]: Failed to init GLFW!");
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    window->glfw_window_p = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
    if(!window)
    {
        printf("%s\n", "[ERROR]: Failed to create glfw window!");
        glfwTerminate();
    }else
    {
        glfwMakeContextCurrent(window->glfw_window_p);
        glfwSwapInterval(window->vsync);

        window->closed = 0;
        //set callbacks
    }

    //Initialze glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("%s\n", "[ERROR]: Failed to init glad!");
    }
}
void window_update(window_t* window)
{
    if(glfwWindowShouldClose(window->glfw_window_p))
        window->closed = 1;
    else
        window->closed = 0;

    glfwSwapBuffers(window->glfw_window_p);
    glfwPollEvents();

    int w, h;
    glfwGetWindowSize(window->glfw_window_p, &w, &h);
    if(w != window->width || h != window->height)
    {
        window->resized = 1;
        window->width = w;
        window->height = h;
    }else
        window->resized = 0;

}
void window_destroy(window_t* window)
{
    glfwDestroyWindow(window->glfw_window_p);
    glfwTerminate();
}