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

/* Initializes two child objects and updates the effect's blinking color and depth offsets. */
void func_80023EB0(void *effect_state)
{
    static void *const variant_labels[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3, &&sw_4
    };
    u8 *state = effect_state;
    register void *child_object ASM_REG("$16");
    void *child_part;
    register u8 *child_state ASM_REG("$2");
    u8 *child_object_data;
    u8 *child_part_data;
    s32 child_scale;
    s32 effect_variant;
    s32 target_depth;
    s32 blink_mask_index;
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

        effect_variant = S16_AT(state, 0x22);
        if ((u32)effect_variant >= 5) {
            goto init_done;
        }
        (void)variant_labels;
        goto *D_80020284[effect_variant];

sw_0:
        target_depth = -0x60;
        goto store_both;
sw_1:
        target_depth = -0x98;
        goto store_both;
sw_2:
        target_depth = -0x30;
store_both:
        S16_AT(state, 0x1E) = target_depth;
        S16_AT(state, 0x1C) = target_depth;
        goto init_done;
sw_3:
        target_depth = -0xB0;
        S16_AT(state, 0x1C) = target_depth;
        target_depth = -0x10;
        goto store_second;
sw_4:
        target_depth = -0x10;
        S16_AT(state, 0x1C) = target_depth;
        target_depth = -0xB0;
store_second:
        S16_AT(state, 0x1E) = target_depth;

init_done:
        child_index = 1;
        child_object_data = D_80024334;
        child_scale = 0x800;
        child_part_data = D_800F8E9C;
alloc_loop:
        child_object = func_8003FC64(0x136);
        if (child_object != 0) {
            PTR_AT(child_object, 0x10) = child_object_data;
            func_8004491C(child_object, D_80045340);
            child_part = PTR_AT(child_object, 0xC);
            S16_AT(child_part, 0x14) = 0xC;
            child_color = 0x00808080;
            ASM_SCHED_BARRIER();
            child_state = (u8 *)child_object + 0x20;
            ASM_KEEP(child_state);
            S16_AT(child_part, 0x1E) = child_scale;
            S16_AT(child_part, 0x1C) = child_scale;
            PTR_AT(child_part, 8) = child_part_data;
            U8_AT(child_part, 4) = 0;
            U8_AT(child_part, 5) = 0;
            S32_AT(child_part, 0xC) = child_color;
            PTR_AT(child_object, 0x20) = state;
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
        blink_mask_index = S16_AT(state, 0x22);
        if ((U16_AT(PTR_AT(state, 0), 0x62) & D_80024500[blink_mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
            goto color_done;
        }
    }
    S32_AT(state, 0x14) = 0x00FFFFFF;

color_done:
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 first_depth_step = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 second_depth_step = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + first_depth_step;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + second_depth_step;
        U16_AT(state, 0x24) &= ~1;
        goto done;
    }

    {
        s32 first_depth_step = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 second_depth_step = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 updated_second_depth;
        s32 rest_depth_distance;

        S16_AT(state, 8) = U16_AT(state, 8) + first_depth_step;
        updated_second_depth = U16_AT(state, 0x10) + second_depth_step;
        S16_AT(state, 0x10) = updated_second_depth;
        ASM_SCHED_BARRIER();
        rest_depth_distance = (s16)updated_second_depth + 0x60;
        if (rest_depth_distance < 0) {
            rest_depth_distance = -rest_depth_distance;
        }
        if (rest_depth_distance < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

done:
    return;
}
