#include "Challenges/Pyramid.h"
#include "buffers/EBO.h"
#include "core/Window.h"
#include "core/Image.h"
#include "Application/Application.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
};


Pyramid::Pyramid() {
    static std::array<Vertex, 9> vertices = {
      Vertex{ glm::vec3{-1.,-1.,0.} ,glm::vec2{2.5,0} },
      Vertex{ glm::vec3{ 1.,-1.,0.} ,glm::vec2{0,0}},
      Vertex{ glm::vec3{-1., 1.,0.} ,glm::vec2{0,0}},
      Vertex{ glm::vec3{ 1., 1.,0.} ,glm::vec2{2.5,0}},
      Vertex{ glm::vec3{ 0., 0.,1.6} ,glm::vec2{1.25,2.5}},

      Vertex{ glm::vec3{-1.,-1.,0.} ,glm::vec2{0,0} },
      Vertex{ glm::vec3{ 1.,-1.,0.} ,glm::vec2{2.5,0}},
      Vertex{ glm::vec3{-1., 1.,0.} ,glm::vec2{0,2.5}},
      Vertex{ glm::vec3{ 1., 1.,0.} ,glm::vec2{2.5,2.5}}
    };
    static std::array<GLuint, 6 * 3> indices = {
        0, 1, 4,
        0, 2, 4,
        1, 3, 4,
        2, 3, 4,

        5, 6, 7,
        8, 6, 7
    };
    glActiveTexture(GL_TEXTURE2);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    Img brick("assets/brick.png");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brick.width, brick.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, brick.data.data());
    glGenerateMipmap(GL_TEXTURE_2D);

    vao = VAO();
    vao.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo((GLfloat*) vertices.data(), sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo((GLuint*) indices.data(), sizeof(indices));

    // Links VBO to VAO
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    shaderProgram = std::make_shared<Shader>(
        "assets/shaders/Pyramid.vert",
        "assets/shaders/Pyramid.frag");
    shaderProgram->Activate();
    shaderProgram->setVec2("u_resolution", Window::instance().getWindowRes());
    shaderProgram->setInt("tex", 2);
    vbo.Delete();
    ebo.Delete();
}

void Pyramid::update(float dt) {
    std::array<glm::vec3, 19> pyramidsPositions{
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(2.0f,  5.0f, 15.0f),
        glm::vec3(-1.5f, -2.2f, 2.5f),
        glm::vec3(-3.8f, -2.0f, 12.3f),
        glm::vec3(2.4f, -0.4f, 3.5f),
        glm::vec3(-1.7f,  3.0f, 7.5f),
        glm::vec3(1.3f, -2.0f, 2.5f),
        glm::vec3(1.5f,  2.0f, 2.5f),
        glm::vec3(1.5f,  0.2f, 1.5f),
        glm::vec3(-1.3f,  1.0f, 1.5f)
    };

    vao.Bind();
    shaderProgram->Activate();
    shaderProgram->setFloat("u_time", glfwGetTime());

    glm::mat4 trans = glm::mat4(1.);
    trans = glm::scale(trans, glm::vec3(0.5));
    trans = glm::translate(trans, glm::vec3(0, 0, 0));
    trans = glm::rotate(trans, glm::radians(-90.f), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians((float) (int(glfwGetTime() * 100) % 360)), glm::vec3(0.0, 0.0, 1.0));

    Window& window = Window::instance();
    float aspect = (float) window.getWindowWidth() / window.getWindowHeight();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, -0.4f, -4.f));
    float angle = (int(glfwGetTime() * 5000) % 360000) / 1000.f;
    view = glm::rotate(view, glm::radians(angle), glm::vec3(0.6f, 0.8f * glfwGetTime(), 0.4f));
    shaderProgram->setMat4("projection", projection);
    shaderProgram->setMat4("view", view);

    for (int i = 0;i < pyramidsPositions.size();i++) {
        trans = glm::mat4(1.);
        trans = glm::scale(trans, glm::vec3(0.7));
        trans = glm::translate(trans, pyramidsPositions[i] * glm::vec3(2.1));
        float angle = i * 20.f;
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        angle = glfwGetTime() * 2.;
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        trans = glm::rotate(trans, glm::radians(-70.f), glm::vec3(1.0f, 0.1f, 0.0f));
        shaderProgram->setMat4("model", trans);
        glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_INT, 0);
    }

}

void Pyramid::Delete() {
    vao.Delete();
}
void Pyramid::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    bool pressed = action == GLFW_PRESS;
}

