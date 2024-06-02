#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/core.h"
#include "component.h"
namespace Snowflake
{
    class Transform
    {
        glm::vec3 mPosition = {0.f, 0.f, 0.f};
        glm::vec3 mRotation = {0.f, 0.f, 0.f};
        glm::vec3 mScale = {1.f, 1.f, 1.f};

    public:
        Transform() {}
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : mPosition(position), mRotation(rotation), mScale(scale) {}

        glm::mat4 getModelMatrix()
        {
            glm::mat4 translation = glm::translate(glm::mat4(1.f), mPosition);

            glm::mat4 rotationX = glm::rotate(glm::mat4(1.0), mRotation.x, glm::vec3(1., 0., 0.));
            glm::mat4 rotationY = glm::rotate(glm::mat4(1.0), mRotation.y, glm::vec3(0., 1., 0.));
            glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0), mRotation.z, glm::vec3(0., 0., 1.));

            glm::mat4 rotation = rotationZ * rotationY * rotationX;

            glm::mat4 scale = glm::scale(glm::mat4(1.), mScale);

            return scale * rotation * translation;
        }

        glm::vec3 getPosition() { return mPosition; }
        glm::vec3 getRotation() { return mRotation; }
        glm::vec3 getScale() { return mScale; }

        Transform *setPosition(glm::vec3 position)
        {
            mPosition = position;
            return this;
        }
        Transform *setRotation(glm::vec3 rotation)
        {
            mRotation = rotation;
            return this;
        }
        Transform *setScale(glm::vec3 scale)
        {
            mScale = scale;
            return this;
        }
    };

    class Entity : public EventListener
    {
        std::shared_ptr<Transform> mTransform;
        std::vector<std::shared_ptr<Component>> mComponents;

    public:
        void addComponent(std::shared_ptr<Component> component) { mComponents.emplace_back(component); }
        bool hasComponent(ComponentType type)
        {
            for (auto &component : mComponents)
            {
                if (component->getType() == type)
                    return true;
            }
            return false;
        }
        std::shared_ptr<Component> getComponent(ComponentType type)
        {
            for (auto &component : mComponents)
            {
                if (component->getType() == type)
                    return component;
            }
            return nullptr;
        }
        // TODO void removeComponent()
        glm::mat4 getModelMatrix() { return mTransform->getModelMatrix(); }
        std::shared_ptr<Transform> getTransform() { return mTransform; }

        virtual void onEvent(Event &e) = 0;
    };

} // namespace Snowflake
