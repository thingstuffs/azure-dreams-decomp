#include "common.h"

extern s32 func_80064584(s32);
extern void func_800478B8(void *);
extern s16 D_80083228;
extern s32 D_800814A0[];

/* Update the derived angle and offset, then propagate status flags. */
void func_800244A4(void *angle_source, void *offset_state, void *angle_state)
{
    *(s16 *)((u8 *)angle_state + 0x1A) =
        (s16)((s32)(-((func_80064584(*(s16 *)((u8 *)angle_source + 8) - D_80083228) >> 4) << 8)) >> 8);
    *(u16 *)((u8 *)offset_state + 0xA) = *(u16 *)((u8 *)offset_state + 0xA) - 8;
    func_800478B8(angle_state);
    if (*(u16 *)((u8 *)angle_state + 0x14) & 0x6000) {
        *(u16 *)((u8 *)angle_source - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
