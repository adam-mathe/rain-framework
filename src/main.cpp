#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "linear.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static const GLfloat vertices[] =
{
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, // Top left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top right
     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, // Bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Bottom left
};

static const GLuint indices[] =
{
    0, 1, 2,
    2, 3, 0
};

int main()
{
    // Create our window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.1 is the latest version supported on MacOS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Window Title", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Initalize GLAD so we can access OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD";
    }

    // Shader
    Shader base_program = Shader("shaders/base.vert", "shaders/base.frag");

    base_program.use();

    // Create a buffer to pass our vertices to OpenGL
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo); // Give 'vbo' a unique ID
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Tell OpenGL any GL_ARRAY_BUFFER commands pertain to 'vbo'
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Give our vertices to OpenGL

    // An Element Array Buffer allows OpenGL to re-use vertices when drawing a primitive
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Load an image and create a texture
    int w, h, channels;
    unsigned char* image_data = stbi_load("assets/magma.png", &w, &h, &channels, 0);

    GLuint texture;
    glGenTextures(1, &texture); // Give 'texture' a unique ID that OpenGL can use to reference it
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_data);

    // Matrix tests
    linear::mat4 mat = linear::identity();

    linear::scale(mat, linear::vec3(2.0, 2.0, 2.0));

    linear::print_mat4(mat);

    // Give the matrix to the shader
    base_program.setMat4("model", mat);

    // Main window loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.05f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
