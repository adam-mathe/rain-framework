#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rain
{
    class Application
    {
        public:
            Application(int w, int h, std::string title)
            {
                // Create our window
                glfwInit();
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.1 is the latest version supported on MacOS
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
                window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
                glfwMakeContextCurrent(window);

                // And initalize GLAD so we can access OpenGL functions
                if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    std::cout << "Failed to initalize GLAD";
                }
            }

            bool is_running() const
            {
                return !glfwWindowShouldClose(window);
            }

            void present() const
            {
                glfwSwapBuffers(window);
                glfwPollEvents();
            }

        private:
            GLFWwindow* window;
    };
}
