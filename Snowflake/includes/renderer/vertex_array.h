#pragma once
#include "core/core.h"
#include "vertex_buffer.h"
namespace Snowflake
{
    class VertexArray
    {
    protected:
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;

    public:
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> vertexbuffer) = 0;

        void setIndexBuffer(const std::shared_ptr<IndexBuffer> indexbuffer)
        {
            bind();
            indexbuffer->bind();
            unbind();
            mIndexBuffer = indexbuffer;
        }
        uint32_t getIndexBufferSize()
        {
            if (mIndexBuffer == nullptr)
                return 0;
            return mIndexBuffer->getSize();
        }

        static std::shared_ptr<VertexArray> create();
    };

    class GLVertexArray : public VertexArray
    {
    private:
        unsigned int VAO;

    public:
        GLVertexArray(/* args */);
        ~GLVertexArray();
        virtual void bind();
        virtual void unbind();
        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> vertexbuffer);
    };

    GLVertexArray::GLVertexArray(/* args */)
    {
        glGenVertexArrays(1, &VAO);
    }

    void GLVertexArray::bind()
    {
        glBindVertexArray(VAO);
    }

    void GLVertexArray::unbind()
    {
        glBindVertexArray(0);
    }
    void GLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> vertexbuffer)
    {
        bind();
        vertexbuffer->bind();
        auto layout = vertexbuffer->getLayout();
        auto size = vertexbuffer->getSize();
        auto vertices = vertexbuffer->getVertices();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        auto a = layout.mElements.size(); // TO REMOVE
        for (int i = 0; i < layout.mElements.size(); i++)
        {
            auto x = layout.mElements[i].GetComponentCount(); // TO REMOVE
            auto y = layout.mStride;                          // TO REMOVE
            auto z = layout.mElements[i].mOffset;             // TO REMOVE
            // glVertexAttribPointer(
            //     0,
            //     3,
            //     GL_FLOAT,
            //     GL_FALSE,
            //     3 * sizeof(float),
            //     (void *)0);
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glVertexAttribPointer(
                i,
                layout.mElements[i].GetComponentCount(),
                ShaderDataTypeToGLenum(layout.mElements[i].mType),
                layout.mElements[i].mNormalised ? GL_TRUE : GL_FALSE,
                layout.mStride,
                (void *)layout.mElements[i].mOffset);
            glEnableVertexAttribArray(i);
        }
        unbind();
        mVertexBuffers.push_back(vertexbuffer);
    }

    GLVertexArray::~GLVertexArray()
    {
    }

    std::shared_ptr<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:
            return std::make_shared<GLVertexArray>();
        case GraphicsAPI::None:
            SF_LOGE("API unsupported!");
        }
        return nullptr;
    }

} // namespace Snowflake
