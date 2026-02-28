#include "mini-engine/render/perspective_camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace me::camera {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float near_clip, float far_clip) {
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::set_projection(float fov, float aspect_ratio, float near_clip, float far_clip) {
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::recalculate_view_matrix() {
		// Calculate the direction the camera is looking based on Pitch and Yaw
		glm::vec3 front{};
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front = glm::normalize(front);

		// View matrix is created using "LookAt" (Position, Target, Up Vector)
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + front, glm::vec3(0.0f, 1.0f, 0.0f));
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
