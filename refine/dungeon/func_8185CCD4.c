#include "common.h"

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);
extern s16 D_80083160[];
extern u8 D_800DEAE0[];

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Advance an expanding spiral effect and update its sprite. */
void func_8185CCD4(void *state, void *position, void *sprite)
{
    s16 angle;
    s16 *angle_table;
    void *owner;

    owner = *(void **)state;
    U16_AT(owner, 0x14) = U16_AT(owner, 0x14) + 1;
    S32_AT(sprite, 0xC) = S32_AT(sprite, 0xC) + 0xFFF7F7F8;

    angle = U16_AT(state, 0x1C) + U16_AT(state, 0x1E);
    angle_table = D_80083160;
    U16_AT(state, 0x1C) = angle;
    U16_AT(state, 0x1C) = angle % 0x1000;
    U16_AT(state, 0x20) = U16_AT(state, 0x20) + 4;

    S16_AT(position, 2) = U16_AT(state, 6) +
        (((func_800644B8(S16_AT(state, 0x1C)) >> 4) *
          S16_AT(state, 0x20)) >> 8);
    S16_AT(position, 6) = U16_AT(state, 0xA) +
        (((func_80064584(S16_AT(state, 0x1C)) >> 4) *
          S16_AT(state, 0x20)) >> 8);
    S16_AT(sprite, 0x1A) =
        (s32)(0 - ((func_80064584(S16_AT(state, 0x1C) - angle_table[100]) >> 4) << 8)) >> 8;

    func_800478B8(sprite);
    if (U16_AT(sprite, 0x14) & 0x6000) {
        func_8003DB94(sprite, D_800DEAE0, 0);
    }
}
