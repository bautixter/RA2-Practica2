#version 460

#extension GL_ARB_shader_draw_parameters : enable

// Vertex attributes from the mesh
layout( location = 0 ) in vec3 v_positions;  // Vertex position in model space
layout( location = 1 ) in vec3 v_normals;    // Vertex normal (not used in shadow pass)
layout( location = 2 ) in vec2 v_uvs;        // Texture coordinates (not used in shadow pass)

// Light data structure - contains all information needed for each light source
struct LightData
{
    vec4 m_light_pos;        // Light position in world space (w component unused)
    vec4 m_radiance;         // Light color and intensity
    vec4 m_attenuattion;     // Attenuation factors for distance falloff
    mat4 m_view_projection;  // Light's view-projection matrix for shadow mapping
};

// Per-frame uniform buffer - contains camera and lighting data that changes each frame
layout( std140, set = 0, binding = 0 ) uniform PerFrameData
{
    vec4      m_camera_pos;           // Camera position in world space
    mat4      m_view;                 // View matrix (world to view space)
    mat4      m_projection;           // Projection matrix (view to clip space)
    mat4      m_view_projection;      // Combined view-projection matrix
    mat4      m_inv_view;             // Inverse view matrix
    mat4      m_inv_projection;       // Inverse projection matrix
    mat4      m_inv_view_projection;  // Inverse view-projection matrix
    vec4      m_clipping_planes;      // Near/far clipping plane distances
    LightData m_lights[ 10 ];         // Array of light data (up to 10 lights)
    uint      m_number_of_lights;     // Actual number of active lights
} per_frame_data;

// Per-object data structure - contains transform and material properties for each object
struct ObjectData
{
    mat4 m_model;              // Model matrix (model to world space)
    vec4 m_albedo;             // Base color/albedo
    vec4 m_metallic_roughness; // Material properties (metallic, roughness, etc.)
};

// Per-object storage buffer - contains data for all objects in the scene
layout(std140,set = 1, binding = 0) readonly buffer ObjectBufferData
{
    ObjectData objects[];  // Dynamic array of object data
} per_object_data;

// Output to geometry shader - position in view space
layout( location = 0 ) out vec3 f_position;

void main() {
    // Transform vertex from model space to view space
    // 1. Apply model matrix to transform from model to world space
    // 2. Apply view matrix to transform from world to view space
    vec4 pos = per_frame_data.m_view * per_object_data.objects[ gl_BaseInstance ].m_model * vec4(v_positions, 1.0);
    
    // Pass view space position to geometry shader
    f_position = pos.xyz;

    // Note: gl_Position is not set here because the geometry shader will handle final positioning
    // The geometry shader will transform this to light space for each light
}