#include "common.h"
#include "shared/slus_callbacks.h"
extern int abs(int);

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern u8 D_80024334[16];
extern u16 D_80024500[8];
extern u8 D_800F8E9C[16];

/* Initialize two child objects, blink their color, and ease their positions toward active or resting targets. */
void func_80023EB0(void *state)
{
    void *child_obj;
    u8 *child_state;
    s32 kind;
    s32 target_pos;
    s32 mask_index;
    s32 color;
    s32 child_index;
    u16 blink_ticks;

    switch (S16_AT(state, 0x18)) {
    case 0:
        S16_AT(state, 0xC) = 0x410;
        S16_AT(state, 4) = 0x340;
        S16_AT(state, 0xE) = 0x348;
        S16_AT(state, 6) = 0x348;
        S16_AT(state, 0x10) = -0x60;
        S16_AT(state, 8) = -0x60;

        kind = S16_AT(state, 0x22);
        switch (kind) {
        case 0:
            target_pos = -0x60;
            goto store_both;
        case 1:
            target_pos = -0x98;
            goto store_both;
        case 2:
            target_pos = -0x30;
store_both:
            S16_AT(state, 0x1E) = target_pos;
            S16_AT(state, 0x1C) = target_pos;
            break;
        case 3:
            target_pos = -0xB0;
            S16_AT(state, 0x1C) = target_pos;
            target_pos = -0x10;
            goto store_second;
        case 4:
            target_pos = -0x10;
            S16_AT(state, 0x1C) = target_pos;
            target_pos = -0xB0;
store_second:
            S16_AT(state, 0x1E) = target_pos;
        }


        child_index = 1;
        do {
            child_obj = func_8003FC64(0x136);
            if (child_obj != 0) {
                child_state = (u8 *)child_obj + 0x20;
                PTR_AT(child_obj, 0x10) = D_80024334;
                func_8004491C(child_obj, func_80045340);
                kind = (s32)PTR_AT(child_obj, 0xC);
                S16_AT(kind, 0x14) = 0xC;
                color = 0x00808080;
                S16_AT(kind, 0x1E) = 0x800;
                S16_AT(kind, 0x1C) = 0x800;
                PTR_AT(kind, 8) = D_800F8E9C;
                U8_AT(kind, 4) = 0;
                U8_AT(kind, 5) = 0;
                S32_AT(kind, 0xC) = color;
                PTR_AT(child_obj, 0x20) = state;
                S16_AT(child_state, 8) = child_index;
            }
            child_index--;
        } while (child_index >= 0);
        S16_AT(state, 0x18) = 1;
        break;

    case 1:
        break;

    default:
        return;
    }

    blink_ticks = U16_AT(state, 0x1A) + 1;
    U16_AT(state, 0x1A) = blink_ticks;
    if (((blink_ticks >> 2) & 1) != 0) {
        mask_index = S16_AT(state, 0x22);
        color = (s32)PTR_AT(state, 0);
        if ((U16_AT(color, 0x62) & D_80024500[mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
        } else {
            S32_AT(state, 0x14) = 0x00FFFFFF;
        }
    } else {
        S32_AT(state, 0x14) = 0x00FFFFFF;
    }
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 first_step = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 second_step = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + first_step;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + second_step;
        U16_AT(state, 0x24) &= ~1;
        return;
    }

    {
        s32 first_step = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 second_step = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 second_pos;
        s32 rest_distance;
        s32 abs_rest_distance;

        S16_AT(state, 8) = U16_AT(state, 8) + first_step;
        second_pos = U16_AT(state, 0x10) + second_step;
        S16_AT(state, 0x10) = second_pos;
        abs_rest_distance = abs((s16)second_pos + 0x60);
        if (abs_rest_distance < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

    return;
}

