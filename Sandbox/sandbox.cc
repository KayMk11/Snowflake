#include <string>
#include <vector>
#include "Snowflake/snowflake.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox : public Snowflake::Application
{
    // std::shared_ptr<Snowflake::Model> model;
    std::shared_ptr<Snowflake::Renderable> model;
    std::shared_ptr<Snowflake::Shader> shader;
    unsigned int VAO;

public:
    Sandbox()
    {
        shader = Snowflake::Shader::create("Triangle", "./shaders/triangle.vs", "./shaders/triangle.fs");
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::APPLICATION_RESIZE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::APPLICATION_CLOSE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::KEYBOARD_PRESS, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::KEYBOARD_RELEASE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_MOVE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_PRESS, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_RELEASE, this);
        Snowflake::EventDispatcher::getInstance()->setCallback(Snowflake::eventType::MOUSE_SCROLL, this);

        model = std::make_shared<Snowflake::Model>("/home/kaymk11/Code/OpenGL-Practice/resources/models/plane.obj");
        std::vector<unsigned int> indices{
            // Top
            2, 6, 7,
            2, 3, 7,

            // Bottom
            0, 4, 5,
            0, 1, 5,

            // Left
            0, 2, 6,
            0, 4, 6,

            // Right
            1, 3, 7,
            1, 5, 7,

            // Front
            0, 2, 3,
            0, 1, 3,

            // Back
            4, 6, 7,
            4, 5, 7};

        std::vector<float> vertices{
            -1, -1, 0.5,  // 0
            1, -1, 0.5,   // 1
            -1, 1, 0.5,   // 2
            1, 1, 0.5,    // 3
            -1, -1, -0.5, // 4
            1, -1, -0.5,  // 5
            -1, 1, -0.5,  // 6
            1, 1, -0.5    // 7
        };

        // model = std::make_shared<Snowflake::Renderable>(vertices, indices);
    }
    ~Sandbox() {}

    virtual void onUpdate() override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.07, 0.13, 0.17, 1.);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        shader->use();
        glm::mat4 matProjection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shader->setMat4("projection", matProjection);
        glm::mat4 matView = glm::mat4(1.0f);
        shader->setMat4("view", matView);
        glm::mat4 matModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        matModel = glm::rotate(matModel, glm::radians(90.0f), glm::vec3(1, 0, 0));
        shader->setMat4("model", matModel);
        model->draw();
    }

    virtual void onEvent(Snowflake::Event &e) override
    {
        if (e.getType() == Snowflake::APPLICATION_CLOSE)
            shutdown();
        else if (e.getType() == Snowflake::APPLICATION_RESIZE)
        {
            SF_LOGI("Application event recieved %s", e.getName());
        }
        else if (e.getType() == Snowflake::KEYBOARD_PRESS)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if (e.getType() == Snowflake::KEYBOARD_RELEASE)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if (e.getType() == Snowflake::MOUSE_MOVE)
        {
            auto me = (Snowflake::MouseMoveEvent *)&e;
            SF_LOGI("event recieved %s | x = %f, y = %f", e.getName(), me->getX(), me->getY());
        }
        else if (e.getType() == Snowflake::MOUSE_PRESS)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if (e.getType() == Snowflake::MOUSE_RELEASE)
        {
            SF_LOGI("event recieved %s", e.getName());
        }
        else if (e.getType() == Snowflake::MOUSE_SCROLL)
        {
            SF_LOGI("event recieved %s", e.getName());
            auto me = (Snowflake::MouseScrollEvent *)&e;
            SF_LOGI("event recieved %s | offset = %f", e.getName(), me->getOffset());
        }
    }
};

Snowflake::Application *Snowflake::create_application()
{
    return new Sandbox();
}