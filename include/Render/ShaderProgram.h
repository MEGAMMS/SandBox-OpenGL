#pragma once

#include "core.h"
#include "Render/Shader.h"
#include "Render/Texture.h"

class ShaderProgram {
    uint32_t shaderProgram = 0;

    [[nodiscard]] int32_t getUniformLocation(const std::string& location) const;

public:
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&&) = delete;

    explicit ShaderProgram(const std::string& name);

    [[nodiscard]] bool isValid() const { return shaderProgram; };
    void activate() const;

    void setInt(const std::string& location, int32_t value) const;
    void setFloat(const std::string& location, float value) const;
    void setVec2(const std::string& location, const glm::vec2& value) const;
    void setVec3(const std::string& location, const glm::vec3& value) const;
    void setMat4(const std::string& location, const glm::mat4& value) const;
      void setTexture(const std::string &location, const std::shared_ptr<const Texture> &texture, int32_t slot) const;

    ~ShaderProgram();
};
