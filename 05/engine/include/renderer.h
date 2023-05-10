#pragma once
#include "shader.h"
#include <vector>

enum RenderType
{
    TRIANGLES = 0,
    LINES     = 1
};

class Renderer
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

public:
    Shader* shader;

    std::vector<float>        vertices;
    std::vector<unsigned int> indices;
    RenderType                type;

    void start();
    void render();
};