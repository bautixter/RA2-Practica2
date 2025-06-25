#pragma once

#include "common.h"
#include <memory>
#include <string>

namespace MiniEngine
{
    class Entity;

    /**
     * @brief Load a scene from an XML file
     * @param i_filename Path to the XML file to load
     * @return Shared pointer to the loaded Entity (scene root)
     */
    std::shared_ptr<Entity> loadFromXML(const std::string& i_filename);
}
