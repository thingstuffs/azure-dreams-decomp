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

/* Initializes an effect state, spawns its objects, and updates its color and position each tick. */
void func_80023EB0(void *state_ptr)
{
    static void *const sw_keep[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3, &&sw_4
    };
    u8 *state = state_ptr;
    register void *object ASM_REG("$16");
    void *object_part;
    register u8 *object_work ASM_REG("$2");
    u8 *object_resource;
    u8 *part_resource;
    s32 initial_scale;
    s32 variant_index;
    s32 position_offset;
    s32 effect_mask_index;
    s32 part_color;
    register s32 object_index ASM_REG("$17");
    u16 animation_counter;

    switch (S16_AT(state, 0x18)) {
    case 0:
        S16_AT(state, 0xC) = 0x410;
        S16_AT(state, 4) = 0x340;
        S16_AT(state, 0xE) = 0x348;
        S16_AT(state, 6) = 0x348;
        S16_AT(state, 0x10) = -0x60;
        S16_AT(state, 8) = -0x60;

        variant_index = S16_AT(state, 0x22);
        if ((u32)variant_index >= 5) {
            goto init_done;
        }
        (void)sw_keep;
        goto *D_80020284[variant_index];

sw_0:
        position_offset = -0x60;
        goto store_both;
sw_1:
        position_offset = -0x98;
        goto store_both;
sw_2:
        position_offset = -0x30;
store_both:
        S16_AT(state, 0x1E) = position_offset;
        S16_AT(state, 0x1C) = position_offset;
        goto init_done;
sw_3:
        position_offset = -0xB0;
        S16_AT(state, 0x1C) = position_offset;
        position_offset = -0x10;
        goto store_second;
sw_4:
        position_offset = -0x10;
        S16_AT(state, 0x1C) = position_offset;
        position_offset = -0xB0;
store_second:
        S16_AT(state, 0x1E) = position_offset;

init_done:
        object_index = 1;
        object_resource = D_80024334;
        initial_scale = 0x800;
        part_resource = D_800F8E9C;
alloc_loop:
        object = func_8003FC64(0x136);
        if (object != 0) {
            PTR_AT(object, 0x10) = object_resource;
            func_8004491C(object, D_80045340);
            object_part = PTR_AT(object, 0xC);
            S16_AT(object_part, 0x14) = 0xC;
            part_color = 0x00808080;
            ASM_SCHED_BARRIER();
            object_work = (u8 *)object + 0x20;
            ASM_KEEP(object_work);
            S16_AT(object_part, 0x1E) = initial_scale;
            S16_AT(object_part, 0x1C) = initial_scale;
            PTR_AT(object_part, 8) = part_resource;
            U8_AT(object_part, 4) = 0;
            U8_AT(object_part, 5) = 0;
            S32_AT(object_part, 0xC) = part_color;
            PTR_AT(object, 0x20) = state;
            S16_AT(object_work, 8) = object_index;
        }
        object_index--;
        if (object_index >= 0) {
            goto alloc_loop;
        }
        S16_AT(state, 0x18) = 1;
        break;

    case 1:
        break;

    default:
        goto done;
    }

    animation_counter = U16_AT(state, 0x1A) + 1;
    U16_AT(state, 0x1A) = animation_counter;
    if (((animation_counter >> 2) & 1) != 0) {
        effect_mask_index = S16_AT(state, 0x22);
        if ((U16_AT(PTR_AT(state, 0), 0x62) & D_80024500[effect_mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
            goto color_done;
        }
    }
    S32_AT(state, 0x14) = 0x00FFFFFF;

color_done:
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 x_delta = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 y_delta = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + x_delta;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + y_delta;
        U16_AT(state, 0x24) &= ~1;
        goto done;
    }

    {
        s32 x_delta = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 y_delta = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 next_y;
        s32 y_distance;

        S16_AT(state, 8) = U16_AT(state, 8) + x_delta;
        next_y = U16_AT(state, 0x10) + y_delta;
        S16_AT(state, 0x10) = next_y;
        ASM_SCHED_BARRIER();
        y_distance = (s16)next_y + 0x60;
        if (y_distance < 0) {
            y_distance = -y_distance;
        }
        if (y_distance < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

done:
    return;
}
