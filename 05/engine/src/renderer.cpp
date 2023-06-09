#include "renderer.h"
#include "glad/glad.h"

int length = 0;

void Renderer::start()
{
    length = indices.size() * 3;
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(float),
                 &vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 &indices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render()
{
    shader->use();
    glBindVertexArray(VAO);
    if (type == RenderType::TRIANGLES)
        glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, 0);
    else
        glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}