#include "ppm.h"
#include "renderer.h"

int main()
{
    Image img;
    img.width     = 100;
    img.height    = 100;
    img.format    = "P6";
    img.max_color = 255;
    img.pixels    = new Color[img.width * img.height];

    fill(img, Color(255, 0, 0));

    return save_ppm("square_fill.ppm", img) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}