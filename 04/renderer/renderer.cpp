#include "renderer.h"
#include <cmath>
#include <cstdint>

void fill(Image img, Color color)
{
    for (int i = 0; i < img.width * img.height; i++)
    {
        img.pixels[i].r = color.r;
        img.pixels[i].g = color.g;
        img.pixels[i].b = color.b;
    }
}

void draw_line(Image img, Vector2 vec1, Vector2 vec2, Color color)
{
    int dx = abs(vec2.x - vec1.x);
    int dy = abs(vec2.y - vec1.y);

    int sx  = (vec1.x < vec2.x) ? 1 : -1;
    int sy  = (vec1.y < vec2.y) ? 1 : -1;
    int err = dx - dy;
    int x   = vec1.x;
    int y   = vec1.y;

    int points[dx + dy + 1][2];
    int num_points = 0;

    while (true)
    {
        points[num_points][0] = x;
        points[num_points][1] = y;
        num_points++;

        if (x == vec2.x && y == vec2.y)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }

    for (int i = 0; i < num_points; i++)
    {
        int x     = points[i][0];
        int y     = points[i][1];
        int coord = y * img.width + x;

        img.pixels[coord].r = color.r;
        img.pixels[coord].g = color.g;
        img.pixels[coord].b = color.b;
    }
}

void draw_triangle(
    Image img, Vector2 vec1, Vector2 vec2, Vector2 vec3, Color color)
{
    draw_line(img, vec1, vec2, color);
    draw_line(img, vec2, vec3, color);
    draw_line(img, vec1, vec3, color);
}

void draw_triangle_indexed(Image                img,
                           std::vector<Vector2> vertices,
                           std::vector<uint8_t> indices,
                           Color                color)
{
    for (int i = 0; i < indices.size(); i += 3)
    {
        Vector2 vec1 = vertices.at(indices[i]);
        Vector2 vec2 = vertices.at(indices[i + 1]);
        Vector2 vec3 = vertices.at(indices[i + 2]);
        draw_line(img, vec1, vec2, color);
        draw_line(img, vec2, vec3, color);
        draw_line(img, vec1, vec3, color);
    }
}

double triangleArea(Vector2 p1, Vector2 p2, Vector2 p3)
{
    return abs(
        (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) /
        2.0);
}

Color interpolateColor(
    Color c1, Color c2, Color c3, double d1, double d2, double d3)
{
    double  totalDistance = d1 + d2 + d3;
    double  w1            = d1 / totalDistance;
    double  w2            = d2 / totalDistance;
    double  w3            = d3 / totalDistance;
    uint8_t r = static_cast<uint8_t>(c1.r * w1 + c2.r * w2 + c3.r * w3);
    uint8_t g = static_cast<uint8_t>(c1.g * w1 + c2.g * w2 + c3.g * w3);
    uint8_t b = static_cast<uint8_t>(c1.b * w1 + c2.b * w2 + c3.b * w3);
    return Color(r, g, b);
}

void draw_triangle_interpolated(
    Image img, Vector2 p1, Vector2 p2, Vector2 p3, Color c1, Color c2, Color c3)
{
    double triangleAreaValue = triangleArea(p1, p2, p3);
    for (int y = std::min(std::min(p1.y, p2.y), p3.y);
         y <= std::max(std::max(p1.y, p2.y), p3.y);
         y++)
    {
        for (int x = std::min(std::min(p1.x, p2.x), p3.x);
             x <= std::max(std::max(p1.x, p2.x), p3.x);
             x++)
        {
            Vector2 currentPixel(x, y);

            double a = triangleArea(currentPixel, p2, p3);
            double b = triangleArea(p1, currentPixel, p3);
            double c = triangleArea(p1, p2, currentPixel);
            if (a + b + c == triangleAreaValue)
            {
                Color interpolatedColor = interpolateColor(c1, c2, c3, a, b, c);
                int   index             = y * img.width + x;
                if (index < img.width * img.height)
                {
                    img.pixels[index] = interpolatedColor;
                }
            }
        }
    }
}
