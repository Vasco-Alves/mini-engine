#pragma once

#include <modulus/platform/input.hpp>

#include <string>
#include <vector>

namespace me::input {

	// Alias Modulus types directly so we don't have to convert them
	using Key = modulus::platform::Key;
	using MouseButton = modulus::platform::MouseButton;

	enum class Axis {
		MouseX, MouseY, MouseWheel
	};

	// Main polling function (Call this in Engine::run loop!)
	void poll();

	// --- Actions ---
	void bind_action(const std::string& name, Key key);
	void bind_action(const std::string& name, MouseButton btn);
	bool action_down(const std::string& name);
	bool action_pressed(const std::string& name);

	// --- Axes ---
	float get_axis(Axis axis);

	// Helpers
	float get_mouse_x();
	float get_mouse_y();
}