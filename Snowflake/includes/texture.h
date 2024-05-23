#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/includes/stb_image.h"

#include "core.h"
#include "renderer.h"
namespace Snowflake
{
    enum class TextureType
    {
        NONE,
        AMBIENT_MAP,
        DIFFUSE_MAP,
        SPECULAR_MAP,
        SHININESS_MAP,
        ALPHA_MAP,
        BUMP_MAP,
        ALBEDO_MAP,
        NORMAL_MAP
    };
    class Texture
    {
    protected:
        unsigned int ID;
        std::string mPath;
        TextureType mType = TextureType::NONE;

    public:
        Texture(std::string path, TextureType type, bool shouldFlip = true) : mPath(path),
                                                      mType(type) {}

        unsigned int getNativeTexture() { return ID; }
        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class GLTexture2D : public Texture
    {
    public:
        GLTexture2D(std::string path, TextureType type, bool shouldFlip = true) : Texture(path, type)
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                stbi_set_flip_vertically_on_load(shouldFlip);  
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }
            this->ID = textureID;
            glBindTexture(GL_TEXTURE_2D, 0);

        }
        virtual void bind()
        {
            glBindTexture(GL_TEXTURE_2D, ID);
        }
        virtual void unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

    std::shared_ptr<Texture> create_texture(std::string path, TextureType type, bool shouldFlip = true)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::OpenGL:

            return std::make_shared<GLTexture2D>(path, type, shouldFlip);
        case GraphicsAPI::None:
            SF_LOGE("GraphicsAPI None is not supported!");
        }
        return nullptr;
    }
} // namespace Snowflake
