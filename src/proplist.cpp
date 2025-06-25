#include "proplist.h"

namespace MiniEngine
{

// String properties
void PropertyList::setString(const std::string& name, const std::string& value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_STRING;
    prop.stringValue = value;
}

std::string PropertyList::getString(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_STRING)
        throw MiniEngineException("Property '%s' not found or not a string", name.c_str());
    return it->second.stringValue;
}

std::string PropertyList::getString(const std::string& name, const std::string& defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_STRING)
        return defaultValue;
    return it->second.stringValue;
}

// Float properties
void PropertyList::setFloat(const std::string& name, float value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_FLOAT;
    prop.floatValue = value;
}

float PropertyList::getFloat(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_FLOAT)
        throw MiniEngineException("Property '%s' not found or not a float", name.c_str());
    return it->second.floatValue;
}

float PropertyList::getFloat(const std::string& name, float defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_FLOAT)
        return defaultValue;
    return it->second.floatValue;
}

// Integer properties
void PropertyList::setInteger(const std::string& name, int32_t value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_INTEGER;
    prop.intValue = value;
}

int32_t PropertyList::getInteger(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_INTEGER)
        throw MiniEngineException("Property '%s' not found or not an integer", name.c_str());
    return it->second.intValue;
}

int32_t PropertyList::getInteger(const std::string& name, int32_t defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_INTEGER)
        return defaultValue;
    return it->second.intValue;
}

// Boolean properties
void PropertyList::setBoolean(const std::string& name, bool value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_BOOLEAN;
    prop.boolValue = value;
}

bool PropertyList::getBoolean(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_BOOLEAN)
        throw MiniEngineException("Property '%s' not found or not a boolean", name.c_str());
    return it->second.boolValue;
}

bool PropertyList::getBoolean(const std::string& name, bool defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_BOOLEAN)
        return defaultValue;
    return it->second.boolValue;
}

// Vector3f properties
void PropertyList::setVector(const std::string& name, const Vector3f& value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_VECTOR;
    prop.vectorValue = value;
}

Vector3f PropertyList::getVector(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_VECTOR)
        throw MiniEngineException("Property '%s' not found or not a vector", name.c_str());
    return it->second.vectorValue;
}

Vector3f PropertyList::getVector(const std::string& name, const Vector3f& defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_VECTOR)
        return defaultValue;
    return it->second.vectorValue;
}

// Color properties (alias for Vector)
void PropertyList::setColor(const std::string& name, const Vector3f& value)
{
    setVector(name, value);
}

Vector3f PropertyList::getColor(const std::string& name) const
{
    return getVector(name);
}

Vector3f PropertyList::getColor(const std::string& name, const Vector3f& defaultValue) const
{
    return getVector(name, defaultValue);
}

// Point properties (alias for Vector)
void PropertyList::setPoint(const std::string& name, const Vector3f& value)
{
    setVector(name, value);
}

Vector3f PropertyList::getPoint(const std::string& name) const
{
    return getVector(name);
}

Vector3f PropertyList::getPoint(const std::string& name, const Vector3f& defaultValue) const
{
    return getVector(name, defaultValue);
}

// Transform properties
void PropertyList::setTransform(const std::string& name, const Matrix4f& value)
{
    Property& prop = m_properties[name];
    prop.type = PROP_TRANSFORM;
    prop.transformValue = value;
}

Matrix4f PropertyList::getTransform(const std::string& name) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_TRANSFORM)
        throw MiniEngineException("Property '%s' not found or not a transform", name.c_str());
    return it->second.transformValue;
}

Matrix4f PropertyList::getTransform(const std::string& name, const Matrix4f& defaultValue) const
{
    auto it = m_properties.find(name);
    if (it == m_properties.end() || it->second.type != PROP_TRANSFORM)
        return defaultValue;
    return it->second.transformValue;
}

// Utility methods
bool PropertyList::hasProperty(const std::string& name) const
{
    return m_properties.find(name) != m_properties.end();
}

void PropertyList::removeProperty(const std::string& name)
{
    m_properties.erase(name);
}

void PropertyList::clear()
{
    m_properties.clear();
}

} // namespace MiniEngine
