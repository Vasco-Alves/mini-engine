#include "mini-engine/render/mesh.hpp"
#include <modulus/gfx/buffer.hpp>

namespace me {

	Mesh::Mesh(std::shared_ptr<modulus::gfx::VertexArray> vertexArray) : m_vao(vertexArray) {}

	std::shared_ptr<Mesh> Mesh::create_cube() {
		auto vao = std::make_shared<modulus::gfx::VertexArray>();

		// 24 Vertices: 4 per face (Position X, Y, Z + UV U, V)
		float vertices[] = {
			// Front Face
			-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 0: Bottom Left
			0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 1: Bottom Right
			0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 2: Top Right
			-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 3: Top Left
			// Back Face
			0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 4: Bottom Left
			-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 5: Bottom Right
			-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 6: Top Right
			0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 7: Top Left
			// Left Face
			-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 8: Bottom Left
			-0.5f, -0.5f,  0.5f,   1.0f, 0.0f, // 9: Bottom Right
			-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, // 10: Top Right
			-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 11: Top Left
			// Right Face
			0.5f, -0.5f,  0.5f,   0.0f, 0.0f, // 12: Bottom Left
			0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 13: Bottom Right
			0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 14: Top Right
			0.5f,  0.5f,  0.5f,   0.0f, 1.0f, // 15: Top Left
			// Top Face
			-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, // 16: Bottom Left
			0.5f,  0.5f,  0.5f,   1.0f, 0.0f, // 17: Bottom Right
			0.5f,  0.5f, -0.5f,   1.0f, 1.0f, // 18: Top Right
			-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, // 19: Top Left
			// Bottom Face
			-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // 20: Bottom Left
			0.5f, -0.5f, -0.5f,   1.0f, 0.0f, // 21: Bottom Right
			0.5f, -0.5f,  0.5f,   1.0f, 1.0f, // 22: Top Right
			-0.5f, -0.5f,  0.5f,   0.0f, 1.0f  // 23: Top Left
		};

		auto vbo = std::make_shared<modulus::gfx::VertexBuffer>(vertices, sizeof(vertices));

		modulus::gfx::BufferLayout layout = {
			{ modulus::gfx::ShaderDataType::Float3, "a_Position" },
			{ modulus::gfx::ShaderDataType::Float2, "a_TexCoord" }
		};
		vao->add_vertex_buffer(vbo, layout);

		// 36 Indices (6 faces * 2 triangles * 3 vertices)
		uint32_t indices[] = {
			 0,  1,  2,  2,  3,  0, // Front
			 4,  5,  6,  6,  7,  4, // Back
			 8,  9, 10, 10, 11,  8, // Left
			12, 13, 14, 14, 15, 12, // Right
			16, 17, 18, 18, 19, 16, // Top
			20, 21, 22, 22, 23, 20  // Bottom
		};

		auto ibo = std::make_shared<modulus::gfx::IndexBuffer>(indices, sizeof(indices) / sizeof(uint32_t));
		vao->set_index_buffer(ibo);

		return std::make_shared<Mesh>(vao);
	}

}