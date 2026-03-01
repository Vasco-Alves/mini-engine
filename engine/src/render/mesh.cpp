#include "mini-engine/render/mesh.hpp"
#include <modulus/gfx/buffer.hpp>

namespace me {

	Mesh::Mesh(std::shared_ptr<modulus::gfx::VertexArray> vertexArray) : m_vao(vertexArray) {}

	std::shared_ptr<Mesh> Mesh::create_cube() {
		auto vao = std::make_shared<modulus::gfx::VertexArray>();

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
		vao->add_vertex_buffer(vbo, layout);

		uint32_t indices[] = {
			0, 1, 2, 2, 3, 0, // Front
			1, 5, 6, 6, 2, 1, // Right
			7, 6, 5, 5, 4, 7, // Back
			4, 0, 3, 3, 7, 4, // Left
			4, 5, 1, 1, 0, 4, // Bottom
			3, 2, 6, 6, 7, 3  // Top
		};
		//auto ibo = std::make_shared<modulus::gfx::IndexBuffer>(indices, 36);
		auto ibo = std::make_shared<modulus::gfx::IndexBuffer>(indices, sizeof(indices));
		vao->set_index_buffer(ibo);

		return std::make_shared<Mesh>(vao);
	}

}