#pragma once

#include <glm/glm.hpp>

#include "core/core.h"
#include "material.h"
namespace Snowflake
{
    struct vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coordinate;
    };

    class Mesh
    {
        std::vector<vertex> mVertices;
        std::vector<unsigned int> mIndices;
        Material mMaterial;

        virtual void setup_mesh() = 0;
    public:
        Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, Material material) :
        mVertices(vertices),
        mIndices(indices),
        mMaterial(material)
        {
            setup_mesh();
        }
    };

} // namespace Snowflake
