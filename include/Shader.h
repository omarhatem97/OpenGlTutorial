#pragma once

#include <string>
#include <unordered_map>

struct ShaderSource {
  std::string vertexShader;
  std::string fragmentShader;
};

class Shader {
 public:
  Shader(const std::string& filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
  unsigned int getUnifromLocation(const std::string& name);

 private:
  ShaderSource parseShader(const std::string& filepath);
  unsigned int compileShader(unsigned int type, const std::string& source);
  unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

  unsigned int m_rendererId;
  std::string m_filePath;
  std::unordered_map<std::string, int> m_uniformLocationCache;

};
