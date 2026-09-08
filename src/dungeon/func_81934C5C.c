#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_81934C5C_0_pre {
    u16 unk_00;
} S_81934C5C_0_pre;   /* the 0x2 bytes before arg0 in func_81934C5C, addressed as arg0[-1] */

typedef struct S_81934C5C_0 {
    void * unk_00;
    u8 pad_04[0x8];
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u8 pad_12[0xA];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_28;   /* overlapping accesses */
    u8 pad_2C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_30;   /* overlapping accesses */
    u8 pad_34[0x14];
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_81934C5C_0;   /* arg0 in func_81934C5C */

typedef struct S_81934C5C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_81934C5C_1;   /* temp_v1 in func_81934C5C */

typedef struct S_81934C5C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934C5C_2;   /* temp_v0_3 in func_81934C5C */

typedef struct S_81934C5C_3 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81934C5C_3;   /* temp_s1 in func_81934C5C */

typedef struct S_81934C5C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81934C5C_4;   /* temp_spawn_base in func_81934C5C */

typedef struct S_81934C5C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81934C5C_5;   /* ((S_81934C5C_2 *)temp_v0_3)->unk_08 in func_81934C5C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80024678() __attribute__((noreturn));
void func_8002468C() __attribute__((noreturn));
void func_80024724() __attribute__((noreturn));
void *func_8003FD64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
s16 func_800BCB04();
extern M2C_UNK D_80024928;
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;

/* Updates effect motion and spawns an impact effect on reaching the surface. */
void func_81934C5C(void *effect) {
    s32 ticks_left;
    s32 surface_height;
    s16 state;
    s32 height_work;
    s32 height_velocity;
    s32 x_fixed;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    s32 x_velocity;
    s32 world_y;
    s32 world_x;
    s32 x_step;
    s32 x_step_tripled;
    s32 height_step_tripled;
    s32 display_y_step;
    s32 display_y;
    s32 next_display_y;
    u16 final_display_y;
    S_81934C5C_3 *impact_sprite;
    S_81934C5C_2 *impact_effect;
    S_81934C5C_1 *owner;

    owner = ((S_81934C5C_0 *)effect)->unk_00;
    ((S_81934C5C_0 *)effect)->unk_48.s = (u16) (((S_81934C5C_0 *)effect)->unk_48.s - 1);
    owner->unk_0E = (u16) (owner->unk_0E | 0x8000);
    state = ((S_81934C5C_0 *)effect)->unk_4C;
    if (state == 2) {
        goto block_state2;
    }
    if (state < 3) {
        if (state == 0) {
            goto block_state0;
        }
        if (state == 1) {
            goto block_state1;
        }
        func_80024724();
        return;
    }
    if (state == 3) {
        goto block_state3;
    }
    if (state == 0xFF) {
        goto block_state_ff;
    }
    func_80024724();
    return;

block_state0:
    ((S_81934C5C_0 *)effect)->unk_48.s = 3U;
    ((S_81934C5C_0 *)effect)->unk_28.at02.v = -4;
    ((S_81934C5C_0 *)effect)->unk_30.at02.v = 0x10;
    ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);

block_state1:
    ((S_81934C5C_0 *)effect)->unk_1C.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_1C.at00.v + ((S_81934C5C_0 *)effect)->unk_28.at00.v);
    ticks_left = ((S_81934C5C_0 *)effect)->unk_48.u;
    ((S_81934C5C_0 *)effect)->unk_24.at00.v = (s32) (((S_81934C5C_0 *)effect)->unk_24.at00.v + ((S_81934C5C_0 *)effect)->unk_30.at00.v);
    if (ticks_left <= 0) {
        func_8002468C(ticks_left);
        return;
    }
    goto block_return;

block_state2:
    x_fixed = ((S_81934C5C_0 *)effect)->unk_1C.at00.v;
    x_velocity = ((S_81934C5C_0 *)effect)->unk_28.at00.v;
    world_y = ((S_81934C5C_0 *)effect)->unk_20.at02.v;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    height_work = ((S_81934C5C_0 *)effect)->unk_30.at02.v;
    height_velocity = ((S_81934C5C_0 *)effect)->unk_30.at00.v;
    ((S_81934C5C_0 *)effect)->unk_1C.at00.v = x_fixed + x_velocity;
    ASM_CLOBBER("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    x_step = ((S_81934C5C_0 *)effect)->unk_28.at02.v;
    world_x = ((S_81934C5C_0 *)effect)->unk_1C.at02.v;
    x_step_tripled = x_step * 3;
    ASM_KEEP(x_step);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ((S_81934C5C_0 *)effect)->unk_0C = (u16) (((S_81934C5C_0 *)effect)->unk_0C + (x_step_tripled >> 2));
    height_step_tripled = height_work * 3;
    display_y_step = height_step_tripled >> 2;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    display_y = ((S_81934C5C_0 *)effect)->unk_10;
    do {
        height_work = ((S_81934C5C_0 *)effect)->unk_24.at00.v;
    } while (0);
    next_display_y = display_y + display_y_step;
    height_work += height_velocity;
    ((S_81934C5C_0 *)effect)->unk_24.at00.v = height_work;
    ((S_81934C5C_0 *)effect)->unk_10 = next_display_y;
    surface_height = func_800BCB04(world_x, world_y, -0x400, height_velocity);
    if (surface_height >= 0x201) {
        if (((S_81934C5C_0 *)effect)->unk_24.at02.v > 0) {
            goto block_tail_ff;
        }
    }
    if (surface_height >= ((S_81934C5C_0 *)effect)->unk_24.at02.v) {
        goto block_return;
    }
    ((S_81934C5C_0 *)effect)->unk_24.at02.v = surface_height;
    impact_effect = func_8003FD64(0x312, &D_80083498);
    if (impact_effect != NULL) {
        impact_effect->unk_10 = &D_80024928;
        impact_effect->unk_20 = (void *) ((S_81934C5C_0 *)effect)->unk_00;
        func_8004491C(impact_effect, &D_80045340);
        impact_sprite = impact_effect->unk_0C;
        ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_00 = (s32) ((S_81934C5C_0 *)effect)->unk_1C.at00.v;
        ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_04 = (s32) ((S_81934C5C_0 *)effect)->unk_20.at00.v;
        ((S_81934C5C_5 *)(impact_effect->unk_08))->unk_08 = (s32) ((S_81934C5C_0 *)effect)->unk_24.at00.v;
        impact_sprite->unk_1E = 0x500;
        impact_sprite->unk_1C = 0x500;
        impact_sprite->unk_14 = (u16) (impact_sprite->unk_14 | 0xC);
        if (func_80069EF8() & 1) {
            M2C_UNK *alt_animation = &D_800DEDB0;

            ASM_TAILSLOT_PIN(alt_animation);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80024678();
            return;
        }
        {
            M2C_UNK *animation;

            ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            animation = &D_800DEE38;
            impact_sprite->unk_00 = animation;
            impact_sprite->unk_08 = (s32) ((S_81934C5C_4 *)animation)->unk_04;
            impact_sprite->unk_04 = 0;
            impact_sprite->unk_05 = 0;
        }
    }
    ((S_81934C5C_0 *)effect)->unk_4C = (s16) ((u16) ((S_81934C5C_0 *)effect)->unk_4C + 1);
    func_80024724();
    return;

block_state3:
    ((S_81934C5C_0 *)effect)->unk_0C = (u16) (((S_81934C5C_0 *)effect)->unk_0C + ((s32) (((S_81934C5C_0 *)effect)->unk_28.at02.v * 3) >> 2));
    final_display_y = ((S_81934C5C_0 *)effect)->unk_10 + ((s32) (((S_81934C5C_0 *)effect)->unk_30.at02.v * 3) >> 2);
    ((S_81934C5C_0 *)effect)->unk_10 = final_display_y;
    if (((S_81934C5C_0 *)effect)->unk_24.at02.v < (s16) final_display_y) {
        ((S_81934C5C_0 *)effect)->unk_10 = (u16) ((S_81934C5C_0 *)effect)->unk_24.at02.v;
        goto block_tail_ff;
    }
    goto block_return;

block_tail_ff:
    ((S_81934C5C_0 *)effect)->unk_4C = 0xFF;
    func_80024724();
    return;

block_state_ff:
    ((S_81934C5C_0_pre *)effect)[-1].unk_00 = (u16) (((S_81934C5C_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;

block_return:
    return;
}
