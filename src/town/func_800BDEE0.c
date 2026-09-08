#include "common.h"

extern void func_800BB508(s32, s32);

/* Update the object and advance its state angle by 0x20 modulo 0x1000. */
void func_800BB640(s32 object, s32 context, void *state) {
    volatile u16 *angle = (volatile u16 *)((u8 *)state + 0x1A);

    func_800BB508(object, context);
    *angle = (u16)(*angle + 0x20);
    *angle = (u16)(*angle & 0xFFF);
}
