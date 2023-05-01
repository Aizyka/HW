#include <SDL3/SDL.h>

#include "ppm.h"
#include "renderer.h"
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace std;

struct Vertex
{
    double x = 0;
    double y = 0;
    double r = 0;
    double g = 0;
    double b = 0;
};

struct Uniform
{
    double f0 = 0;
    double f1 = 0;
    double f2 = 0;
};

struct GFXProgram
{
    virtual void   set_uniform(const Uniform&)         = 0;
    virtual Vertex vertex_shader(const Vertex& v_in)   = 0;
    virtual Color  fragment_shader(const Vertex& v_in) = 0;
};

vector<Vector2> pixels_positions(Vector2 start, Vector2 end)
{
    vector<Vector2> result;
    int             x0 = start.x;
    int             y0 = start.y;
    int             x1 = end.x;
    int             y1 = end.y;

    auto plot_line_low = [&](int x0, int y0, int x1, int y1)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int yi = 1;
        if (dy < 0)
        {
            yi = -1;
            dy = -dy;
        }
        int D = 2 * dy - dx;
        int y = y0;

        for (int x = x0; x <= x1; ++x)
        {
            result.push_back(Vector2{ x, y });
            if (D > 0)
            {
                y += yi;
                D -= 2 * dx;
            }
            D += 2 * dy;
        }
    };

    auto plot_line_high = [&](int x0, int y0, int x1, int y1)
    {
        int dx = x1 - x0;
        int dy = y1 - y0;
        int xi = 1;
        if (dx < 0)
        {
            xi = -1;
            dx = -dx;
        }
        int D = 2 * dx - dy;
        int x = x0;

        for (int y = y0; y <= y1; ++y)
        {
            result.push_back(Vector2{ x, y });
            if (D > 0)
            {
                x += xi;
                D -= 2 * dy;
            }
            D += 2 * dx;
        }
    };

    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            plot_line_low(x1, y1, x0, y0);
        }
        else
        {
            plot_line_low(x0, y0, x1, y1);
        }
    }
    else
    {
        if (y0 > y1)
        {
            plot_line_high(x1, y1, x0, y0);
        }
        else
        {
            plot_line_high(x0, y0, x1, y1);
        }
    }
    return result;
}

double vec_length(Vector2 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double interpolate(const double f0, const double f1, const double t)
{
    assert(t >= 0.0);
    assert(t <= 1.0);
    return f0 + (f1 - f0) * t;
}

Vertex interpolate(const Vertex& v0, const Vertex& v1, const double t)
{
    return { interpolate(v0.x, v1.x, t),
             interpolate(v0.y, v1.y, t),
             interpolate(v0.r, v1.r, t),
             interpolate(v0.g, v1.g, t),
             interpolate(v0.b, v1.b, t) };
}

void raster_one_horizontal_line(const Vertex&   left_Vertex,
                                const Vertex&   right_Vertex,
                                vector<Vertex>& out)
{
    size_t num_of_pixels_in_line =
        static_cast<size_t>(round(abs(left_Vertex.x - right_Vertex.x)));
    if (num_of_pixels_in_line > 0)
    {
        // use +1 pixels to garantee no empty black pixels
        for (size_t p = 0; p <= num_of_pixels_in_line + 1; ++p)
        {
            double t_pixel =
                static_cast<double>(p) / (num_of_pixels_in_line + 1);
            Vertex pixel = interpolate(left_Vertex, right_Vertex, t_pixel);

            out.push_back(pixel);
        }
    }
    else
    {
        out.push_back(left_Vertex);
    }
}

vector<Vertex> raster_horizontal_triangle(const Vertex& single,
                                          const Vertex& left,
                                          const Vertex& right)
{
    vector<Vertex> out;
    size_t num_of_hlines = static_cast<size_t>(round(abs(single.y - left.y)));

    if (num_of_hlines > 0)
    {
        for (size_t i = 0; i <= num_of_hlines; ++i)
        {
            double t_vertical   = static_cast<double>(i) / num_of_hlines;
            Vertex left_Vertex  = interpolate(left, single, t_vertical);
            Vertex right_Vertex = interpolate(right, single, t_vertical);

            raster_one_horizontal_line(left_Vertex, right_Vertex, out);
        }
    }
    else
    {
        raster_one_horizontal_line(left, right, out);
    }

    return out;
}

vector<Vertex> rasterize_triangle(const Vertex& v0,
                                  const Vertex& v1,
                                  const Vertex& v2)
{
    vector<Vertex> out;

    array<const Vertex*, 3> in_vertices{ &v0, &v1, &v2 };
    sort(begin(in_vertices),
         end(in_vertices),
         [](const Vertex* left, const Vertex* right)
         { return left->y < right->y; });

    const Vertex& top    = *in_vertices.at(0);
    const Vertex& middle = *in_vertices.at(1);
    const Vertex& bottom = *in_vertices.at(2);

    Vector2 start{ static_cast<int32_t>(round(top.x)),
                   static_cast<int32_t>(round(top.y)) };
    Vector2 end{ static_cast<int32_t>(round(bottom.x)),
                 static_cast<int32_t>(round(bottom.y)) };
    Vector2 middle_pos{ static_cast<int32_t>(round(middle.x)),
                        static_cast<int32_t>(round(middle.y)) };

    if (start.x == end.x && start.y == end.y)
    {
        Vector2 delta = Vector2(start.x - middle_pos.x, start.y - middle_pos.y);
        size_t  count_pixels = 4 * (abs(delta.x) + abs(delta.y) + 1);
        for (size_t i = 0; i < count_pixels; ++i)
        {
            double t      = static_cast<double>(i) / count_pixels;
            Vertex Vertex = interpolate(top, middle, t);
            out.push_back(Vertex);
        }

        return out;
    }

    if (start.x == middle_pos.x && start.y == middle_pos.y)
    {
        Vector2 delta        = Vector2(start.x - end.x, start.y - end.y);
        size_t  count_pixels = 4 * (abs(delta.x) + abs(delta.y) + 1);
        for (size_t i = 0; i < count_pixels; ++i)
        {
            double t      = static_cast<double>(i) / count_pixels;
            Vertex Vertex = interpolate(top, bottom, t);
            out.push_back(Vertex);
        }

        return out;
    }

    if (end.x == middle_pos.x && end.y == middle_pos.y)
    {
        Vector2 delta = Vector2(start.x - middle_pos.x, start.y - middle_pos.y);
        size_t  count_pixels = 4 * (abs(delta.x) + abs(delta.y) + 1);
        for (size_t i = 0; i < count_pixels; ++i)
        {
            double t      = static_cast<double>(i) / count_pixels;
            Vertex Vertex = interpolate(top, middle, t);
            out.push_back(Vertex);
        }

        return out;
    }

    vector<Vector2> longest_side_line = pixels_positions(start, end);

    auto it_middle =
        find_if(std::begin(longest_side_line),
                std::end(longest_side_line),
                [&](const Vector2& pos)
                { return pos.y == static_cast<int32_t>(round(middle.y)); });
    assert(it_middle != std::end(longest_side_line));
    Vector2 second_middle = *it_middle;
    double  t{ 0 };
    double  end_start = vec_length(Vector2(end.x - start.x, end.y - start.y));
    if (end_start > 0)
    {
        double middle_start = vec_length(
            Vector2(second_middle.x - start.x, second_middle.y - start.y));
        t = middle_start / end_start;
    }
    else
    {
        vector<Vector2> line = pixels_positions(start, middle_pos);
    }
    Vertex         second_middle_Vertex = interpolate(top, bottom, t);
    vector<Vertex> top_triangle =
        raster_horizontal_triangle(top, middle, second_middle_Vertex);

    vector<Vertex> bottom_triangle =
        raster_horizontal_triangle(bottom, middle, second_middle_Vertex);

    out.insert(std::end(out), std::begin(top_triangle), std::end(top_triangle));
    out.insert(
        std::end(out), std::begin(bottom_triangle), std::end(bottom_triangle));

    return out;
}
void draw_triangles(GFXProgram*       program_,
                    Image             image,
                    vector<Vertex>&   vertices,
                    vector<uint16_t>& indices)
{
    for (size_t index = 0; index < indices.size(); index += 3)
    {
        const uint16_t index0 = indices.at(index + 0);
        const uint16_t index1 = indices.at(index + 1);
        const uint16_t index2 = indices.at(index + 2);

        const Vertex& v0 = vertices.at(index0);
        const Vertex& v1 = vertices.at(index1);
        const Vertex& v2 = vertices.at(index2);

        const Vertex v0_ = program_->vertex_shader(v0);
        const Vertex v1_ = program_->vertex_shader(v1);
        const Vertex v2_ = program_->vertex_shader(v2);

        const vector<Vertex> interpoleted = rasterize_triangle(v0_, v1_, v2_);
        for (const Vertex& interpolated_Vertex : interpoleted)
        {
            const Color c = program_->fragment_shader(interpolated_Vertex);
            image.pixels[static_cast<int32_t>(round(interpolated_Vertex.y)) *
                             image.width +
                         static_cast<int32_t>(round(interpolated_Vertex.x))] =
                c;
        }
    }
}

const double& clamp(const double& value,
                    const double& min_value,
                    const double& max_value)
{
    return (value < min_value) ? min_value
                               : ((max_value < value) ? max_value : value);
}

int main(int, char**)
{

    if (0 != SDL_Init(SDL_INIT_EVERYTHING))
    {
        cerr << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    int width  = 800;
    int height = 800;

    SDL_Window* window =
        SDL_CreateWindow("Soft GFX Program", width, height, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        cerr << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cerr << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    const Color black(0, 0, 0);
    Image       image(width, height);

    struct program : GFXProgram
    {
        Vector2 mouse_position;
        double  radius;

        void set_uniform(const Uniform& a_Uniform) override
        {
            mouse_position.x = a_Uniform.f0;
            mouse_position.y = a_Uniform.f1;
            radius           = a_Uniform.f2;
        }
        Vertex vertex_shader(const Vertex& v_in) override
        {
            const double PI  = 3.14159265358979323846;
            Vertex       out = v_in;

            double x = out.x;
            double y = out.y;

            double dx = x - mouse_position.x;
            double dy = y - mouse_position.y;
            if (dx * dx + dy * dy < radius * radius)
            {
                double angle    = atan2(dy, dx);
                double distance = sqrt(dx * dx + dy * dy);
                double time =
                    chrono::duration_cast<chrono::milliseconds>(
                        chrono::system_clock::now().time_since_epoch())
                        .count() *
                    0.001;
                double spiral_radius = cos(time * 2 * PI) * 10;
                x = mouse_position.x + cos(angle) * (distance + spiral_radius);
                y = mouse_position.y + sin(angle) * (distance + spiral_radius);

                out.x = x;
                out.y = y;
            }
            return out;
        }
        Color fragment_shader(const Vertex& v_in) override
        {
            Color  out;
            double x    = v_in.x;
            double y    = v_in.y;
            double dx   = x - mouse_position.x;
            double dy   = y - mouse_position.y;
            double dist = sqrt(dx * dx + dy * dy);

            if (dist < radius)
            {
                double t = dist / radius;
                out.r    = static_cast<uint8_t>(lerp(t, 255, t));
                out.g    = static_cast<uint8_t>(lerp(255, 0, t));
                out.b    = static_cast<uint8_t>(lerp(255, 255, t));
            }
            else
            {
                out.r = 70;
                out.g = 70;
                out.b = 255;
            }

            return out;
        }
    } program01;

    vector<Vertex> vertices;

    const size_t cell_x_count = 25;
    const size_t cell_y_count = 25;
    const double cell_width   = static_cast<double>(width) / cell_x_count;
    const double cell_height  = static_cast<double>(height) / cell_y_count;
    for (size_t j = 0; j < cell_y_count; ++j)
    {
        for (size_t i = 0; i < cell_x_count; ++i)
        {
            double x = i * cell_width;
            double y = j * cell_height;
            vertices.push_back({ x, y, 0, 0, 1 });
        }
    }

    vector<uint16_t> indices;
    for (size_t j = 1; j < cell_y_count - 1; j++)
    {
        for (size_t i = 1; i < cell_x_count - 1; i++)
        {
            uint16_t v0 = j * cell_x_count + i;
            uint16_t v1 = v0 + 1;
            uint16_t v2 = v0 + cell_x_count;
            uint16_t v3 = v2 + 1;

            indices.insert(end(indices), { v0, v1, v0 });
            indices.insert(end(indices), { v1, v2, v1 });
            indices.insert(end(indices), { v2, v0, v2 });

            indices.insert(end(indices), { v2, v3, v2 });
            indices.insert(end(indices), { v1, v3, v1 });
            indices.insert(end(indices), { v3, v0, v3 });
        }
    }

    void*     pixels = (void*)image.pixels;
    const int pitch  = width * sizeof(Color);

    SDL_Surface* bitmapSurface = SDL_CreateSurfaceFrom(
        pixels, width, height, pitch, SDL_PIXELFORMAT_RGB24);
    if (bitmapSurface == nullptr)
    {
        cerr << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    double mouse_x;
    double mouse_y;
    double radius = 100.0;

    bool continue_loop = true;

    while (continue_loop)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                continue_loop = false;
                break;
            }
            else if (e.type == SDL_EVENT_MOUSE_MOTION)
            {
                mouse_x = e.motion.x;
                mouse_y = e.motion.y;
            }
            else if (e.type == SDL_EVENT_MOUSE_WHEEL)
            {
                radius += e.wheel.y;
            }
        }

        fill(image, black);

        program01.set_uniform(Uniform{ mouse_x, mouse_y, radius });
        draw_triangles(&program01, image, vertices, indices);

        SDL_Texture* bitmapTex =
            SDL_CreateTextureFromSurface(renderer, bitmapSurface);
        if (bitmapTex == nullptr)
        {
            cerr << SDL_GetError() << endl;
            return EXIT_FAILURE;
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, bitmapTex, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(bitmapTex);
    }
    SDL_DestroySurface(bitmapSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}