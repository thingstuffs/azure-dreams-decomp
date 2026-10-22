/* Object removal flags, resource decode-buffer sizing and scene texture loading. */
#include "common.h"
#include "engine/node.h"
#include "shared/object_flags.h"
#include "engine/resource.h"
#include "engine/scene.h"
#include "slus/data.h"

/* Resource flag and load helpers. */

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void mark_object_removal_for_inner_release(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

/* --- wave-60 --- */

/* Ring-buffer size accumulator. */

/* Adds the amount to the global accumulator. */
void adjust_resource_decode_buffer_capacity(int amount)
{
    gpu_scratch_ring_size = gpu_scratch_ring_size + amount;
}

typedef struct { u32 word; } PackedLoc;
extern PackedLoc scene_texture_data_resource;

/* Passes the global buffer to file_load_com. */
void load_scene_texture_resource(void)
{
    file_load_com(&scene_texture_data_resource);
}

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void flag_object_for_removal(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
