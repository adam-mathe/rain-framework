#include <glad/glad.h>
#include <string>

#include "linear.hpp"

class Shader
{
    public:
        Shader(std::string vertex_path, std::string fragment_path);
        void use();
        void setVec3(std::string location, float a, float b, float c);
        void setMat4(std::string location, linear::mat4& mat);
    private:
        GLuint id;
};
