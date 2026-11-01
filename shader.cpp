#include <string>

#include "util.hpp"
#include "shader.hpp"
#include "linear.hpp"

Shader::Shader(std::string vertex_path, std::string fragment_path)
{
    id = glCreateProgram();

    // Load the shader source code
    std::string vertex_source_string = load_file("base.vert");
    std::string fragment_source_string = load_file("base.frag");

    const GLchar* vertex_source_pointer = vertex_source_string.c_str();
    const GLchar* fragment_source_pointer = fragment_source_string.c_str();

    // Create and compile each shader
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertex_source_pointer, NULL);
    glShaderSource(fragment, 1, &fragment_source_pointer, NULL);

    glCompileShader(vertex);
    glCompileShader(fragment);

    // Attach shaders to the program and link
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    glLinkProgram(id);

    // Cleanup
    glDetachShader(id, vertex);
    glDetachShader(id, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setVec3(std::string location, float a, float b, float c)
{
    glUniform3f(glGetUniformLocation(id, location.c_str()), a, b, c);
}

void Shader::setMat4(std::string location, linear::mat4& data)
{
    glUniformMatrix4fv(glGetUniformLocation(id, location.c_str()), 1, GL_FALSE, &data.c[0].x);
}
