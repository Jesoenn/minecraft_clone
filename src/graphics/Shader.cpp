//
// Created by jakub on 15.02.2026.
//

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Load shader source codes
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile shaders
    unsigned int vertex = compileShader(vShaderCode, GL_VERTEX_SHADER);
    unsigned int fragment = compileShader(fShaderCode, GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // Delete linked shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

/**
 * Use shader program.
 */
void Shader::use() const {
    glUseProgram(ID);
}

/**
 * Loads entire text file into std::string.
 * @param path Path to file (relative to .EXE (cmake-build-debug))
 * @return Content of file as string. Empty string if failed.
 */
std::string Shader::loadFile(const char* path) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    // File buffer
    std::stringstream ss;

    try {
        file.open(path);
        // Read whole file to buffer
        ss << file.rdbuf();
        file.close();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    return ss.str();
}

unsigned int Shader::compileShader(const char *shaderCode, unsigned int type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout<< "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
    }

    return shader;
}

void Shader::setBool(const std::string &name, bool value) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniform1i(location, static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniform1f(location, value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniform3f(location, x, y, z);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    int location = getLocation(name);
    if (location == -1) return;
    glUniform3fv(location, 1, glm::value_ptr(value));
}

int Shader::getLocation(const std::string &name) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        std::cout << "WARNING::SHADER::UNIFORM '" << name << "' NOT FOUND" << std::endl;
    }

    return location;
}