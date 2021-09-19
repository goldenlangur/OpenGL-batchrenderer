#include "pch.h"

vec2_t vec2_new(float x, float y)
{
    vec2_t vec = {x, y};
    return vec;
}
vec3_t vec3_new(float x, float y, float z)
{
    vec3_t vec = {x, y, z};
    return vec;
}
vec4_t vec4_new(float x, float y, float z, float w)
{
    vec4_t vec = {x, y, z, w};
    return vec;
}