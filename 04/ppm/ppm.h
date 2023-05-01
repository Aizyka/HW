#pragma once
#include <string>

#pragma pack(push, 1)
typedef struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    Color(uint8_t r, uint8_t g, uint8_t b)
        : r(r)
        , g(g)
        , b(b)
    {
    }
    Color()
        : r(0)
        , g(0)
        , b(0)
    {
    }
} Color;
#pragma pack(pop)

typedef struct Image
{
    int         width;
    int         height;
    int         max_color;
    std::string format;
    Color*      pixels;

    Image(int width, int height)
        : width(width)
        , height(height)
    {
        pixels = (Color*)calloc(width * height, sizeof(Color));
    }
    Image() {}
} Image;

int load_ppm(const char* filename, Image& img);
int save_ppm(const char* filename, Image img);
