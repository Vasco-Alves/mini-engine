#pragma once

#include <modulus/gfx/vertex_array.hpp>

#include <memory>

namespace me {

	class Mesh {
	public:
		Mesh(std::shared_ptr<modulus::gfx::VertexArray> vertexArray);
		~Mesh() = default;

		std::shared_ptr<modulus::gfx::VertexArray> get_vao() const { return m_vao; }

		static std::shared_ptr<Mesh> create_cube();

	private:
		std::shared_ptr<modulus::gfx::VertexArray> m_vao;
	};

}