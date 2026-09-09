#include "common.h"

typedef struct GlobalState {
    s32 pad0;
    u16 flags;
    u8 pad6[6];
} GlobalState;

extern GlobalState D_80083160;
extern s32 D_800814A0[3];

extern s32 func_800644B8(s32);

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Fades and pulses the effect, restoring the linked primitive when the fade ends. */
void func_800A5828(void *effect, s32 unused, void *render_state)
{
    s32 fade_step;
    s32 brightness;
    s32 pulse_scale;
    s16 current_brightness;
    u16 tilt;
    void *linked_prim;
    GlobalState *global_state = &D_80083160;

    if (S16_AT(effect, 0x64) == 0) {
        if (global_state->flags & 1) {
            brightness = (s16)U16_AT(effect, 0x6A) >> 1;
        } else {
            current_brightness = U16_AT(effect, 0x6A);
            U16_AT(effect, 0x6A) =
                U16_AT(effect, 0x6A) + (192 - current_brightness) / S16_AT(effect, 0x66);
            brightness = U8_AT(effect, 0x6A);
        }
        U8_AT(render_state, 0xE) = brightness;
        U8_AT(render_state, 0xD) = brightness;
        U8_AT(render_state, 0xC) = brightness;

        U16_AT(effect, 0x66)--;
        if (S16_AT(effect, 0x66) <= 0) {
            U16_AT(effect, 0x66) = 16;
            U16_AT(effect, 0x64)++;
        }
    } else {
        if (global_state->flags & 1) {
            S32_AT(render_state, 0xC) = 0;
        } else {
            fade_step = S16_AT(effect, 0x6A) / S16_AT(effect, 0x66);
            U16_AT(effect, 0x6A) -= fade_step;
            brightness = U8_AT(effect, 0x6A);
            U8_AT(render_state, 0xE) = brightness;
            U8_AT(render_state, 0xD) = brightness;
            U8_AT(render_state, 0xC) = brightness;
        }

        U16_AT(effect, 0x66)--;
        if (S16_AT(effect, 0x66) <= 0) {
            linked_prim = *(void **)((u8 *)(*(void **)((u8 *)effect + 4)) - 0x14);
            U8_AT(linked_prim, 0xC) = 0x80;
            U8_AT(linked_prim, 0xD) = 0x80;
            U8_AT(linked_prim, 0xE) = 0x80;
            U16_AT(effect, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            return;
        }
    }

    U16_AT(effect, 0x68)++;
    pulse_scale = (func_800644B8((s16)U16_AT(effect, 0x68) << 9) >> 4) + 0x1000;
    S16_AT(render_state, 0x1C) = pulse_scale;
    S16_AT(render_state, 0x1E) = pulse_scale;

    tilt = 0xFFC0;
    if (U16_AT(effect, 0x68) & 1) {
        tilt = 64;
    }
    S16_AT(render_state, 0x1A) = tilt;

    brightness = ((U16_AT(effect, 0x68) & 3) << 4) + 64;
    linked_prim = *(void **)((u8 *)(*(void **)((u8 *)effect + 4)) - 0x14);
    U8_AT(linked_prim, 0xC) = brightness;
    U8_AT(linked_prim, 0xD) = brightness;
    U8_AT(linked_prim, 0xE) = brightness;
}
