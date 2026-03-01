#include "mini-engine/render/renderer.hpp"

#include <modulus/gfx/graphics.hpp>
#include <modulus/gfx/shader.hpp>

namespace me {

	struct RendererData {
		std::shared_ptr<modulus::gfx::Shader> color_shader;
	};

	static RendererData* s_Data = nullptr;

	void Renderer::init() {
		s_Data = new RendererData();

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

	void Renderer::begin_scene(const glm::mat4& view_projection) {
		s_Data->color_shader->bind();
		s_Data->color_shader->set_mat4("u_ViewProjection", view_projection);
	}

	void Renderer::end_scene() {}

	void Renderer::draw_mesh(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform, const glm::vec4& color) {
		s_Data->color_shader->set_mat4("u_Transform", transform);
		s_Data->color_shader->set_float4("u_Color", color.r, color.g, color.b, color.a);

		mesh->get_vao()->bind();
		modulus::gfx::draw_indexed(mesh->get_vao());
	}

}