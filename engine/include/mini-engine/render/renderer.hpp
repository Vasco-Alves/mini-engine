#pragma once

#include "mini-engine/render/mesh.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace me {

	class Renderer {
	public:
		static void init();
		static void shutdown();

		static void begin_scene(const glm::mat4& view_projection);
		static void end_scene();

		static void draw_mesh(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform, const glm::vec4& color);
	};

}