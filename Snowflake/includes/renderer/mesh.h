#pragma once

#include <glm/glm.hpp>

#include "core/core.h"
#include "material.h"
#include "vertex_array.h"
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
            BufferElement position = {"Position", ShaderDataType::Float3, false};
            BufferElement normal = {"Normal", ShaderDataType::Float3, false};
            BufferElement texcoord = {"TexCoord", ShaderDataType::Float2, false};
            // std::vector<BufferElement> elements = {position}; // TO REMOVE
            std::vector<BufferElement> elements = {position, normal, texcoord};
            BufferLayout layout(elements);
            auto vbo = VertexBuffer::create(&mVertices[0], mVertices.size(), layout);
            auto ebo = IndexBuffer::create(&mIndices[0], mIndices.size());
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

        void draw()
        {
            VAO->bind();
            auto size = static_cast<unsigned int>(VAO->getIndexBufferSize());
            // TODO move this to renderer
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        };
    };
} // namespace Snowflake
