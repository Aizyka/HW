#include "ppm.h"
#include "renderer.h"

int main()
{
    srand(time(NULL));

    const int size = 512;

    Image img;
    img.width     = size;
    img.height    = size;
    img.format    = "P6";
    img.max_color = 255;
    img.pixels    = new Color[img.width * img.height];

    for (int k = 0; k < 10; k++)
    {
        int x0 = rand() % size, y0 = rand() % size;
        int x1 = rand() % size, y1 = rand() % size;

        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        draw_line(img, Vector2(x0, y0), Vector2(x1, y1), Color(r, g, b));
    }

    return save_ppm("lines.ppm", img) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}