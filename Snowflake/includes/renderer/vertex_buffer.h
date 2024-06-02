#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "core/core.h"
#include "renderer.h"
#include "layouts.h"
namespace Snowflake
{
    class VertexBuffer
    {
    protected:
        float *mVertices;
        uint32_t mSize;
        BufferLayout mLayout;

    public:
        VertexBuffer(uint32_t size, const BufferLayout &layout) : mSize(size), mLayout(layout) {}
        VertexBuffer(float *vertices, uint32_t size, const BufferLayout &layout) : mVertices(vertices), mSize(size), mLayout(layout) {}

        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void setData(float *vertices, uint32_t size) = 0;

        float *getVertices() { return mVertices; }
        uint32_t getSize() { return mSize; }
        BufferLayout &getLayout() { return mLayout; }
        static std::shared_ptr<VertexBuffer> create(float *vertices, uint32_t size, const BufferLayout &layout);
        static std::shared_ptr<VertexBuffer> create(uint32_t size, const BufferLayout &layout);
    };

    class IndexBuffer
    {
    protected:
        uint32_t mSize;

    public:
        IndexBuffer() {}
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual uint32_t getSize() const = 0;
        uint32_t getSize() { return mSize; }

        static std::shared_ptr<IndexBuffer> create(uint32_t *indices, uint32_t size);
    };

    static GLenum ShaderDataTypeToGLenum(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Float2:
        case ShaderDataType::Float3:
        case ShaderDataType::Float4:
        case ShaderDataType::Mat3:
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
        case ShaderDataType::Int2:
        case ShaderDataType::Int3:
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }
        SF_LOGE("Unknown Enum");
        return 0;
    }

    class GLVertexBuffer : public VertexBuffer
    {
        unsigned int VBO;

    public:
        GLVertexBuffer(uint32_t size, const BufferLayout &layout) : VertexBuffer(size, layout)
        {
            glGenBuffers(1, &VBO);
        }
        GLVertexBuffer(float *vertices, uint32_t size, const BufferLayout &layout) : VertexBuffer(vertices, size, layout)
        {
            glGenBuffers(1, &VBO);
        }

        virtual void bind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
        }
        virtual void unbind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        virtual void setData(float *vertices, uint32_t size)
        {
            bind();
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
            unbind();
        }
    };
    class GLIndexBuffer : public IndexBuffer
    {
        unsigned int EBO;

    public:
        GLIndexBuffer(uint32_t *indices, uint32_t size)
        {
            mSize = size;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        }

        virtual void bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        }

        virtual void unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        virtual uint32_t getSize() const
        {
            return mSize;
        }
    };

    std::shared_ptr<VertexBuffer> VertexBuffer::create(float *vertices, uint32_t size, const BufferLayout &layout)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<GLVertexBuffer>(vertices, size, layout);
        case GraphicsAPI::None:
            SF_LOGE("API unsupported!");
        }
        return nullptr;
    }
    std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size, const BufferLayout &layout)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<GLVertexBuffer>(size, layout);
        case GraphicsAPI::None:
            SF_LOGE("API unsupported!");
        }
        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t *indices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<GLIndexBuffer>(indices, size);
        case GraphicsAPI::None:
            SF_LOGE("API unsupported!");
        }
        return nullptr;
    }
} // namespace Snowflake
