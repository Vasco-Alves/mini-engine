#include "mini-engine/input/input.hpp"

#include <modulus/platform/input.hpp>

#include <unordered_map>
#include <vector>

namespace me::input {

	// -------------------------------------------------------------------------
	// Internal Types & State
	// -------------------------------------------------------------------------

	struct ActionBinding {
		std::vector<Key> keys;
		std::vector<MouseButton> buttons;
	};

	// Map action names to their bindings (e.g., "Jump" -> [Space, GamepadA])
	static std::unordered_map<std::string, ActionBinding> s_Actions;

	// Track the "Previous Frame" state to detect single-frame clicks/presses
	static std::unordered_map<Key, bool> s_KeyPrevState;
	static std::unordered_map<MouseButton, bool> s_BtnPrevState;

	// Shorten the backend type access
	using ModInput = modulus::platform::Input;

	// -------------------------------------------------------------------------
	// Polling
	// -------------------------------------------------------------------------
	void poll() {
		for (auto& [name, binding] : s_Actions) {
			for (auto k : binding.keys)
				s_KeyPrevState[k] = ModInput::is_key_down(k);

			for (auto b : binding.buttons)
				s_BtnPrevState[b] = ModInput::is_mouse_down(b);
		}
	}

	// -------------------------------------------------------------------------
	// Binding Management
	// -------------------------------------------------------------------------
	void bind_action(const std::string& name, Key key) {
		s_Actions[name].keys.push_back(key);
	}

	void bind_action(const std::string& name, MouseButton btn) {
		s_Actions[name].buttons.push_back(btn);
	}

	// -------------------------------------------------------------------------
	// Action Checks
	// -------------------------------------------------------------------------

	bool action_down(const std::string& name) {
		// If ANY key or button in the binding is down, the action is triggered.
		auto& binding = s_Actions[name];

		for (auto k : binding.keys) {
			if (ModInput::is_key_down(k)) return true;
		}

		for (auto b : binding.buttons) {
			if (ModInput::is_mouse_down(b)) return true;
		}

		return false;
	}

	bool action_pressed(const std::string& name) {
		// Pressed = Currently Down AND Not Down Previously
		auto& binding = s_Actions[name];

		for (auto k : binding.keys) {
			bool current = ModInput::is_key_down(k);
			bool prev = s_KeyPrevState[k];
			if (current && !prev) return true;
		}

		for (auto b : binding.buttons) {
			bool current = ModInput::is_mouse_down(b);
			bool prev = s_BtnPrevState[b];
			if (current && !prev) return true;
		}

		return false;
	}

	// -------------------------------------------------------------------------
	// Mouse & Axis Helpers
	// -------------------------------------------------------------------------

	float get_mouse_x() {
		auto [x, y] = ModInput::get_mouse_position();
		return x;
	}

	float get_mouse_y() {
		auto [x, y] = ModInput::get_mouse_position();
		return y;
	}

	float get_axis(Axis axis) {
		switch (axis) {
		case Axis::MouseX:		return get_mouse_x();
		case Axis::MouseY:		return get_mouse_y();
		case Axis::MouseWheel:	return ModInput::get_mouse_scroll();
		}
		return 0.0f;
	}

}