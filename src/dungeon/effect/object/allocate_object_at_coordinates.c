#include "shared/object_node.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect.h"
#include "dungeon/effect/object.h"

typedef s32 M2C_UNK;

typedef struct S_800B7B60_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B7B60_0;

typedef struct S_800B7B60_1_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800B7B60_1_pre;   /* the 0x18 bytes before arg0 in allocate_object_at_coordinates, addressed as arg0[-1] */

#ifndef NULL
#define NULL 0
#endif


extern void D_800B7774();

/* Allocates an object, copies the source coordinates, and increments the object counter. */
void *allocate_object_at_coordinates(void *source, s32 *init_value) {
    u16 coord_z;
    MovingPosition *src_coords;
    S_800B7B60_0 *object;
    MovingPosition *dst_coords;

    object = allocate_flagged_object_node(0x12);
    if (object != NULL) {
        object->unk_10 = &D_800B7774;
        object->unk_20 = *init_value;
        src_coords = ((S_800B7B60_1_pre *)source)[-1].unk_00;
        dst_coords = object->unk_08;
        dst_coords->x = src_coords->x;
        dst_coords->y = src_coords->y;
        coord_z = src_coords->z;
        dst_coords->z = coord_z;
        spawn_directed_and_scattered_particles((s16) dst_coords->x, (s16) dst_coords->y, (s16) coord_z);
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
    return object;
}
