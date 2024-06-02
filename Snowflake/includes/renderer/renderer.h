#pragma once

#include <queue>
#include "core/core.h"
#include "core/component.h"
#include "scene/scene_manager.h"
#include "renderer_commands.h"
namespace Snowflake
{
    enum class GraphicsAPI
    {
        OpenGL,
        None
    };

    class Renderer
    {

        std::shared_ptr<Scene> mActiveScene;
        std::queue<RenderCommand> mCommandQueue;

        void clear()
        {
        }
        void flush()
        {
            while (!mCommandQueue.empty())
            {
                auto &command = mCommandQueue.front();
                mCommandQueue.pop();
                command.execute();
            }
        }
        void draw(Renderable &renderable)
        {
            auto &meshes = renderable.getMeshes();
            for (auto &mesh : meshes)
            {
                auto size = mesh.activateMesh();
                if (mesh.isMeshIndexed())
                    drawIndexed(size);
                else
                    drawArray(size); // TODO write support for this in VertexArray
            }
        }

        virtual void drawArray(uint32_t size) = 0;
        virtual void drawIndexed(uint32_t size) = 0;

        void render()
        {
            auto entities = mActiveScene->getEntities();
            for (auto &entity : entities)
            {
                if (entity->hasComponent(ComponentType::RENDERABLE))
                {
                    auto renderable = entity->getComponent(ComponentType::RENDERABLE);
                }
            }
        }

    public:
        void beginFrame(std::shared_ptr<Scene> scene)
        {
            mActiveScene = scene;

            // TODO decide on following policy
            if (!mCommandQueue.empty())
            {
                SF_LOGE("Previous frame has not yet completed");
                return;
            }
            // Common configuration TBD

            clear();
        }
        void addCommand(RenderCommand &command)
        {
            mCommandQueue.push(command);
        }
        void endFrame()
        {
            flush();
        }
        static GraphicsAPI getAPI()
        {
#ifdef SF_USE_OPENGL
            return GraphicsAPI::OpenGL;
#else
            return GraphicsAPI::None;
#endif
        }
    };

    class GLRenderer : public Renderer
    {
    public:
        virtual void drawArray(uint32_t size)
        {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        virtual void drawIndexed(uint32_t size)
        {
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        }
    }
} // namespace Snowflake
