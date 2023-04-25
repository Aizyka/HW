#include "ppm.h"
#include <fstream>
#include <iostream>

int load_ppm(const char* filename, Image& img)
{
    using namespace std;
    ifstream file(filename);
    if (!file.good())
    {
        fprintf(stderr, "Error: Failed to open file \"%s\"", filename);
        return 1;
    }
    char last_next_line = 0;
    file >> img.format >> img.width >> img.height >> img.max_color >>
        std::noskipws >> last_next_line;
    int size   = img.width * img.height;
    img.pixels = new Color[size];
    for (int i = 0; i < size; i++)
    {
        int r, g, b;
        file >> img.pixels[i].r >> img.pixels[i].g >> img.pixels[i].b;
    }
    return 0;
}
int save_ppm(const char* filename, Image img)
{
    using namespace std;
    ofstream outfile(filename);
    if (!outfile.good())
    {
        fprintf(stderr, "Error: Failed to create file \"%s\"", filename);
        return 1;
    }
    outfile << img.format << "\n"
            << img.width << " " << img.height << " " << img.max_color << "\n";
    for (int i = 0; i < img.width * img.height; i++)
    {
        outfile << img.pixels[i].r << img.pixels[i].g << img.pixels[i].b;
    }
    outfile.close();
    return 0;
}