//
// Created by jakub on 15.02.2026.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glm/glm.hpp>


class Shader {
public:
    // program ID
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    // Activate shader
    void use();

    // Uniform Setters
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;

private:
    std::string loadFile(const char* path);
    unsigned int compileShader(const char* shaderCode, unsigned int type);

    int getLocation(const std::string& name) const;
};



#endif //SHADER_H