#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus.h"

/* External word holding the current buffer write position. */
extern s32 gpu_scratch_write_pointer;

/* External word holding the buffer base. */
extern s32 gpu_scratch_buffer_base;

/*
 * Resets the GPU scratch write pointer and installs load_scene_dispatch_resources as the next
 * scene phase.
 */
void begin_scene_dispatch_resource_loading(void) {
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    set_scene_phase_callback((int)load_scene_dispatch_resources);
}
