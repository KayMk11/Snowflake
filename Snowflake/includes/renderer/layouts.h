#pragma once

namespace Snowflake
{
    enum class ShaderDataType
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool,
        Mat3,
        Mat4
    };
    // REVIEW
    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 4 * 2;
        case ShaderDataType::Float3:
            return 4 * 3;
        case ShaderDataType::Float4:
            return 4 * 4;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 4 * 2;
        case ShaderDataType::Int3:
            return 4 * 3;
        case ShaderDataType::Int4:
            return 4 * 4;
        case ShaderDataType::Bool:
            return 1;
        }

        SF_LOGE("Unknown ShaderDataType!");
        return 0;
    }
    struct BufferElement
    {
        std::string mName;
        ShaderDataType mType;
        bool mNormalised;
        uint32_t mSize = 0;
        size_t mOffset = 0;

        BufferElement(std::string name, ShaderDataType type, bool normalised) : mName(name),
                                                                                mType(type),
                                                                                mSize(ShaderDataTypeSize(type)),
                                                                                mOffset(0),
                                                                                mNormalised(normalised) {}

        uint32_t GetComponentCount() const
        {
            switch (mType)
            {
            case ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3; // 3* float3
            case ShaderDataType::Mat4:
                return 4; // 4* float4
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
            }

            SF_LOGE("Unknown Enum");
            return 0;
        }
    };
    struct BufferLayout
    {
        std::vector<BufferElement> mElements;
        uint32_t mStride;
        void calculateOffsetsAndStride()
        {
            size_t offset = 0;
            mStride = 0;
            for (auto &element : mElements)
            {
                element.mOffset = offset;
                offset += element.mSize;
                mStride += element.mSize;
            }
        }

    public:
        BufferLayout() {}

        BufferLayout(std::vector<BufferElement> elements) : mElements(elements)
        {
            calculateOffsetsAndStride();
        }
        uint32_t getStride() const { return mStride; }
        std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
        std::vector<BufferElement>::iterator end() { return mElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }
    };

    const BufferElement POSITION = {"Position", ShaderDataType::Float3, false};
    const BufferElement NORMAL = {"Position", ShaderDataType::Float3, false};
    const BufferElement TEXTURE_COORDINATE = {"Position", ShaderDataType::Float2, false};

    const BufferLayout POSITION_LAYOUT({POSITION});
    const BufferLayout POSITION_NORMAL_TEXTURE_LAYOUT({POSITION, NORMAL, TEXTURE_COORDINATE});
} // namespace Snowflake
