#include "app.h"
#include "renderer.h"
#include <chrono>
#include <iostream>

class MyGame : Game
{
    Renderer* renderer;
    float     time;
    void      init() override
    {
        renderer                       = new Renderer();
        renderer->shader               = new Shader();
        renderer->shader->shaderSource = R"(
        #version 330 core
        vertex
        [
uniform vec3 mouse_position;
uniform float radius;
uniform float time;
uniform float spiral_radius;
in vec3 vertexPosition;

out vec3 vertexColor;

void main()
{
    vec2 v_in = vec2(vertexPosition.x, vertexPosition.y);
    vec2 out_pos = v_in;

    float x = v_in.x;
    float y = v_in.y;
    vec2 mousePos = vec2(mouse_position.x / 400.0,mouse_position.y / 400.0);
    float dx = x - mousePos.x;
    float dy = y - mousePos.y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist*1000.0 < radius)
    {
        float angle = atan(dy, dx);
        float distance = sqrt(dx * dx + dy * dy);
        out_pos = mousePos + vec2(cos(angle), sin(angle)) * (distance + spiral_radius);
    }

    gl_Position = vec4(out_pos, vertexPosition.z, 1.0);
    vertexColor = vec3(1.0f);
}

        ]
        fragment
        [
uniform vec3 mouse_position;
uniform float radius;

in vec3 vertexColor;

out vec4 outColor;

void main()
{
    vec2 v_in = vec2(gl_FragCoord.xy);

    float x = v_in.x;
    float y = v_in.y;
    vec2 mousePos = vec2(mouse_position.x*2 + 800.0, mouse_position.y*2 + 800.0);
    float dx = x - mousePos.x;
    float dy = y - mousePos.y;
    float dist = sqrt(dx * dx + dy * dy);
    

    if (dist < radius)
    {
        float t = dist / radius;
        outColor = vec4(mix(t, 1.0, t), mix(1.0, 0.0, t), mix(1.0, 1.0, t), 1.0);
    }
    else
    {
        outColor = vec4(70.0 / 255.0, 70.0 / 255.0, 255.0 / 255.0, 1.0);
    }
}
        ]
    )";
        renderer->shader->load();

        float                     slices = 25.0f;
        std::vector<float>        vertices;
        std::vector<unsigned int> indices;

        for (int j = 0; j <= slices; j++)
        {
            for (int i = 0; i <= slices; i++)
            {

                float x = (float)i / (float)slices;
                float y = (float)j / (float)slices;
                float z = 0;
                vertices.insert(end(vertices),
                                { x * 2.0f - 1.0f, y * 2.0f - 1.0f, z });
            }
        }
        for (int j = 0; j < slices; j++)
        {
            for (int i = 0; i < slices; i++)
            {

                unsigned int row1 = j * (slices + 1);
                unsigned int row2 = (j + 1) * (slices + 1);

                indices.insert(end(indices),
                               { row1 + i, row1 + i + 1, row2 + i });
                indices.insert(end(indices),
                               { row1 + i, row2 + i + 1, row2 + i });
            }
        }
        renderer->vertices = vertices;
        renderer->indices  = indices;
        renderer->type     = RenderType::LINES;
        renderer->start();
    }
    void update(float deltaTime) override
    {
        time += deltaTime;
        if (time > 4.0f)
            time = 0.0f;
    }
    void render() override
    {
        const float PI = 3.14159265358979323846f;
        renderer->shader->use();
        renderer->shader->SetUniform("mouse_position",
                                     get_mouse_position() +
                                         Vector3(-400.0f, 400.0f, 0.0f));
        renderer->shader->SetUniform("radius", 350.0f);
        renderer->shader->SetUniform("spiral_radius",
                                     (float)Math::cos(time * PI) / 40.0f);
        renderer->render();
    }
};

int main()
{
    Engine::start((Game*)(new MyGame()));
    return 0;
}