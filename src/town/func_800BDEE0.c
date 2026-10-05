#include "common.h"

extern void func_800BB508(s32, s32);

/* Update the object and advance its state angle by 0x20 modulo 0x1000. */
void func_800BB640(s32 object, s32 context, void *state) {
    u16 *angle = (u16 *)((u8 *)state + 0x1A);
    s32 t;
    func_800BB508(object, context);
    *angle += 0x20;
    t = *angle;
    *angle = t & 0xFFF;
}
