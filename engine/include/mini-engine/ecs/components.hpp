#pragma once

#include "mini-engine/render/material.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace me {
	class Mesh;
}

namespace me::components {

	struct TransformComponent {
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f }; // Euler angles in Degrees
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		// Helper to get just the rotation matrix. 
		glm::mat4 get_rotation_matrix() const {
			return glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0, 1 });
		}

		// Model Matrix
		glm::mat4 get_transform() const {
			return glm::translate(glm::mat4(1.0f), position) * get_rotation_matrix() * glm::scale(glm::mat4(1.0f), scale);
		}

		// --- Directional Helpers ---
		glm::vec3 get_forward() const {
			return glm::normalize(glm::vec3(get_rotation_matrix() * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
		}

		glm::vec3 get_right() const {
			return glm::normalize(glm::vec3(get_rotation_matrix() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
		}

		glm::vec3 get_up() const {
			return glm::normalize(glm::vec3(get_rotation_matrix() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
		}
	};

	struct CameraComponent {
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };

		ProjectionType type = ProjectionType::Perspective;

		// Projection parameters
		float fov = 45.0f;
		float aspect_ratio = 16.0f / 9.0f;
		float near_clip = 0.1f;
		float far_clip = 100.0f;

		// Orthographic specific
		float ortho_size = 10.0f;

		glm::vec4 viewport = { 0.0f, 0.0f, 1.0f, 1.0f };
		int render_priority = 0;

		bool is_main_camera = true;
		bool is_active = true;
	};

	struct SpriteComponent {
		std::shared_ptr<modulus::gfx::Texture2D> texture;
		glm::vec4 tint{ 1.0f, 1.0f, 1.0f, 1.0f }; // Base color (white)

		SpriteComponent(const std::string& path) {
			texture = std::make_shared<modulus::gfx::Texture2D>(path);
		}
	};

	struct VelocityComponent {
		glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
	};

	struct MeshComponent {
		std::shared_ptr<me::Mesh> mesh;
		std::shared_ptr<me::Material> material = nullptr;
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		MeshComponent() = default;
		MeshComponent(std::shared_ptr<me::Mesh> m) : mesh(m) {}
		MeshComponent(std::shared_ptr<me::Mesh> m, const glm::vec4& c) : mesh(m), color(c) {}
	};

} // namespace me::components
