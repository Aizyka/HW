#include "ppm.h"
#include "renderer.h"
#include <cmath>
#include <vector>

std::vector<Vector2> generate_circle_vertices(int num_segments,
                                              int radius,
                                              int size)
{
    std::vector<Vector2> vertices;
    for (int i = 0; i < num_segments; i++)
    {
        float angle = static_cast<float>(i) / static_cast<float>(num_segments) *
                      2.0f * static_cast<float>(M_PI);
        int y = static_cast<int>(std::cos(angle) * static_cast<float>(radius) +
                                 size / 2);
        int x = static_cast<int>(std::sin(angle) * static_cast<float>(radius) +
                                 size / 2);
        vertices.push_back(Vector2(x, y));
    }
    return vertices;
}

int main()
{
    const int size = 1024;

    Image img;
    img.width     = size;
    img.height    = size;
    img.format    = "P6";
    img.max_color = 255;
    img.pixels    = new Color[img.width * img.height];

    const int num_segments = 100;
    const int radius       = 512;

    std::vector<Vector2> circle_vertices =
        generate_circle_vertices(num_segments, radius, size);

    std::vector<uint8_t> indices;
    for (int i = 0; i < num_segments - 2; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    indices.push_back(0);
    indices.push_back(num_segments - 1);
    indices.push_back(1);

    draw_triangle_indexed(img, circle_vertices, indices, Color(255, 0, 0));
    return save_ppm("triangle_indexed.ppm", img) == 0 ? EXIT_SUCCESS
                                                      : EXIT_FAILURE;
}