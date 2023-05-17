#pragma once
#include "glm/mat4x4.hpp"
#include "tmath.h"
class Shader
{
    unsigned int program;

public:
    const char* shaderSource;

    void load();

    void use();

    void SetUniform(const char* id, int value);

    void SetUniform(const char* id, float value);

    void SetUniform(const char* id, Color value);

    void SetUniform(const char* id, Vector3 value);

    void SetUniform(const char* id, glm::mat4 value);
};