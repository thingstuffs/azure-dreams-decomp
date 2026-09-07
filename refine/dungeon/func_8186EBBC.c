#include "common.h"

extern s32 rand(void);
extern s16 func_800BCB04(s32, s32, s32);
extern s16 D_80025308;
extern s32 D_800814A0[];

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        s32 unk8;
        struct {
            u16 unk8_lo;
            u16 unkA;
        } half;
    } value;
} UnkArg1;

/* Raise the position toward the queried height and set flags when the countdown expires. */
void func_8186EBBC(u8 *state, UnkArg1 *position)
{
    u16 countdown;

    D_80025308 = 1;
    if ((s16)position->value.half.unkA <
        func_800BCB04(position->unk2, position->unk6,
                      (s16)(position->value.half.unkA + 2))) {
        position->value.unk8 += 0x20000 + (rand() & 0xFFF);
    }

    countdown = *(u16 *)(state + 0x32) - 8;
    *(u16 *)(state + 0x32) = countdown;
    if ((s32)(countdown << 16) <= 0) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
