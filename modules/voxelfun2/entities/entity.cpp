#include "entity.h"
#include "scene/main/node.h"

Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_READY:
			// In case path is set before the player entered the tree (aka via the Inspector)
			if (has_node(terrain_path)) {
				VoxelTerrain *t = Object::cast_to<VoxelTerrain>(get_node(terrain_path));
				if (t) {
					terrain = t;
					tool = terrain->get_voxel_tool();
				}
			}
			break;
		case Node::NOTIFICATION_PHYSICS_PROCESS:
			_physics_process(get_physics_process_delta_time());
			break;
	}
}

void Entity::_physics_process(float delta) {
}

void Entity::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_hitbox", "hb"), &Entity::set_hitbox);
	ClassDB::bind_method(D_METHOD("get_hitbox"), &Entity::get_hitbox);
	ClassDB::bind_method(D_METHOD("set_terrain_path"), &Entity::set_terrain_path);
	ClassDB::bind_method(D_METHOD("get_terrain_path"), &Entity::get_terrain_path);

	ADD_GROUP("Collision", "collision_");
	ADD_PROPERTY(PropertyInfo(Variant::AABB, "collision_hitbox"), "set_hitbox", "get_hitbox");
	ADD_GROUP("Nodes", "node_");
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "node_terrain", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "VoxelTerrain"), "set_terrain_path", "get_terrain_path");
}
