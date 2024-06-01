#pragma once

#include "core/core.h"
#include "core/component.h"
#include "renderer.h"
#include "shader.h"
#include "mesh.h"
#include "vendor/includes/OBJ_Loader.h"

namespace Snowflake
{
    class Renderable : public Component
    {
    protected:
        std::string mName;
        std::vector<Mesh> mMeshes;

    public:
        Renderable() : Component(ComponentType::RENDERABLE)
        {
            // Does constructor need anything?
        }
        Renderable(std::vector<float> vertices, std::vector<unsigned int> indices) : Component(ComponentType::RENDERABLE)
        {
            Material m;
            Mesh mesh(vertices, indices, m);
            mMeshes.emplace_back(mesh);
        }
        void draw()
        {
            // draw all meshes
            for (auto &mesh : mMeshes)
                mesh.draw();
        }
        // static std::shared_ptr<Renderable> create();
    };

    class Model : public Renderable
    {
    private:
        void loadModel(std::string const &path)
        {
            objl::Loader loader;
            if (!loader.LoadFile(path))
                SF_LOGE("Unable to load object");
            for (auto &objmesh : loader.LoadedMeshes)
            {
                std::vector<float> vertices;
                std::vector<unsigned int> indices;
                Material m;
                for (int i = 0; i < objmesh.Vertices.size(); i++)
                {
                    vertices.push_back(objmesh.Vertices[i].Position.X);
                    vertices.push_back(objmesh.Vertices[i].Position.Y);
                    vertices.push_back(objmesh.Vertices[i].Position.Z);
                    vertices.push_back(objmesh.Vertices[i].Normal.X);
                    vertices.push_back(objmesh.Vertices[i].Normal.Y);
                    vertices.push_back(objmesh.Vertices[i].Normal.Z);
                    vertices.push_back(objmesh.Vertices[i].TextureCoordinate.X);
                    vertices.push_back(objmesh.Vertices[i].TextureCoordinate.Y);
                }
                for (int i = 0; i < objmesh.Indices.size(); i++)
                {
                    indices.push_back(objmesh.Indices[i]);
                }
                Mesh mesh(vertices, indices, m);
                mMeshes.push_back(mesh);
            }
        }

    public:
        // constructor
        Model(std::string const &path) { loadModel(path); }
    };
} // namespace Snowflake
