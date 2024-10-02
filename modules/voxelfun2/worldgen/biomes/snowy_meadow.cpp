#include "biomes.h"
#include "modules/voxelfun2/misc.h"

int SnowyMeadow::generate_surface_block(int y, int surface_y) {
	return generate_default_surface_block(y, surface_y, VoxelFun2Misc::SNOW);
}
