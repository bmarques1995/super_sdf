#ifndef GL4_SHADER_HH
#define GL4_SHADER_HH

#include <glad/gl_safe_include.h>
#include <unordered_map>
#include <vector>

#include "Interface/Graphics/Shader.hh"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class GL4Shader : public Shader
{
public:
    
    GL4Shader(const char* vertexSource, const char* fragmentSource);
    ~GL4Shader();
    
    virtual void Bind() const override;
    virtual void SetUniform(const std::string &name, void* value, size_t valueType) const override;

private:

    unsigned Compile(const char* source, GLenum type);
    unsigned Link(const std::vector<unsigned>& shaders);

    void CheckCompileErrors(unsigned int shader, std::string_view shaderType);
    void CheckLinkErrors(unsigned int program);

    unsigned int m_ProgramID;
    std::unordered_map<unsigned, std::string> m_ShaderMapping;
};
#endif
