#include "common.h"
#include "shared/entity_objects.h"
#include "shared/object_flags.h"

extern s32 D_800834B8[2];
extern s32 D_80097D2C;
extern s32 D_80097EA0;
extern s32 D_800D0428;

extern void unlink_node_if_registered(void *object);

/* Copy the adjusted vector when state references match; otherwise process and flag the object. */
void copy_adjusted_vector_or_flag_object(void *object, s32 *out_vector)
{
    s32 *state_refs = D_800834B8;

    if ((state_refs[0] != (s32)&D_80097D2C) ||
        (state_refs[1] != (s32)&D_80097EA0)) {
        unlink_node_if_registered(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    out_vector[0] = D_80083780.x.v;
    out_vector[1] = D_80083780.y.v;
    out_vector[2] = D_80083780.z.v + D_800D0428;
}
