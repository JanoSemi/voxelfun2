#ifndef ENTITY_H
#define ENTITY_H

#include "core/node_path.h"
#include "modules/voxel/edition/voxel_tool_terrain.h"
#include "modules/voxel/terrain/voxel_box_mover.h"
#include "modules/voxel/terrain/voxel_terrain.h"
#include "scene/3d/spatial.h"

class Entity : public Spatial {
	GDCLASS(Entity, Spatial)
public:
	Entity();
	~Entity();
	virtual void _physics_process(float delta);

	void set_hitbox(AABB hb) { hitbox = hb; }
	AABB get_hitbox() const { return hitbox; }

	void set_terrain_path(const NodePath p) {
		terrain_path = p;
		if (!has_node(p)) {
			return;
		}
		VoxelTerrain *t = Object::cast_to<VoxelTerrain>(get_node(p));
		if (t) {
			terrain = t;
			tool = terrain->get_voxel_tool();
		}
	}
	NodePath get_terrain_path() const { return terrain_path; }

protected:
	virtual void _notification(int p_what);
	static void _bind_methods();

	AABB hitbox;
	VoxelTerrain *terrain;
	NodePath terrain_path;
	Ref<VoxelTool> tool;
	VoxelBoxMover terrain_collision;
};

#endif