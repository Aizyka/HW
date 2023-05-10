#include "app.h"
#include "renderer.h"

class MyGame : Game
{
    Renderer* renderer;
    void      init() override
    {
        renderer                       = new Renderer();
        renderer->shader               = new Shader();
        renderer->shader->shaderSource = R"(
        #version 330 core
        vertex
        [
            layout (location = 0) in vec3 aPos;
            void main()
            {
                gl_Position = vec4(aPos, 1.0);
            }
        ]
        fragment
        [
            uniform vec4 color; 
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0, 0.0, 0.0, 1.0);
            }
        ]
    )";
        renderer->shader->load();
        /*renderer->vertices = { -1.0f, 1.0f,  0.0f, 1.0f,  1.0f,  0.0f,
                               1.0f,  -1.0f, 0.0f, -1.0f, -1.0f, 0.0f };

        renderer->indices = { 0, 1, 2, 2, 3, 0 };*/
        renderer->vertices = { -0.5f, -0.5f, 0.0f,  0.0f, 0.5f,
                               0.0f,  0.5f,  -0.5f, 0.0f };

        renderer->indices = { 0, 1, 2 };
        renderer->type    = RenderType::TRIANGLES;
        renderer->start();
    }
    void update(float deltaTime) override {}
    void render() override { renderer->render(); }
};

int main()
{
    Engine::start((Game*)(new MyGame()));
    return 0;
}