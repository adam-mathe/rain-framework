#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rain
{
    enum RESOURCE_TYPE
    {
        TEXTURE
    };

    class ResourceManager
    {
        public:
            void generate_resource(const std::string& path, rain::RESOURCE_TYPE type, const std::string& id)
            {
                // if type == rain::RESOURCE_TYPE::TEXTURE
                //
                // Maybe we can hash their string id and use a hash map
            }
        private:
            unsigned int resources[];
    };

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
            ResourceManager* resources;
    };
}
