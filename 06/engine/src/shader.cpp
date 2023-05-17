#include "shader.h"
#include "glad/glad.h"
#include <regex>
#include <string>

int getShaders(std::string source, char*& vertex, char*& fragment)
{
    std::regex version_regex("#version\\s+(\\d+)\\s+\\w+");
    std::regex vertex_regex("vertex\\s*\\[([\\S\\s]*?)\\]");
    std::regex fragment_regex("fragment\\s*\\[([\\S\\s]*?)\\]");

    std::smatch version_match;
    std::string version_string;
    if (std::regex_search(source, version_match, version_regex))
    {
        version_string = version_match[0].str() + "\n";
    }

    std::smatch shader_match;
    std::string vertex_shader, fragment_shader;
    if (std::regex_search(source, shader_match, vertex_regex))
    {
        vertex_shader = version_string + shader_match[1].str();
    }
    if (std::regex_search(source, shader_match, fragment_regex))
    {
        fragment_shader = version_string + shader_match[1].str();
    }

    std::cout << "Vertex shader:\n" << vertex_shader << "\n\n";
    std::cout << "Fragment shader:\n" << fragment_shader << "\n\n";

    vertex   = strdup(vertex_shader.c_str());
    fragment = strdup(fragment_shader.c_str());
}

void Shader::load()
{
    char* vertShader;
    char* fragShader;
    getShaders(shaderSource, vertShader, fragShader);
    unsigned int vertexShader;
    if (vertShader == NULL || fragShader == NULL)
    {
        std::cout << "ERROR::SHADER::PARSING_FAILED\n" << std::endl;
        return;
    }
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::LINK_FAILED\n"
                  << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
void Shader::use()
{
    glUseProgram(program);
}

void Shader::SetUniform(const char* id, int value)
{
    GLint pos = glGetUniformLocation(program, id);
    if (pos == -1)
    {
        std::cout << "ERROR::SHADER::UNIFORM::NOTFOUND::" << id << std::endl;
        return;
    }
    glUniform1i(pos, value);
}

void Shader::SetUniform(const char* id, float value)
{
    GLint pos = glGetUniformLocation(program, id);
    if (pos == -1)
    {
        std::cout << "ERROR::SHADER::UNIFORM::NOTFOUND::" << id << std::endl;
        return;
    }
    glUniform1f(pos, value);
}

void Shader::SetUniform(const char* id, Color value)
{
    GLint pos = glGetUniformLocation(program, id);
    if (pos == -1)
    {
        std::cout << "ERROR::SHADER::UNIFORM::NOTFOUND::" << id << std::endl;
        return;
    }
    glUniform4f(pos, value.r, value.g, value.b, value.a);
}

void Shader::SetUniform(const char* id, Vector3 value)
{
    GLint pos = glGetUniformLocation(program, id);
    if (pos == -1)
    {
        std::cout << "ERROR::SHADER::UNIFORM::NOTFOUND::" << id << std::endl;
        return;
    }
    glUniform3f(pos, value.x, value.y, value.z);
}

void Shader::SetUniform(const char* id, glm::mat4 value)
{
    GLint pos = glGetUniformLocation(program, id);
    if (pos == -1)
    {
        std::cout << "ERROR::SHADER::UNIFORM::NOTFOUND::" << id;
        return;
    }
    glUniformMatrix4fv(pos, 1, GL_FALSE, &value[0][0]);
}