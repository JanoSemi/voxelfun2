#ifndef PLAYER_H
#define PLAYER_H

#include "../entity.h"
#include "core/engine.h"
#include "core/math/vector3.h"
#include "core/os/input.h"
#include "core/os/input_event.h"
#include "modules/voxel/edition/voxel_raycast_result.h"
#include "scene/3d/camera.h"

class Player : public Entity {
	GDCLASS(Player, Entity)

public:
	Player();
	~Player();

	void _physics_process(float delta) override;

	void _input(const Ref<InputEvent> &p_event);

	Ref<VoxelRaycastResult> get_pointed_result();

	// Setter/Getter
	void set_speed(float s) { speed = s; };
	float get_speed() const { return speed; };

	void set_jump_power(float p) { jump_power = p; };
	float get_jump_power() const { return jump_power; };

	void set_gravity(float g) { gravity = g; };
	float get_gravity() const { return gravity; };

	void set_horizontal_sensitivity(float hs) { horizontal_sensitivity = hs / -100; };
	float get_horizontal_sensitivity() const { return horizontal_sensitivity * -100; };

	void set_vertical_sensitivity(float vs) { vertical_sensitivity = vs / -100; };
	float get_vertical_sensitivity() const { return vertical_sensitivity * -100; };

	void set_camera_path(const NodePath cp) {
		camera_path = cp;
		if (!has_node(cp)) {
			return;
		}
		Camera *c = Object::cast_to<Camera>(get_node(cp));
		if (c) {
			camera = c;
		}
	}
	NodePath get_camera_path() const { return camera_path; }

	Vector3 velocity;
	float speed = 4.0;
	float jump_power = 5.0;
	float gravity = 9.8;
	float horizontal_sensitivity = -0.01;
	float vertical_sensitivity = -0.01;
	bool grounded = false;
	Camera *camera;
	NodePath camera_path;
	Input *input = Input::get_singleton();
	Engine *engine = Engine::get_singleton();

protected:
	void _notification(int p_what) override;

	static void _bind_methods();
};

#endif