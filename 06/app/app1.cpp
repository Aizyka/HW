#include "app.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "tmath.h"

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
            layout (location = 1) in vec2 uv;
            uniform mat4 mvp;
            out vec2 tUV;
            void main()
            {
                tUV = uv;
                gl_Position = mvp * vec4(aPos, 1.0);
            }
        ]
        fragment
        [
            uniform sampler2D tex;
            uniform vec4 color;
            in vec2 tUV;
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1,1,1,1) * texture(tex, tUV);
            }
        ]
    )";
        renderer->shader->load();
        renderer->vertices = { -1.0f, 1.0f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,
                               0.0f,  0.0f,  0.0f,  1.0f,  -1.0f, 0.0f, 0.0f,
                               1.0f,  -1.0f, -1.0f, 0.0f,  -1.0f, 1.0f };
        renderer->indices  = { 0, 1, 2, 2, 3, 0 };
        renderer->scale    = Vector3(0.2f, 0.2f, 1.0f);
        renderer->texture  = new Texture();
        renderer->texture->path = "tank.png";
        renderer->start();
    }
    void update(float deltaTime) override
    {
        renderer->rotation.z += ((Input::GetKey(KeyCode::A) ? 50.0 : 0.0f) -
                                 (Input::GetKey(KeyCode::D) ? 50.0 : 0.0f)) *
                                deltaTime;
        if (Input::GetKey(KeyCode::W) || Input::GetKey(KeyCode::S))
        {
            float angle = (renderer->rotation.z + 90.0f) * Math::Deg2Rad;
            float sin   = Math::sin(angle);
            float cos   = Math::cos(angle);
            if (Input::GetKey(KeyCode::S))
            {
                sin = -sin;
                cos = -cos;
            }

            Vector3 forward = Vector3(cos, sin, 0.0f);
            renderer->position.x += cos * deltaTime;
            renderer->position.y += sin * deltaTime;
        }
    }
    void render() override { renderer->render(); }
};

int main()
{
    Engine::start((Game*)(new MyGame()));
    return 0;
}