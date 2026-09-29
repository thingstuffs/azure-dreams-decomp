#include "common.h"
/* Updates an object's movement, blinking, and removal flags from its animation state. */
void func_80088EDC(void *object, void *motion, void *sprite) {
    void *owner = *(void **)object;
    s16 state;

    if (*(u16 *)((char *)owner + 0x26) & 1)
        *(s16 *)((char *)object + 8) = 255;
    state = *(s16 *)((char *)object + 8);
    switch (state) {
    case 0:
        break;
    case 1:
        {
            u16 ticks_left = *(u16 *)((char *)object + 0xA) - 1;
            *(u16 *)((char *)object + 0xA) = ticks_left;
            if ((s32)(ticks_left << 16) <= 0) {
                *(s32 *)motion = *(s32 *)motion + *(s32 *)((char *)motion + 0xC);
                *(s32 *)((char *)motion + 0xC) = *(s32 *)((char *)motion + 0xC) - 0x10000;
                if (*(s32 *)((char *)motion + 0xC) == 0) {
                    *(u16 *)((char *)object + 0xA) = 4;
                    *(s16 *)((char *)object + 8) = 2;
                }
            }
        }
        break;
    case 2:
        {
            u16 ticks_left;
            *(s16 *)((char *)motion + 2) = *(u16 *)((char *)motion + 2) +
                ((160 - *(s16 *)((char *)motion + 2)) >> 1);
            ticks_left = *(u16 *)((char *)object + 0xA) - 1;
            *(u16 *)((char *)object + 0xA) = ticks_left;
            if ((s32)(ticks_left << 16) <= 0)
                *(s16 *)((char *)object + 8) = 16;
        }
        break;
    case 16:
        *(s16 *)((char *)motion + 2) = 160;
        if (*(s16 *)((char *)owner + 0x20) == 32) {
            if (*(s16 *)((char *)owner + 0x24) == *(s16 *)((char *)object + 0xC))
                *(s16 *)((char *)object + 8) = 32;
            else {
                *(s32 *)((char *)motion + 0xC) = 0xFFF80000;
                *(s16 *)((char *)object + 8) = 33;
            }
        }
        break;
    case 32:
        if ((*(u16 *)((char *)owner + 0x22) >> 3) & 1)
            *(u16 *)((char *)sprite + 0x14) |= 0x80;
        else
            *(u16 *)((char *)sprite + 0x14) &= 0xFF7F;
        break;
    case 33:
        {
            s32 position = *(s32 *)motion;
            if (position <= 0x1FFFFFF) {
                *(s32 *)motion = position + *(s32 *)((char *)motion + 0xC);
                *(s32 *)((char *)motion + 0xC) = *(s32 *)((char *)motion + 0xC) + 0x20000;
            }
        }
        break;
    case 255:
        {
            s32 *flags_base = (s32 *)0x80080000;
            *(u16 *)((char *)object - 2) |= 0x8000;
            flags_base[0x14A0 / 4] |= 0x8000;
        }
        break;
    }
}
