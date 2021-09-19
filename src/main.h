#pragma once
#include "pch.h"

#include "graphics/graphics.h"

void print_fps()
{
    static int frames = 0;
    static double last_time;
    double current_time = glfwGetTime();
    frames++;
    if ( current_time - last_time >= 1.0 )
    {
        printf("Framerate: %d \n", frames);
        frames = 0;
        last_time  = current_time;
    }
}