#include "common.h"
#include "shared/object_flags.h"

typedef struct Obj800A5BC0 {
    u8 pad0[8];
    s16 timer;
    u8 padA[6];
    s32 x;
    s32 dx;
    s32 y;
    s32 dy;
    s16 value;
} Obj800A5BC0;

extern void draw_segmented_menu_ring(s32 center_source, s32 radius_a, s32 radius_b, s16 segment_arg);

/* Advance the object's motion and timer-scaled value, or mark it expired. */
void tick_menu_motion_fade(Obj800A5BC0 *obj, void *ctx)
{
    obj->timer--;
    if (obj->timer < 0) {
        *(u16 *)((u8 *)obj - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    obj->x += obj->dx;
    obj->y += obj->dy;
    obj->dx -= 16;
    obj->value = (obj->timer * 255) / 20;
    draw_segmented_menu_ring(ctx, obj->x, obj->y, obj->value);
}
