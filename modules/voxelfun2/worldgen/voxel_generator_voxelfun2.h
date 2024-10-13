#ifndef VOXEL_GENERATOR_VOXELFUN2_H
#define VOXEL_GENERATOR_VOXELFUN2_H

#include "biomes/biomes.h"
#include "modules/voxel/generators/voxel_generator.h"
#include "modules/voxel/util/noise/fast_noise_lite.h"

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

	void set_mountain_power(float p);
	float get_mountain_power() const;

	void set_seed(int s);
	int get_seed() const;

protected:
	static void _bind_methods();

private:
	struct Parameters {
		float hill_height = 10.0;
		float mountain_height = 50.0;
		float mountain_power = 2.5;
		int seed = 0;
	};

	struct Biomes {
		Meadow *meadow = new Meadow();
		SnowyMeadow *snowy_meadow = new SnowyMeadow();
		Desert *desert = new Desert();
	};

	Parameters _parameters;
	RWLock _parameters_lock;
	// Heightmap
	FastNoiseLite hill_noise;
	FastNoiseLite mountain_noise;
	FastNoiseLite selector_noise;
	// Biomes
	FastNoiseLite humidity_noise;
	FastNoiseLite temperature_noise;
	Biomes biomes;
	// Caves
	FastNoiseLite cheese_cave_noise;

	void update_seed(int s);
	Biome *select_biome(float humidity, float temperature);
};

#endif // VOXEL_GENERATOR_VOXELFUN2_H
