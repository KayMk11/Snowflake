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

        model = std::make_shared<Snowflake::Model>("/home/kaymk11/Code/OpenGL-Practice/resources/models/cube.obj");
        // std::vector<unsigned int> indices{
        //     // Top
        //     2, 6, 7,
        //     2, 3, 7,

        //     // Bottom
        //     0, 4, 5,
        //     0, 1, 5,

        //     // Left
        //     0, 2, 6,
        //     0, 4, 6,

        //     // Right
        //     1, 3, 7,
        //     1, 5, 7,

        //     // Front
        //     0, 2, 3,
        //     0, 1, 3,

        //     // Back
        //     4, 6, 7,
        //     4, 5, 7};

        // std::vector<float> vertices{
        //     -1.0f, -1.0f, 0.0f, // 0
        //     1.0f, -1.0f, 0.0f,  // 1
        //     -1.0f, 1.0f, 0.0f,  // 2
        //     1.0f, 1.0f, 0.0f,   // 3
        //     -1.0f, -1.0f, 0.0f, // 4
        //     1.0f, -1.0f, 0.0f,  // 5
        //     -1.0f, 1.0f, 0.0f,  // 6
        //     1.0f, 1.0f, 0.0f    // 7
        // };

        std::vector<float> vertices = {
            0.5f, 0.5f, 0.0f,   // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f, // bottom left
            -0.5f, 0.5f, 0.0f   // top left
        };
        std::vector<unsigned int> indices = {
            // note that we start from 0!
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        // model = std::make_shared<Snowflake::Renderable>(vertices, indices);
        unsigned int VBO, EBO;
        // Generate VAO
        glGenVertexArrays(1, &VAO);
        // Generate VBO
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // Bind VAO
        glBindVertexArray(VAO);
        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Assign data to VBO
        glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);
        // Bind EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // Assign data to EBO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

        // Tell opengl how to read the VBO data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        // once opengl knows how to read VBO, enable it so that opengl uses it
        glEnableVertexAttribArray(0);

        // unbind VBO and VAO so that we dont mistakenly make changes to it;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    ~Sandbox() {}

    virtual void onUpdate() override
    {
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glClearColor(0.07, 0.13, 0.17, 1.);
        // SF_LOGI("onUpdate!");
        // if (Snowflake::Input::isKeyPressed(SF_KEY_TAB))
        //     SF_LOGI("Tab pressed!");
        shader->use();
        glm::mat4 matProjection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        shader->setMat4("projection", matProjection);
        glm::mat4 matView = glm::mat4(1.0f);
        shader->setMat4("view", matView);
        glm::mat4 matModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        shader->setMat4("model", matModel);
        model->draw();

        // glBindVertexArray(VAO);

        // tell opengl to draw bound VAO
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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