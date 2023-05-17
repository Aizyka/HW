#include "renderer.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/mat4x4.hpp"
#include "tmath.h"

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
        0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    texture->load();
}

void Renderer::render()
{
    shader->use();
    texture->use();
    glBindVertexArray(VAO);
    glm::mat4 matrix       = glm::mat4(1.0f);
    float     aspect_ratio = 800.0f / 600.0f;
    matrix = glm::scale(matrix, glm::vec3(1.0f, aspect_ratio, 1.0f));
    matrix =
        glm::translate(matrix, glm::vec3(position.x, position.y, position.z));

    matrix = glm::rotate(
        matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(
        matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(
        matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, scale.z));
    shader->SetUniform("mvp", matrix);
    shader->SetUniform("tex", 0);
    glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}