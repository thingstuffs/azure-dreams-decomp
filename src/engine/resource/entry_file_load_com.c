#include "common.h"

/* Resource flag and load helpers. */

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void mark_object_removal_for_inner_release(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* --- wave-60 --- */

/* Ring-buffer size accumulator. */
extern int gpu_scratch_ring_size;

/* Adds the amount to the global accumulator. */
void adjust_resource_decode_buffer_capacity(int amount)
{
    gpu_scratch_ring_size = gpu_scratch_ring_size + amount;
}


extern void file_load_com(void *arg);

typedef struct { u32 word; } PackedLoc;
extern PackedLoc scene_texture_data_resource;

/* Passes the global buffer to file_load_com. */
void func_80050FCC(void)
{
    file_load_com(&scene_texture_data_resource);
}

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void func_8004B1A4(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
