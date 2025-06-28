#version 460

layout(triangles) in;
layout(triangle_strip, max_vertices = 30) out;

#extension GL_ARB_shader_draw_parameters : enable

// Input from vertex shader
layout( location = 0 ) in vec3 g_position[];

// Light data structure - contains all information needed for each light source
struct LightData
{
    vec4 m_light_pos;        // Light position in world space
    vec4 m_radiance;         // Light color and intensity  
    vec4 m_attenuattion;     // Attenuation factors for distance falloff
    mat4 m_view_projection;  // Light's view-projection matrix for shadow mapping
};

// Per-frame uniform buffer - contains camera and lighting data
layout( std140, set = 0, binding = 0 ) uniform PerFrameData
{
    vec4      m_camera_pos;           // Camera position in world space
    mat4      m_view;                 // View matrix (world to view space)
    mat4      m_projection;           // Projection matrix (view to clip space)
    mat4      m_view_projection;      // Combined view-projection matrix
    mat4      m_inv_view;             // Inverse view matrix (view to world space)
    mat4      m_inv_projection;       // Inverse projection matrix
    mat4      m_inv_view_projection;  // Inverse view-projection matrix
    vec4      m_clipping_planes;      // Near/far clipping plane distances
    LightData m_lights[ 10 ];         // Array of light data (up to 10 lights)
    uint      m_number_of_lights;     // Actual number of active lights
} per_frame_data;

void main() {
    // For each light source, render the triangle to its corresponding layer
    for (int i = 0; i < per_frame_data.m_number_of_lights; ++i) {
        // Set the target layer for this light (each light gets its own layer in the shadow map array)
        gl_Layer = i;
        
        // Process each vertex of the input triangle
        for(int j = 0; j < 3; ++j)
        {
            // Transform vertex from view space back to world space
            vec4 worldPos = per_frame_data.m_inv_view * vec4(g_position[j], 1.0f);

            // Transform world position to light's clip space using light's view-projection matrix
            vec4 lightSpacePos = per_frame_data.m_lights[i].m_view_projection * worldPos;
            gl_Position = lightSpacePos;
            
            EmitVertex();
        }
        EndPrimitive();
    }
}