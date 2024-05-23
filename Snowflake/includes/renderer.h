#pragma once

#include "core.h"
namespace Snowflake
{
    enum class GraphicsAPI {
        OpenGL,
        None
    };

    class Renderer
    {
    public:
        static GraphicsAPI getAPI()
        {
#ifdef SF_USE_OPENGL
            return GraphicsAPI::OpenGL;
#else
            return GraphicsAPI::None;
#endif
        }
    };
} // namespace Snowflake
