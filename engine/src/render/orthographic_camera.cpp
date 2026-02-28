#include "mini-engine/render/orthographic_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace me::camera {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_ViewMatrix(1.0f) {
		set_projection(left, right, bottom, top);
	}

	void OrthographicCamera::recalculate_view_matrix() {
		// Create a transform for the camera (Position + Rotation)
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		// The View Matrix is the INVERSE of the Camera's Transform
		// (Moving camera right = Moving world left)
		m_ViewMatrix = glm::inverse(transform);

		// Combine them
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::set_projection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

} // namespace me::camera