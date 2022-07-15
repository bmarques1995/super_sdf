#ifndef SHADER_HH
#define SHADER_HH

#include <glad/gl_safe_include.h>
#include <unordered_map>
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();
    
    void Bind() const;
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;

private:

    unsigned Compile(const char* source, GLenum type);
    unsigned Link(const std::vector<unsigned>& shaders);

    void CheckCompileErrors(unsigned int shader, std::string_view shaderType);
    void CheckLinkErrors(unsigned int program);

    unsigned int m_ProgramID;
    std::unordered_map<unsigned, std::string> m_ShaderMapping;
};
#endif
