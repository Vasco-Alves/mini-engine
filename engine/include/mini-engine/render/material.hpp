#pragma once

#include <modulus/gfx/shader.hpp>
#include <modulus/gfx/texture.hpp> 

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>
#include <string>

namespace me {

	class Material {
	public:
		Material(std::shared_ptr<modulus::gfx::Shader> shader) : m_shader(shader) {}

		// Bind a texture to a specific uniform name in the shader (e.g., "u_Texture")
		void set_texture(const std::string& name, std::shared_ptr<modulus::gfx::Texture2D> texture) {
			m_textures[name] = texture;
		}

		// Set the base color (tint) of the material
		void set_color(const glm::vec4& color) {
			m_color = color;
		}

		// Binds the shader, uploads the color, and binds all associated textures to their slots
		void bind() {
			m_shader->bind();

			// Upload the base color
			m_shader->set_float4("u_Color", m_color.r, m_color.g, m_color.b, m_color.a);

			// Loop through all assigned textures and bind them to incremental slots
			int slot = 0;
			for (auto& [name, texture] : m_textures) {
				texture->bind(slot);
				m_shader->set_int(name, slot); // Tell the shader which texture unit to read from
				slot++;
			}
		}

		std::shared_ptr<modulus::gfx::Shader> get_shader() const { return m_shader; }

	private:
		std::shared_ptr<modulus::gfx::Shader> m_shader;
		std::unordered_map<std::string, std::shared_ptr<modulus::gfx::Texture2D>> m_textures;

		// Default to white so it doesn't tint textures black by default
		glm::vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

} // namespace me