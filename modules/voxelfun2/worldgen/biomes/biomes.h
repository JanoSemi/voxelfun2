#include "modules/voxelfun2/misc.h"

class Biome {
public:
	Biome() {};
	~Biome() {};
	int generate_surface_block(int y, int surface_y) {
		return (y == 0) ? VoxelFun2Misc::STONE : VoxelFun2Misc::AIR;
	};

	//virtual void generate_surface_decorations(Vector2i chunk);
protected:
	int generate_default_surface_block(int y, int surface_y, int surface_block = VoxelFun2Misc::GRASS, int subsurface_block = VoxelFun2Misc::DIRT, int stone = VoxelFun2Misc::STONE, int deep_stone = VoxelFun2Misc::DEEP_STONE) {
		if (y < surface_y - 100) {
			return deep_stone;
		} else if (y < surface_y - 10) {
			return stone;
		} else if (y < surface_y) {
			return subsurface_block;
		} else if (y == surface_y) {
			return surface_block;
		} else {
			return VoxelFun2Misc::AIR;
		}
	}
};

class Meadow : public Biome {
public:
	int generate_surface_block(int y, int surface_y);
};

class SnowyMeadow : public Biome {
public:
	int generate_surface_block(int y, int surface_y);
};

class Desert : public Biome {
public:
	int generate_surface_block(int y, int surface_y);
};
