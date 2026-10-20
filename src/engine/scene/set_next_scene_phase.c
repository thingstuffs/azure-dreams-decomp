#include "common.h"

extern s32 gpu_scratch_write_pointer;
extern s32 gpu_scratch_buffer_base;

/* Next function in the binary; its address is registered as the next
 * per-frame callback. */
extern void func_80043D04(void);

/* Registers a function-pointer callback (matched, gcc 2.8.1, src/code2.c). */
extern void set_scene_phase_callback(void (*a0)(void));

/* Copies D_8008148C's leading word into D_80081480 and registers func_80043D04 as the next callback. */
void set_next_scene_phase(void)
{
    gpu_scratch_write_pointer = gpu_scratch_buffer_base;
    set_scene_phase_callback(func_80043D04);
}
