#pragma once

#include "common.h"
#include <string>
#include <map>
#include <stdexcept>

namespace MiniEngine
{

/**
 * @brief A simple property list class for storing typed key-value pairs
 * 
 * This class is used to pass parameters to various engine objects during
 * construction. It supports basic types like strings, floats, integers,
 * booleans, vectors, and transforms.
 */
class PropertyList
{
public:
    PropertyList() = default;
    ~PropertyList() = default;

    // String properties
    void setString(const std::string& name, const std::string& value);
    std::string getString(const std::string& name) const;
    std::string getString(const std::string& name, const std::string& defaultValue) const;

    // Float properties
    void setFloat(const std::string& name, float value);
    float getFloat(const std::string& name) const;
    float getFloat(const std::string& name, float defaultValue) const;

    // Integer properties
    void setInteger(const std::string& name, int32_t value);
    int32_t getInteger(const std::string& name) const;
    int32_t getInteger(const std::string& name, int32_t defaultValue) const;

    // Boolean properties
    void setBoolean(const std::string& name, bool value);
    bool getBoolean(const std::string& name) const;
    bool getBoolean(const std::string& name, bool defaultValue) const;

    // Vector3f properties
    void setVector(const std::string& name, const Vector3f& value);
    Vector3f getVector(const std::string& name) const;
    Vector3f getVector(const std::string& name, const Vector3f& defaultValue) const;

    // Color (Vector3f) properties
    void setColor(const std::string& name, const Vector3f& value);
    Vector3f getColor(const std::string& name) const;
    Vector3f getColor(const std::string& name, const Vector3f& defaultValue) const;

    // Point (Vector3f) properties
    void setPoint(const std::string& name, const Vector3f& value);
    Vector3f getPoint(const std::string& name) const;
    Vector3f getPoint(const std::string& name, const Vector3f& defaultValue) const;

    // Transform (Matrix4f) properties
    void setTransform(const std::string& name, const Matrix4f& value);
    Matrix4f getTransform(const std::string& name) const;
    Matrix4f getTransform(const std::string& name, const Matrix4f& defaultValue) const;

    // Check if a property exists
    bool hasProperty(const std::string& name) const;

    // Remove a property
    void removeProperty(const std::string& name);

    // Clear all properties
    void clear();

private:
    enum PropertyType {
        PROP_STRING,
        PROP_FLOAT,
        PROP_INTEGER,
        PROP_BOOLEAN,
        PROP_VECTOR,
        PROP_TRANSFORM
    };

    struct Property {
        PropertyType type;
        std::string stringValue;
        float floatValue;
        int32_t intValue;
        bool boolValue;
        Vector3f vectorValue;
        Matrix4f transformValue;

        Property() : type(PROP_STRING), floatValue(0.0f), intValue(0), boolValue(false) {}
    };

    std::map<std::string, Property> m_properties;
};

} // namespace MiniEngine
