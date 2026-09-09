#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern GlobalFlags D_800814A0;

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Advances the effect state and frame coordinates, setting flags when its timer expires. */
void func_80024B60(void *effect)
{
    s32 state;
    u16 timer;
    u16 counter;
    void *object;

    object = *(void **)effect;
    S32_AT(object, 0x10) |= 0x8000;

    state = S16_AT(effect, 0x4C);
    timer = U16_AT(effect, 0x4E) + 1;
    U16_AT(effect, 0x4E) = timer;

    if (state == 1) {
        goto update_counter;
    }
    if (state >= 2) {
        goto check_final_state;
    }
    if (state == 0) {
        goto initialize;
    }
    goto update_position;

check_final_state:
    if (state == 2) {
        goto check_completion;
    }
    goto update_position;

initialize:
    U16_AT(effect, 0x4E) = 0;
    U16_AT(effect, 0x48) = 0;
    S16_AT(effect, 0x46) = 0x1F;
    S16_AT(effect, 0x44) = 0x1F;
    U16_AT(effect, 0x4C)++;

update_counter:
    counter = U16_AT(effect, 0x48) + 1;
    U16_AT(effect, 0x48) = counter;
    S16_AT(effect, 0x4A) = (s16)counter * 0x30;

    if (S16_AT(effect, 0x48) >= 4) {
        U16_AT(effect, 0x4C)++;
        goto update_position;
    }
    goto update_position;

check_completion:
    if ((s16)timer >= 0xF) {
        U16_AT(effect, -2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

update_position:
    S16_AT(effect, 0x40) = ((U16_AT(effect, 0x4E) & 3) << 5) + 0x80;
    S16_AT(effect, 0x42) = ((s16)U16_AT(effect, 0x4E) >> 2) << 5;
}
