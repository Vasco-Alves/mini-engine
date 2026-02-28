#include "mini-engine/render/renderer.hpp"
#include "mini-engine/render/perspective_camera.hpp"

#include <modulus/gfx/graphics.hpp>
#include <modulus/gfx/shader.hpp>

namespace me {

	struct RendererData {
		std::shared_ptr<modulus::gfx::VertexArray> cube_vao;
		std::shared_ptr<modulus::gfx::Shader> color_shader;
	};

	static RendererData* s_Data = nullptr;

	void Renderer::init() {
		s_Data = new RendererData();
		s_Data->cube_vao = std::make_shared<modulus::gfx::VertexArray>();

		// 1. Cube Vertices (8 corners of a box)
		float vertices[] = {
			-0.5f, -0.5f,  0.5f, // 0: Front Bottom Left
			 0.5f, -0.5f,  0.5f, // 1: Front Bottom Right
			 0.5f,  0.5f,  0.5f, // 2: Front Top Right
			-0.5f,  0.5f,  0.5f, // 3: Front Top Left
			-0.5f, -0.5f, -0.5f, // 4: Back Bottom Left
			 0.5f, -0.5f, -0.5f, // 5: Back Bottom Right
			 0.5f,  0.5f, -0.5f, // 6: Back Top Right
			-0.5f,  0.5f, -0.5f  // 7: Back Top Left
		};

		auto vbo = std::make_shared<modulus::gfx::VertexBuffer>(vertices, sizeof(vertices));
		modulus::gfx::BufferLayout layout = {
			{ modulus::gfx::ShaderDataType::Float3, "a_Position" }
		};

		s_Data->cube_vao->add_vertex_buffer(vbo, layout);

		// 2. Cube Indices (6 faces * 2 triangles * 3 vertices = 36 indices)
		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0, // Front
			1, 5, 6, 6, 2, 1, // Right
			7, 6, 5, 5, 4, 7, // Back
			4, 0, 3, 3, 7, 4, // Left
			4, 5, 1, 1, 0, 4, // Bottom
			3, 2, 6, 6, 7, 3  // Top
		};
		auto ibo = std::make_shared<modulus::gfx::IndexBuffer>(indices, 36);
		s_Data->cube_vao->set_index_buffer(ibo);

		// 3. The 3D Shader
		std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            void main() {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

		std::string fragmentSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            uniform vec4 u_Color;
            
            void main() {
                color = u_Color;
            }
        )";

		s_Data->color_shader = std::make_shared<modulus::gfx::Shader>(vertexSrc, fragmentSrc);
	}

	void Renderer::shutdown() {
		delete s_Data;
	}

	void Renderer::begin_scene(const camera::PerspectiveCamera& camera) {
		s_Data->color_shader->bind();
		s_Data->color_shader->set_mat4("u_ViewProjection", camera.get_view_projection_matrix());
	}

	void Renderer::end_scene() {}

	void Renderer::draw_cube(const glm::mat4& transform, const glm::vec4& color) {
		s_Data->color_shader->set_mat4("u_Transform", transform);
		s_Data->color_shader->set_float4("u_Color", color.r, color.g, color.b, color.a);

		s_Data->cube_vao->bind();
		modulus::gfx::draw_indexed(s_Data->cube_vao);
	}
}