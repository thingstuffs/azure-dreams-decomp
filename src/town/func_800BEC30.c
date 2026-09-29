#include "common.h"
extern u8 D_80080000[];

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define VU16_AT(p, o) (*(volatile u16 *)((u8 *)(p) + (o)))

/* Advance a timed state sequence, decrease its value, and set completion flags. */
void func_800BC390(void *object)
{
    s32 state;
    s32 timer;
    s32 decay_value;
    u16 prior_state;

    state = S16_AT(object, 0);
    timer = U16_AT(object, 2) - 1;
    U16_AT(object, 2) = timer;
    switch (state) {
    case 0:
        if ((timer << 16) > 0) {
            return;
        }
        VU16_AT(object, 2) = 12;
        prior_state = VU16_AT(object, 0);
        state = 3;
        S16_AT(object, 0x14) = state;
        U16_AT(object, 0) = prior_state + 1;
        return;

    case 1:
        decay_value = S32_AT(object, 8);
        if (decay_value > 0) {
            S32_AT(object, 8) = decay_value + (s32)0xFFF7FBFC;
        }
        if (S16_AT(object, 2) > 0) {
            return;
        }
        prior_state = U16_AT(object, 0);
        U16_AT(object, 0) = prior_state + 1;
        return;

    case 2:
        U16_AT(object, -2) = U16_AT(object, -2) | 0x8000;
        S32_AT((void *)D_80080000, 0x14A0) |= 0x8000;
        return;
    }
}
