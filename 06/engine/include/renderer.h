#pragma once
#include "shader.h"
#include "texture.h"
#include "tmath.h"
#include <vector>

class Renderer
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

public:
    Shader*  shader;
    Texture* texture;
    Vector3  position;
    Vector3  rotation;
    Vector3  scale;

    std::vector<float>        vertices;
    std::vector<unsigned int> indices;

    void start();
    void render();
};