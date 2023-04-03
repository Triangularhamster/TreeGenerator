#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "shader.h"
#include "common.h"

CLASS_PTR(Program)
class Program{
public:
    // shader의 메모리 주소만 전달받도록
    // shared pointer의 형태로 전달받음
    static ProgramUPtr Create(const std::vector<ShaderPtr>& shaders);

    ~Program();
    uint32_t Get() const {return m_program;}
    void Use() const;

    // ... in Program class declaration
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, const glm::vec3& value) const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;

private:
    Program() {}
    bool Link(const std::vector<ShaderPtr>& shaders);
    uint32_t m_program{0};
};

#endif // __PROGRAM_H__