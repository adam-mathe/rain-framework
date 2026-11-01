#include <fstream>
#include <string>

inline std::string load_file(std::string filepath)
{
    std::ifstream file(filepath);
    std::string line, output;

    while(getline(file, line))
    {
        output += line + "\n";
    }

    return output;
}
