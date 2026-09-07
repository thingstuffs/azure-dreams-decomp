#include "common.h"

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);

extern void *D_80020284[5];
extern u8 D_80024334[16];
extern u16 D_80024500[8];
extern u8 D_80045340[];
extern u8 D_800F8E9C[16];

// Initializes and updates a blinking two-part effect that eases between hidden and type-specific positions.
void func_80023EB0(void *effect_state)
{
    static void *const sw_keep[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3, &&sw_4
    };
    u8 *state = effect_state;
    register void *child ASM_REG("$16");
    void *child_part;
    register u8 *child_state ASM_REG("$2");
    u8 *child_object_data;
    u8 *child_part_data;
    s32 child_scale;
    s32 effect_kind;
    s32 target_position;
    s32 effect_mask_index;
    s32 child_color;
    register s32 child_index ASM_REG("$17");
    u16 blink_counter;

    switch (S16_AT(state, 0x18)) {
    case 0:
        S16_AT(state, 0xC) = 0x410;
        S16_AT(state, 4) = 0x340;
        S16_AT(state, 0xE) = 0x348;
        S16_AT(state, 6) = 0x348;
        S16_AT(state, 0x10) = -0x60;
        S16_AT(state, 8) = -0x60;

        effect_kind = S16_AT(state, 0x22);
        if ((u32)effect_kind >= 5) {
            goto init_done;
        }
        (void)sw_keep;
        goto *D_80020284[effect_kind];

sw_0:
        target_position = -0x60;
        goto store_both;
sw_1:
        target_position = -0x98;
        goto store_both;
sw_2:
        target_position = -0x30;
store_both:
        S16_AT(state, 0x1E) = target_position;
        S16_AT(state, 0x1C) = target_position;
        goto init_done;
sw_3:
        target_position = -0xB0;
        S16_AT(state, 0x1C) = target_position;
        target_position = -0x10;
        goto store_second;
sw_4:
        target_position = -0x10;
        S16_AT(state, 0x1C) = target_position;
        target_position = -0xB0;
store_second:
        S16_AT(state, 0x1E) = target_position;

init_done:
        child_index = 1;
        child_object_data = D_80024334;
        child_scale = 0x800;
        child_part_data = D_800F8E9C;
alloc_loop:
        child = func_8003FC64(0x136);
        if (child != 0) {
            PTR_AT(child, 0x10) = child_object_data;
            func_8004491C(child, D_80045340);
            child_part = PTR_AT(child, 0xC);
            S16_AT(child_part, 0x14) = 0xC;
            child_color = 0x00808080;
            ASM_SCHED_BARRIER();
            child_state = (u8 *)child + 0x20;
            ASM_KEEP(child_state);
            S16_AT(child_part, 0x1E) = child_scale;
            S16_AT(child_part, 0x1C) = child_scale;
            PTR_AT(child_part, 8) = child_part_data;
            U8_AT(child_part, 4) = 0;
            U8_AT(child_part, 5) = 0;
            S32_AT(child_part, 0xC) = child_color;
            PTR_AT(child, 0x20) = state;
            S16_AT(child_state, 8) = child_index;
        }
        child_index--;
        if (child_index >= 0) {
            goto alloc_loop;
        }
        S16_AT(state, 0x18) = 1;
        break;

    case 1:
        break;

    default:
        goto done;
    }

    blink_counter = U16_AT(state, 0x1A) + 1;
    U16_AT(state, 0x1A) = blink_counter;
    if (((blink_counter >> 2) & 1) != 0) {
        effect_mask_index = S16_AT(state, 0x22);
        if ((U16_AT(PTR_AT(state, 0), 0x62) & D_80024500[effect_mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
            goto color_done;
        }
    }
    S32_AT(state, 0x14) = 0x00FFFFFF;

color_done:
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 x_step = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 y_step = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + x_step;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + y_step;
        U16_AT(state, 0x24) &= ~1;
        goto done;
    }

    {
        s32 x_step = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 y_step = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 y_position;
        s32 distance_from_hidden;

        S16_AT(state, 8) = U16_AT(state, 8) + x_step;
        y_position = U16_AT(state, 0x10) + y_step;
        S16_AT(state, 0x10) = y_position;
        ASM_SCHED_BARRIER();
        distance_from_hidden = (s16)y_position + 0x60;
        if (distance_from_hidden < 0) {
            distance_from_hidden = -distance_from_hidden;
        }
        if (distance_from_hidden < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

done:
    return;
}
