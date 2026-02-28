#pragma once

#include "mini-engine/render/perspective_camera.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace me {

	class Renderer {
	public:
		static void init();
		static void shutdown();

		static void begin_scene(const camera::PerspectiveCamera& camera);
		static void end_scene();

		static void draw_cube(const glm::mat4& transform, const glm::vec4& color);
	};

}