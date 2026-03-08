#include <sandbox/systems/camera_movement.hpp>

#include <mini-engine/ecs/components.hpp>
#include <mini-engine/input/input.hpp>

namespace sandbox::systems {

	CameraMovementSystem::CameraMovementSystem(me::Registry& registry, me::entity::entity_id camera) : me::System(registry), m_camera(camera) {}

	void CameraMovementSystem::on_update(float dt) {
		auto* transform = m_registry.try_get_component<me::components::TransformComponent>(m_camera);
		if (!transform) return;

		float sensitivity = 30.0f; // Degrees per second
		float speed = 5.0f; // Units per second

		// --- FPS rotation ---
		// Pitch
		if (me::input::action_down("RotateU")) transform->rotation.x += sensitivity * dt;
		if (me::input::action_down("RotateD")) transform->rotation.x -= sensitivity * dt;

		// Yaw
		if (me::input::action_down("RotateR")) transform->rotation.y -= sensitivity * dt;
		if (me::input::action_down("RotateL")) transform->rotation.y += sensitivity * dt;

		// Clamp Pitch so you can't flip the camera upside down
		if (transform->rotation.x > 89.0f) transform->rotation.x = 89.0f;
		if (transform->rotation.x < -89.0f) transform->rotation.x = -89.0f;

		// --- Free Fly Movement ---
		// Get the local directions from the component
		glm::vec3 forward = transform->get_forward();
		glm::vec3 right = transform->get_right();
		glm::vec3 up = transform->get_up();

		// Move along the local axes
		if (me::input::action_down("Forward")) transform->position += forward * speed * dt;
		if (me::input::action_down("Backward")) transform->position -= forward * speed * dt;

		if (me::input::action_down("Right")) transform->position += right * speed * dt;
		if (me::input::action_down("Left")) transform->position -= right * speed * dt;

		if (me::input::action_down("Up")) transform->position += up * speed * dt;
		if (me::input::action_down("Down")) transform->position -= up * speed * dt;
	}

}