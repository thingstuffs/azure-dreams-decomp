#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus.h"
#include "slus/gp_af3_pair.h"

/*
 * Resets the GPU scratch write pointer and installs load_scene_dispatch_resources as the next
 * scene phase.
 */
void begin_scene_dispatch_resource_loading(void) {
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    set_scene_phase_callback((int)load_scene_dispatch_resources);
}
