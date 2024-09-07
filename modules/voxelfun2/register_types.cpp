/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "worldgen/voxel_generator_voxelfun2.h"

void register_voxelfun2_types() {
    ClassDB::register_class<VoxelGeneratorVoxelFun2>();
}

void unregister_voxelfun2_types() {
   // Nothing to do here in this example.
}
