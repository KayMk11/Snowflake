#pragma once

#include <glm/glm.hpp>
#include "texture.h"
#include "core/core.h"

namespace Snowflake {
    class Material {
    public:
        std::string name;
        glm::vec3 ambient;      // Ka
        glm::vec3 diffuse;      // Kd
        glm::vec3 specular;     // Ks
        float shininess;        // Ns
        float refractive_index; // Ni
        float alpha;            // dissolve / d
        int illumination;       // illum

        std::vector<Texture> textures;

        std::string map_ambient_path;
        std::string map_diffuse_path;
        std::string map_specular_path;
        std::string map_shininess_path;
        std::string map_alpha_path;
        std::string map_bump_path;

        Material(){};
    };
}