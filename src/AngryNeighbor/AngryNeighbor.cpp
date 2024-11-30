#include "AngryNeighbor/AngryNeighbor.h"
#include "core/Window.h"
#include "Application/Application.h"
#include "AssetManager/AssetManager.h"

AngryNeighbor::AngryNeighbor() {
    camera = std::make_shared<Camera>();
    camera->setPosition(glm::vec3(0, 2, 0));
    camera->walkingSpeed = 20;
    camera->runningSpeed = 200;
    this->setProjectionMatrixParams(80.f, 0.001, 100.f);
    planes = {
        std::make_shared<Plane>(
        glm::vec3{ -60,0,60 },
        glm::vec2{ 120,120 },
        glm::vec3{ 0,1,0 },
            "assets/test-textures/dirt_128.png"),
        std::make_shared<Plane>(
        glm::vec3{ 0,0,0 },
        glm::vec2{ 24,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 0,10,0 },
        glm::vec2{ 24,1 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 0,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 23,1,0 },
        glm::vec2{ 1,9 },
        glm::vec3{ 0,0,1 },
            "assets/test-textures/default_brick.png"),
            std::make_shared<Plane>(
        glm::vec3{ 0,1,0 },
        glm::vec2{ 24,9 },
        glm::vec3{ 0,1,0 },
            "assets/test-textures/default_pine_wood.png"),

    };

}
void AngryNeighbor::update(float dt) {
    camera->update(dt);
    mvp = projection * camera->getViewMatrix();
}

void AngryNeighbor::render() {
    for (auto plane : planes)
        plane->render(mvp);
}

void AngryNeighbor::onKeyEvent(int32_t key, int32_t scancode, int32_t action, int32_t mode) {
    camera->onKeyEvent(key, scancode, action, mode);

}
void AngryNeighbor::onCursorPositionEvent(double x, double y) {
    camera->onCursorPositionEvent(x, y);
}