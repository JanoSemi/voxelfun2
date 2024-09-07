#ifndef VOXEL_GENERATOR_VOXELFUN2_H
#define VOXEL_GENERATOR_VOXELFUN2_H

#include "../../voxel/generators/voxel_generator.h"
#include "../../voxel/util/noise/fast_noise_lite.h"

class VoxelGeneratorVoxelFun2 : public VoxelGenerator {
	GDCLASS(VoxelGeneratorVoxelFun2, VoxelGenerator)

public:
	VoxelGeneratorVoxelFun2();
	~VoxelGeneratorVoxelFun2();

	int get_used_channels_mask() const override;

	Result generate_block(VoxelBlockRequest &input) override;

	void set_hill_height(float h);
	float get_hill_height() const;

	void set_mountain_height(float h);
	float get_mountain_height() const;

	void set_seed(int s);
	int get_seed() const;

protected:
	static void _bind_methods();

private:
	struct Parameters {
		float hill_height = 10.0;
		float mountain_height = 50.0;
		int seed = 0;
	};

	Parameters _parameters;
	RWLock _parameters_lock;
	// Heightmap
	FastNoiseLite hill_noise;
	FastNoiseLite mountain_noise;
	FastNoiseLite selector_noise;

	void update_seed(int s);
};

#endif // VOXEL_GENERATOR_VOXELFUN2_H
