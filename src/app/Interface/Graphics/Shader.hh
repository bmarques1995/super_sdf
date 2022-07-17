#ifndef SHADER_HH
#define SHADER_HH

#include <string>

class Shader
{
public:
    virtual void Bind() const = 0;
    virtual void SetBool(const std::string &name, bool value) const = 0;
    virtual void SetInt(const std::string &name, int value) const = 0;
    virtual void SetFloat(const std::string &name, float value) const = 0;
};
#endif
