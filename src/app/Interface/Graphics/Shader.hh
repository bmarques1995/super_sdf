#ifndef SHADER_HH
#define SHADER_HH

#include <string>

class Shader
{
public:
    virtual void Bind() const = 0;
    virtual void SetUniform(const std::string &name, void* value, size_t valueType) const = 0;
};
#endif
