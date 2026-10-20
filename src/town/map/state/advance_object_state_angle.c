#include "common.h"

extern void clear_object_link_and_mark_complete(s32, s32);

/* Update the object and advance its state angle by 0x20 modulo 0x1000. */
void advance_object_state_angle(s32 object, s32 context, void *state) {
    u16 *angle = (u16 *)((u8 *)state + 0x1A);
    s32 t;
    clear_object_link_and_mark_complete(object, context);
    *angle += 0x20;
    t = *angle;
    *angle = t & 0xFFF;
}
