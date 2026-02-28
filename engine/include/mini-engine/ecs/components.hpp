#pragma once

namespace me::components {

	struct Transform {
		float x = 0.0f, y = 0.0f, z = 0.0f;				// Position
		float rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;	// Euler angles in Degrees
		float sx = 1.0f, sy = 1.0f, sz = 1.0f;			// Scale
	};

	struct Camera {
		float target_x = 0.0f, target_y = 0.0f, target_z = 0.0f; // Look at
		float up_x = 0.0f, up_y = 1.0f, up_z = 0.0f;
		float fovy = 45.0f;
		int projection = 0; // 0 = Perspective / 1 = Orthographic
		bool active = true;
	};

	struct Velocity {
		float vx = 0.0f, vy = 0.0f, vz = 0.0f;
	};
}