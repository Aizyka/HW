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

    draw_triangle_interpolated(img,
                               Vector2(128, 128),
                               Vector2(128, 384),
                               Vector2(384, 384),
                               Color(255, 0, 0),
                               Color(0, 255, 0),
                               Color(0, 0, 255));

    return save_ppm("triangle_interpolated.ppm", img) == 0 ? EXIT_SUCCESS
                                                           : EXIT_FAILURE;
}