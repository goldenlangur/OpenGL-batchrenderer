#include "pch.h"

mat4_t mat4_ident(float value)
{
    mat4_t matrix;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matrix.data[i][j] = value;
            else
                matrix.data[i][j] = 0;
        }
    }
    return matrix;
}

mat4_t mat4_ortho(float left, float right, float top, float bottom, float far, float near)
{
    mat4_t mat4_ret;
    mat4_ret.data[0][0] = 2 / (right - left);
    mat4_ret.data[0][1] = 0;
    mat4_ret.data[0][2] = 0;
    mat4_ret.data[0][3] = 0;
    
    mat4_ret.data[1][0] = 0;
    mat4_ret.data[1][1] = 2 / (top - bottom);
    mat4_ret.data[1][2] = 0;
    mat4_ret.data[1][3] = 0;

    mat4_ret.data[2][0] = 0;
    mat4_ret.data[2][1] = 0;
    mat4_ret.data[2][2] = -2 / (far - near);
    mat4_ret.data[2][3] = 0;
    
    mat4_ret.data[3][0] = -((right + left) / (right - left));
    mat4_ret.data[3][1] = -((top + bottom) / (top - bottom));
    mat4_ret.data[3][2] = -((far + near) / (far - near));
    mat4_ret.data[3][3] = 1;
    
    return mat4_ret;
}

mat4_t mat4_ortho_aspect(float aspect, float size, float far, float near)
{
    return mat4_ortho(-aspect * size, aspect * size, size, -size, far, near);
}

mat4_t mat4_scale(mat4_t matrix, vec3_t vector)
{
    matrix.data[0][0] = vector.x;
    matrix.data[1][1] = vector.y;
    matrix.data[2][2] = vector.z;
    return matrix;
}

mat4_t mat4_translate(mat4_t matrix, vec3_t vector)
{
    mat4_t result = matrix;
    result.data[0][3] = matrix.data[0][0] * vector.x + matrix.data[0][1] * vector.y + matrix.data[0][2] * vector.z + matrix.data[0][3];
    result.data[1][3] = matrix.data[1][0] * vector.x + matrix.data[1][1] * vector.y + matrix.data[1][2] * vector.z + matrix.data[1][3];
    result.data[2][3] = matrix.data[2][0] * vector.x + matrix.data[2][1] * vector.y + matrix.data[2][2] * vector.z + matrix.data[2][3];
    result.data[3][3] = matrix.data[3][0] * vector.x + matrix.data[3][1] * vector.y + matrix.data[3][2] * vector.z + matrix.data[3][3];
    return result;
}