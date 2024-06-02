#pragma once

#include <glm/glm.hpp>

#include "core/core.h"
#include "material.h"
#include "vertex_array.h"
#include "layouts.h"
namespace Snowflake
{
    class Mesh
    {
        std::vector<float> mVertices;
        std::vector<unsigned int> mIndices;
        Material mMaterial;

        std::shared_ptr<VertexArray> VAO;

        void setup_mesh()
        {
            VAO = VertexArray::create();

            auto vbo = VertexBuffer::create(&mVertices[0], sizeof(float) * mVertices.size(), POSITION_NORMAL_TEXTURE_LAYOUT);
            auto ebo = IndexBuffer::create(&mIndices[0], sizeof(unsigned int) * mIndices.size());
            VAO->addVertexBuffer(vbo);
            VAO->setIndexBuffer(ebo);
            // VAO->unbind();
        }

    public:
        Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, Material material) : mVertices(vertices),
                                                                                                  mIndices(indices),
                                                                                                  mMaterial(material)
        {
            setup_mesh();
        }
        bool isMeshIndexed()
        {
            return VAO->getIndexBufferSize() != 0;
        }
        uint32_t activateMesh()
        {
            VAO->bind();
            if (isMeshIndexed())
                return static_cast<unsigned int>(VAO->getIndexBufferSize());
            // else
            //     return VAO->
            return 0;
        }
    };
} // namespace Snowflake
