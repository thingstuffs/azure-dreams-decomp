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

/* Initialize two child objects, blink their color, and ease their positions toward active or resting targets. */
void func_80023EB0(void *state_ptr)
{
    static void *const kind_labels[] = {
        &&sw_0, &&sw_1, &&sw_2, &&sw_3, &&sw_4
    };
    u8 *state = state_ptr;
    register void *child_obj ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *render_part;
    register u8 *child_state ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    u8 *object_data;
    u8 *part_data;
    s32 scale;
    s32 kind;
    s32 target_pos;
    s32 mask_index;
    s32 color;
    register s32 child_index ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
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
        if ((u32)kind >= 5) {
            goto init_done;
        }
        (void)kind_labels;
        goto *D_80020284[kind];

sw_0:
        target_pos = -0x60;
        goto store_both;
sw_1:
        target_pos = -0x98;
        goto store_both;
sw_2:
        target_pos = -0x30;
store_both:
        S16_AT(state, 0x1E) = target_pos;
        S16_AT(state, 0x1C) = target_pos;
        goto init_done;
sw_3:
        target_pos = -0xB0;
        S16_AT(state, 0x1C) = target_pos;
        target_pos = -0x10;
        goto store_second;
sw_4:
        target_pos = -0x10;
        S16_AT(state, 0x1C) = target_pos;
        target_pos = -0xB0;
store_second:
        S16_AT(state, 0x1E) = target_pos;

init_done:
        child_index = 1;
        object_data = D_80024334;
        scale = 0x800;
        part_data = D_800F8E9C;
alloc_loop:
        child_obj = func_8003FC64(0x136);
        if (child_obj != 0) {
            PTR_AT(child_obj, 0x10) = object_data;
            func_8004491C(child_obj, D_80045340);
            render_part = PTR_AT(child_obj, 0xC);
            S16_AT(render_part, 0x14) = 0xC;
            color = 0x00808080;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            child_state = (u8 *)child_obj + 0x20;
            ASM_KEEP(child_state);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
            S16_AT(render_part, 0x1E) = scale;
            S16_AT(render_part, 0x1C) = scale;
            PTR_AT(render_part, 8) = part_data;
            U8_AT(render_part, 4) = 0;
            U8_AT(render_part, 5) = 0;
            S32_AT(render_part, 0xC) = color;
            PTR_AT(child_obj, 0x20) = state;
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

    blink_ticks = U16_AT(state, 0x1A) + 1;
    U16_AT(state, 0x1A) = blink_ticks;
    if (((blink_ticks >> 2) & 1) != 0) {
        mask_index = S16_AT(state, 0x22);
        if ((U16_AT(PTR_AT(state, 0), 0x62) & D_80024500[mask_index]) != 0) {
            S32_AT(state, 0x14) = 0;
            goto color_done;
        }
    }
    S32_AT(state, 0x14) = 0x00FFFFFF;

color_done:
    if (U16_AT(PTR_AT(state, 0), 0x64) >= U16_AT(state, 0x20)) {
        s32 first_step = (S16_AT(state, 0x1C) - S16_AT(state, 8)) >> 1;
        s32 second_step = (S16_AT(state, 0x1E) - S16_AT(state, 0x10)) >> 1;

        S16_AT(state, 8) = U16_AT(state, 8) + first_step;
        S16_AT(state, 0x10) = U16_AT(state, 0x10) + second_step;
        U16_AT(state, 0x24) &= ~1;
        goto done;
    }

    {
        s32 first_step = (-0x60 - S16_AT(state, 8)) >> 1;
        s32 second_step = (-0x60 - S16_AT(state, 0x10)) >> 1;
        s32 second_pos;
        s32 rest_distance;

        S16_AT(state, 8) = U16_AT(state, 8) + first_step;
        second_pos = U16_AT(state, 0x10) + second_step;
        S16_AT(state, 0x10) = second_pos;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        rest_distance = (s16)second_pos + 0x60;
        if (rest_distance < 0) {
            rest_distance = -rest_distance;
        }
        if (rest_distance < 2) {
            U16_AT(state, 0x24) |= 1;
        }
    }

done:
    return;
}

