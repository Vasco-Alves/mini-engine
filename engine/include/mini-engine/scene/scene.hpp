#pragma once

#include <mini-ecs/registry.hpp>

namespace me {

	class Scene {
	public:
		virtual ~Scene() = default;

		virtual void on_resize(int width, int height) {}
		virtual void on_start(int width, int height) {}
		virtual void on_update(float dt) {}
		virtual void on_render() {}
		virtual void on_close() {}

	protected:
		me::Registry registry;
	};

}