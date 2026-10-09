#include "common.h"
#include "shared/object_flags.h"

extern s32 rand(void);
#include "modules/dungeon_native_abi.h"
extern s16 D_80025630;

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
} EffectPosition;

/* Raise the position toward the queried height and set flags when the countdown expires. */
void func_800243A4(u8 *state, EffectPosition *position)
{
    u16 countdown;

    D_80025630 = 1;
    if ((s16)position->value.half.unkA <
        (s16)func_800BCB04(position->unk2, position->unk6,
                      (s16)(position->value.half.unkA + 2))) {
        position->value.unk8 += 0x20000 + (rand() & 0xFFF);
    }

    countdown = *(u16 *)(state + 0x32) - 8;
    *(u16 *)(state + 0x32) = countdown;
    if ((s32)(countdown << 16) <= 0) {
        *(u16 *)(state - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
