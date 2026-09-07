#include "common.h"

extern s16 func_800BCB04(u16, u16, s16);
extern s16 D_8002694C;
extern s32 D_800814A0[3];

/* Conditionally advances the position and decrements a counter, setting flags when it expires. */
void func_8187B7F0(void *object, s16 *position)
{
    s16 *object_fields = object;
    s16 counter;

    D_8002694C = 1;
    if (position[5] < func_800BCB04((s16)position[1], (u16)position[3], position[5] + 2)) {
        ((s32 *)position)[2] += *(s32 *)((u8 *)object + 0xB4);
    }

    counter = (u16)object_fields[8] - 4;
    object_fields[8] = counter;
    if ((counter << 16) <= 0) {
        ((u16 *)object_fields)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
