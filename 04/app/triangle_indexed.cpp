#include "ppm.h"
#include "renderer.h"

int main()
{
    const int size = 512;

    Image img;
    img.width     = size;
    img.height    = size;
    img.format    = "P6";
    img.max_color = 255;
    img.pixels    = new Color[img.width * img.height];

    std::vector<Vector2> vertices;

    int max_triangles = 10;

    int step_x = (img.width - 1) / max_triangles;
    int step_y = (img.height - 1) / max_triangles;

    for (int i = 0; i <= max_triangles; i++)
    {
        for (int j = 0; j <= max_triangles; j++)
        {
            Vector2 v(i * step_x, j * step_y);

            vertices.push_back(v);
        }
    }

    std::vector<uint8_t> indicies;

    for (int x = 0; x < max_triangles; ++x)
    {
        for (int y = 0; y < max_triangles; ++y)
        {
            uint8_t index0 = static_cast<uint8_t>(y * (max_triangles + 1) + x);
            uint8_t index1 =
                static_cast<uint8_t>(index0 + (max_triangles + 1) + 1);
            uint8_t index2 = index1 - 1;
            uint8_t index3 = index0 + 1;

            indicies.push_back(index0);
            indicies.push_back(index1);
            indicies.push_back(index2);

            indicies.push_back(index0);
            indicies.push_back(index3);
            indicies.push_back(index1);
        }
    }

    draw_triangle_indexed(img, vertices, indicies, Color(255, 0, 0));

    return save_ppm("triangle_indexed.ppm", img) == 0 ? EXIT_SUCCESS
                                                      : EXIT_FAILURE;
}