#pragma once

#include "core.h"
#include "Render/ShaderProgram.h"
#include "Render/VertexArray.h"
#include "Application/Scene.h"

class Box {
private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec3 Normal;
        static std::vector<VertexAttribute> vertexAttributes() {
            return {
                {3, VertexAttribute::Float, 0},
                {2, VertexAttribute::Float, 3 * sizeof(float)},
                {3, VertexAttribute::Float, 5 * sizeof(float)},
            };
        }
    };

    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<const ShaderProgram> shaderProgram;
    std::shared_ptr<const Texture> texture;
    glm::mat4 model = glm::mat4(1.f);

    glm::vec3 position;
    glm::vec2 size;
    glm::vec3 orientation;
    glm::vec3 color;
    bool useTexture = false;

    Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation,std::vector<int> &facesToRender);
    std::pair<std::vector<Box::Vertex>, std::vector<GLuint>> generateVerticesAndIndices(std::vector<int>& facesToRender);
public:
    Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation,std::vector<int> facesToRender, glm::vec3 color);
    Box(glm::vec3 position, glm::vec3 size, glm::vec3 orientation,std::vector<int> facesToRender, const std::string& textureName);
    void update(float dt);
    void render(glm::mat4& mvp, glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 viewPos);
    void onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode);
};
