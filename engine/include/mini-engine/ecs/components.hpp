#pragma once

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

		glm::mat4 get_transform() const {
			glm::mat4 rot =
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1, 0 }) *
				glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0, 1 });

			return glm::translate(glm::mat4(1.0f), position) * rot * glm::scale(glm::mat4(1.0f), scale); // Model matrix
		}
	};

	struct VelocityComponent {
		glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
	};

	struct MeshComponent {
		std::shared_ptr<me::Mesh> mesh;
		glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		MeshComponent() = default;
		MeshComponent(std::shared_ptr<me::Mesh> m, const glm::vec4& c) : mesh(m), color(c) {}
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

} // namespace me::components
