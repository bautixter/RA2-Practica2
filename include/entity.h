#pragma once

#include "common.h"
#include "transform.h"
#include <vector>
#include <memory>


typedef VkCommandBuffer CommandBuffer;

namespace MiniEngine
{
    class MeshVK;
    class Material;
    struct Frame;
    struct Runtime;
    class PropertyList;

    class Entity 
    {
    public:
        // Enum for different entity class types (needed for XML parser)
        enum class EClassType {
            EScene = 0,
            EMesh,
            EBSDF,
            EPhaseFunction,
            EEmitter,
            EMedium,
            ECamera,
            EIntegrator,
            ESampler,
            ETest,
            EReconstructionFilter,
            EClassTypeCount
        };

        explicit Entity( const Runtime& i_runtime ) : m_runtime( i_runtime ), m_classType(EClassType::EMesh){};
        virtual ~Entity() = default;
    
        bool initialize();

        void shutdown();

        static std::shared_ptr<Entity> createEntity(  const Runtime& i_runtime, const pugi::xml_node& i_node, const uint32_t i_id );

        void draw( CommandBuffer& i_command_buffer,  const Frame& i_frame );

        // Methods needed for XML parser
        virtual void activate() {}
        virtual void addChild(std::shared_ptr<Entity> child);
        virtual void setParent(std::shared_ptr<Entity> parent);
        
        EClassType getClassType() const { return m_classType; }
        void setClassType(EClassType type) { m_classType = type; }
        
        static const char* classTypeName(EClassType type);
        
        virtual std::string toString() const { return "Entity"; }

        inline Transform& getTransform()
       {
           return m_transform;
       }

       inline Material& getMaterial() const
       {
           return *m_material;
       }

       inline uint32_t getEntityOffset() const
       {
           return m_entity_offset;
       }

    protected:
        EClassType m_classType;
        std::vector<std::shared_ptr<Entity>> m_children;
        std::weak_ptr<Entity> m_parent;

    private:
        Entity( const Entity& ) = delete;
        Entity& operator=(const Entity& ) = delete;

        const Runtime& m_runtime;
        std::shared_ptr<MeshVK> m_mesh;
        Transform m_transform;
        std::shared_ptr<Material> m_material;

        uint32_t m_entity_offset;
    };
};