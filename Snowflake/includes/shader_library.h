#pragma once
#include <unordered_map>
#include "core.h"
#include "shader.h"
#include "renderer.h"
namespace Snowflake
{
    class ShaderLibrary
    {
        static ShaderLibrary *instance;
        std::unordered_map<std::string, std::shared_ptr<Shader>> library;
        ShaderLibrary(){};

    public:
        ShaderLibrary(ShaderLibrary &other) = delete;
        void operator=(const ShaderLibrary &) = delete;

        static ShaderLibrary *getInstance()
        {
            if (instance == nullptr)
                instance = new ShaderLibrary();
            return instance;
        }
        std::shared_ptr<Shader> CreateShader(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath = "")
        {
            switch (Renderer::getAPI())
            {
            case GraphicsAPI::OpenGL:
            {
                std::shared_ptr<Shader> shader = std::make_shared<GLShader>(name, vertexShaderPath, fragmentShaderPath, geometryShaderPath);
                AddShader(name, shader);
                return shader;
            }
            case GraphicsAPI::None:
                SF_LOGE("GraphicsAPI None is not supported!");
            }
            return nullptr;
        }
        void AddShader(std::string &name, std::shared_ptr<Shader> shader)
        {
            if (!checkIsExist(name))
            {
                library[name] = shader;
            }
        }
        std::shared_ptr<Shader> getShader(std::string &name)
        {
            if (library.count(name) > 0)
                return library[name];

            return nullptr;
        }
        bool checkIsExist(std::string &name)
        {
            return library.count(name);
        }
    };
    ShaderLibrary* ShaderLibrary::instance = nullptr;
} // namespace Snowflake
