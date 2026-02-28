#pragma once

#include <glm/glm.hpp>

namespace me::camera {
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fov, float aspect_ratio, float near_clip, float far_clip);

		void set_projection(float fov, float aspect_ratio, float near_clip, float far_clip);

		void set_position(const glm::vec3& position) { m_Position = position; recalculate_view_matrix(); }
		const glm::vec3& get_position() const { return m_Position; }

		void set_rotation(float pitch, float yaw) { m_Pitch = pitch; m_Yaw = yaw; recalculate_view_matrix(); }

		const glm::mat4& get_view_projection_matrix() const { return m_ViewProjectionMatrix; }

	private:
		void recalculate_view_matrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Pitch = 0.0f;
		float m_Yaw = -90.0f; // Look down the -Z axis by default
	};
}