#include "common.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus.h"

/* External word holding the current buffer write position. */
extern s32 gpu_scratch_write_pointer;

/* External word holding the buffer base. */
extern s32 gpu_scratch_buffer_base;

/* Copy the value from D_8008148C to D_80081480 and register func_80041AE4. */
void begin_scene_dispatch_resource_loading(void) {
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    set_scene_phase_callback((int)func_80041AE4);
}
