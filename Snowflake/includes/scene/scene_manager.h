#pragma once

#include "core/core.h"
#include "core/entity.h"

namespace Snowflake
{
    class Scene
    {
        std::vector<std::shared_ptr<Entity>> mEntities;

    public:
        uint32_t addToScene(std::shared_ptr<Entity> entity)
        {
            mEntities.push_back(entity);
            return mEntities.size();
        }
        std::vector<std::shared_ptr<Entity>> &getEntities()
        {
            return mEntities;
        }
    };
} // namespace Snowflake
