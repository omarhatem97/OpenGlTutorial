#include "Shader.h"
#include "Renderer.h"

#include "glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


Shader::Shader(const std::string& filepath) 
    :m_filePath(filepath), m_rendererId(0) {
    auto source = parseShader("res/shaders/basic.shader");
    std::cout << "vertex\n" << source.vertexShader << std::endl;
    std::cout << "fragment\n" << source.fragmentShader << std::endl;

    m_rendererId = createShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_rendererId));
}

void Shader::bind() const {
    GLCall(glUseProgram(m_rendererId));
}

void Shader::unbind() const {
    GLCall(glDeleteProgram(m_rendererId));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    int location = getUnifromLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

unsigned int Shader::getUnifromLocation(const std::string& name) { 
    int location = -1;
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }
    GLCall(location = glGetUniformLocation(m_rendererId, name.c_str()));
    if(location == -1)
        std::cout << "Warning: Unifrom with name:" << name << "wasn't found!" << std::endl;
    return location;
 }

shaderSource Shader::parseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    if (!stream.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return { "", "" }; // Return empty strings to handle the error
    }

    std::string line;
    std::stringstream ss[2];

    enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    //creating shaders
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex shader!" : "Fragment shader!")
            << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}