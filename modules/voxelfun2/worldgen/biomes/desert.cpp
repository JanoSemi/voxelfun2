#include "biomes.h"
#include "modules/voxelfun2/misc.h"

int Desert::generate_surface_block(int y, int surface_y) {
	if (y < surface_y - 100) {
		return VoxelFun2Misc::DEEP_STONE;
	} else if (y < surface_y - 20) {
		return VoxelFun2Misc::STONE;
	} else if (y < surface_y - 10) {
		return VoxelFun2Misc::SAND; // Sandstone?
	} else if (y <= surface_y) {
		return VoxelFun2Misc::SAND;
	} else {
		return VoxelFun2Misc::AIR;
	}
}
