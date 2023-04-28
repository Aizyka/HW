#pragma once
#include "ppm.h"
#include <vector>

typedef struct Vector2
{
    int x;
    int y;
    Vector2(int x, int y)
        : x(x)
        , y(y)
    {
    }
    Vector2()
        : x(0)
        , y(0)
    {
    }
} Vector2;

void fill(Image img, Color color);
void draw_line(Image img, Vector2 vec1, Vector2 vec2, Color color);
void draw_triangle(
    Image img, Vector2 vec1, Vector2 vec2, Vector2 vec3, Color color);
void draw_triangle_indexed(Image                img,
                           std::vector<Vector2> vertices,
                           std::vector<uint8_t> indices,
                           Color                color);
void draw_triangle_interpolated(Image   img,
                                Vector2 p1,
                                Vector2 p2,
                                Vector2 p3,
                                Color   c1,
                                Color   c2,
                                Color   c3);