#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform; // Local object transform (Model Matrix)

out vec4 v_Color;

void main() {
    v_Color = a_Color;
    
    // Multiply: Proj * View * Model * Vertex
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}