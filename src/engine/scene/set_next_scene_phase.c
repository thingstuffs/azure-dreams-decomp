#include "common.h"
#include "engine/scene.h"
#include "slus.h"

extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/*
 * Copies gpu_scratch_buffer_base's leading word into gpu_scratch_write_pointer and registers
 * load_object_scene_dispatch_resources as the next callback.
 *
 * Next function in the binary; its address is registered as the next per-frame callback.
 *
 * Registers a function-pointer callback (matched, gcc 2.8.1, src/code2.c).
 */
void set_next_scene_phase(void)
{
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    set_scene_phase_callback(load_object_scene_dispatch_resources);
}
