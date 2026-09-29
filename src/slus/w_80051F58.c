#include "common.h"

#include "common.h"

typedef struct S_80051F58_ptr {
    u8 pad00[6];
    u16 unk06;
    u8 pad08[0x10];
    s32 unk18;
} S_80051F58_ptr;

typedef struct S_80051F58 {
    S_80051F58_ptr *unk00;
    s16 state;
    u16 timer;
    u8 pad08[4];
    s16 unk0C;
} S_80051F58;

typedef struct S_80051F58_a2 {
    u8 pad00[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
} S_80051F58_a2;

extern s32 D_800814A0_abs __attribute__((section(".data")));
__asm__(".set D_800814A0_abs, 0x800814A0");

/* Fade the color in, hold it, then fade it out and mark the effect complete. */
void func_80051F58(S_80051F58 *effect, void *unused_1, S_80051F58_a2 *color, void *unused_3)
{
    u16 timer = effect->timer;
    u16 advance_state;
    int next_timer;
    int state = effect->state;
    u16 state_bits = effect->state;

    next_timer = timer + 1;
    effect->timer = next_timer;
    switch (state) {
    case 0:
        if (effect->unk0C == 0) {
            return;
        }
        effect->unk0C = 0;
        advance_state = effect->state;
        effect->timer = 0;
        effect->state = advance_state + 1;
        return;
    case 1:
    {
        u8 intensity = color->unk0E + 2;
        color->unk0E = intensity;
        color->unk0D = intensity;
        color->unk0C = intensity;
    }
        if ((s16)effect->timer < 0x40) {
            return;
        }
        advance_state = effect->state;
        effect->timer = 0;
        effect->state = advance_state + 1;
        return;
    case 2:
        if ((s16)next_timer < 0x100) {
            return;
        }
        {
            u16 next_state = state_bits + 1;
            effect->state = next_state;
        }
        effect->timer = 0;
        return;
    case 3:
    {
        u8 intensity = color->unk0E - 2;
        color->unk0E = intensity;
        color->unk0D = intensity;
        color->unk0C = intensity;
    }
        if ((s16)effect->timer < 0x40) {
            return;
        }
        break;
    default:
        color->unk0E = 0;
        color->unk0D = 0;
        color->unk0C = 0;
        break;
    }
    effect->unk00->unk18 = 0;
    effect->unk00->unk06 += 1;
    *((u16 *)effect - 1) |= 0x8000;
    D_800814A0_abs |= 0x8000;
}
