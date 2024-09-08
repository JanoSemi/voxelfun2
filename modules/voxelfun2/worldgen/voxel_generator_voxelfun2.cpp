#include "voxel_generator_voxelfun2.h"

VoxelGeneratorVoxelFun2::VoxelGeneratorVoxelFun2() {
	// Heightmap
	hill_noise.set_period(128.0);
	mountain_noise.set_period(192.0);
	selector_noise.set_period(512.0);
	// Caves
	cheese_cave_noise.set_period(128.0);
	// Other stuff
	update_seed(_parameters.seed);
}

VoxelGeneratorVoxelFun2::~VoxelGeneratorVoxelFun2() {
}

int VoxelGeneratorVoxelFun2::get_used_channels_mask() const {
	return (1 << VoxelBufferInternal::CHANNEL_TYPE);
}

void VoxelGeneratorVoxelFun2::set_hill_height(float h) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.hill_height = h;
}

float VoxelGeneratorVoxelFun2::get_hill_height() const {
	RWLockRead rlock(_parameters_lock);
	return _parameters.hill_height;
}

void VoxelGeneratorVoxelFun2::set_mountain_height(float h) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.mountain_height = h;
}

float VoxelGeneratorVoxelFun2::get_mountain_height() const {
	RWLockRead rlock(_parameters_lock);
	return _parameters.mountain_height;
}

void VoxelGeneratorVoxelFun2::set_seed(int s) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.seed = s;
	update_seed(s);
}

int VoxelGeneratorVoxelFun2::get_seed() const {
	RWLockRead rlock(_parameters_lock);
	return _parameters.seed;
}

void VoxelGeneratorVoxelFun2::update_seed(int seed) {
	hill_noise.set_seed(seed);
	mountain_noise.set_seed(seed);
	selector_noise.set_seed(seed);
	cheese_cave_noise.set_seed(seed);
}

VoxelGenerator::Result VoxelGeneratorVoxelFun2::generate_block(VoxelBlockRequest &input) {
	Result result;

	Parameters params;
	{
		RWLockRead rlock(_parameters_lock);
		params = _parameters;
	}

	VoxelBufferInternal &out_buffer = input.voxel_buffer;
	const Vector3i origin = input.origin_in_voxels;
	const Vector3i bs = out_buffer.get_size();
	const float margin = 1 << input.lod;
	const int lod = input.lod;

	for (int x = 0; x < bs.x; ++x) {
		int gx = origin.x + x;
		for (int z = 0; z < bs.z; ++z) {
			int gz = origin.z + z;
			float hill_y = hill_noise.get_noise_2d(gx, gz) * params.hill_height;
			float mountain_y = (mountain_noise.get_noise_2d(gx, gz) * params.mountain_height) + params.mountain_height / 2;
			float selector = selector_noise.get_noise_2d(gx, gz) * 0.5f + 0.5f;
			int surface_y = int(Math::lerp(hill_y, mountain_y, selector));
			for (int y = 0; y < bs.y; ++y) {
				int gy = origin.y + y;
				bool cheese_cave = ((selector > 0.4) ? gy <= surface_y : gy < surface_y) && (cheese_cave_noise.get_noise_3d(gx, gy, gz)) > 0.6;
				if (!cheese_cave && gy <= surface_y) {
					out_buffer.set_voxel(1, x, y, z);
				}
			}
		} // for z
	} // for x

	return result;
}

void VoxelGeneratorVoxelFun2::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_hill_height", "h"), &VoxelGeneratorVoxelFun2::set_hill_height);
	ClassDB::bind_method(D_METHOD("get_hill_height"), &VoxelGeneratorVoxelFun2::get_hill_height);
	ClassDB::bind_method(D_METHOD("set_mountain_height", "h"), &VoxelGeneratorVoxelFun2::set_mountain_height);
	ClassDB::bind_method(D_METHOD("get_mountain_height"), &VoxelGeneratorVoxelFun2::get_mountain_height);
	ClassDB::bind_method(D_METHOD("set_seed", "s"), &VoxelGeneratorVoxelFun2::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VoxelGeneratorVoxelFun2::get_seed);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "hill_height"), "set_hill_height", "get_hill_height");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "mountain_height"), "set_mountain_height", "get_mountain_height");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
}
