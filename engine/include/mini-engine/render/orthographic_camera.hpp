#pragma once

#include <glm/glm.hpp>

namespace me::camera {

	class OrthographicCamera {
	public:
		// left, right, bottom, top define the visible area
		OrthographicCamera(float left, float right, float bottom, float top);

		void set_position(const glm::vec3& position) { m_Position = position; recalculate_view_matrix(); }
		const glm::vec3& get_position() const { return m_Position; }

		void set_rotation(float rotation) { m_Rotation = rotation; recalculate_view_matrix(); }
		float get_rotation() const { return m_Rotation; }

		const glm::mat4& get_view_matrix() const { return m_ViewMatrix; }

		void set_projection(float left, float right, float bottom, float top);
		const glm::mat4& get_projection_matrix() const { return m_ProjectionMatrix; }

		const glm::mat4& get_view_projection_matrix() const { return m_ViewProjectionMatrix; } // The combined matrix (Projection * View) used by the shader

	private:
		void recalculate_view_matrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f; // Z-axis rotation (2D)
	};

} // namespace me::camera