/* Relinked copy of dungeon/func_80D65810 (func_80D65810.c); retail differs only at relocation sites. */
#include "shared/object_node.h"
#include "common.h"



typedef struct S_80D65810_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x1C];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} S_80D65810_0;

typedef struct S_80D65810_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65810_1;

typedef struct S_80D65810_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80D65810_2;

typedef struct S_80D65810_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65810_3;

typedef struct S_80D65810_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65810_4;   /* input in create_baloon_puff_effect_slot_b */

typedef struct S_80D65810_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80D65810_5;


s32 func_8003DB94();
s32 register_node();
s32 rand();
extern u8 D_800DE870[];
extern void project_sprite_chain(void);
extern void func_80152D34(void);

/* Creates an effect relative to the origin and initializes its motion and appearance. */
void create_baloon_puff_effect_slot_b(s32 unused_0, void *origin_ptr_in, s32 unused_2, u16 offset_x, s16 offset_y, s16 offset_z) {
    void *origin_ptr;
    u16 render_flags;
    S_80D65810_4 *origin;
    u16 x;
    s16 y;
    s16 z;
    s32 size;
    S_80D65810_2 *render;
    S_80D65810_5 *sprite;
    S_80D65810_0 *motion;
    S_80D65810_3 *position;
    void *effect;
    origin_ptr = origin_ptr_in;

    origin = origin_ptr;
    x = offset_x;
    y = offset_y;
    z = offset_z;
    effect = func_8003FC64(0x212);
    if (effect != 0) {
        motion = effect + 0x20;
        motion->unk_0C = 0x1E;
        motion->unk_0E = 0x1E;
        ((S_80D65810_1 *)effect)->unk_10 = func_80152D34;
        register_node(effect, project_sprite_chain);
        render = ((S_80D65810_1 *)effect)->unk_0C;
        render->unk_14 |= 0xC;
        size = 0x60;
        render->unk_10 = size;
        render->unk_06 = 0;
        render_flags = render->unk_14;
        render->unk_14 = (u16)(render_flags | 2);
        position = ((S_80D65810_1 *)effect)->unk_08;
        position->unk_00.at02.v = x;
        position->unk_04.at02.v = (u16)y;
        position->unk_0A = (u16)z;
        motion->unk_34 = 0x40000;
        motion->unk_40 = 0x8000;
        motion->unk_2C = (s32)((s32)position->unk_00.at00.v >> 1);
        motion->unk_30 = (s32)((s32)position->unk_04.at00.v >> 1);
        if (motion->unk_2C == 0) {
            motion->unk_2C = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
            motion->unk_30 = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
        }
        motion->unk_38 = (s32)(0 - ((s32)motion->unk_2C >> 4));
        motion->unk_3C = (s32)(0 - ((s32)motion->unk_30 >> 4));
        position->unk_00.at02.v = (u16)(position->unk_00.at02.v + origin->unk_02);
        position->unk_04.at02.v = (u16)(position->unk_04.at02.v + origin->unk_06);
        position->unk_0A = (u16)(position->unk_0A + origin->unk_0A);
        sprite = ((S_80D65810_1 *)effect)->unk_0C;
        sprite->unk_1C = 0xC00;
        sprite->unk_1E = 0xC00;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        sprite->unk_12 = 0x7DCF;
        sprite->unk_14 = (u16)(sprite->unk_14 | 0x100);
        func_8003DB94(sprite, D_800DE870, 0);
    }
}

/* MECHANISM: Inherited pins preserve the retail 0x30 frame and s4/s5 argument holds.
   Splitting the flags RMW around ASM_SCHED_BARRIER makes its sh precede the reused-value copy.
   Guarded s0/s1 pins restore the held object/subobject bases perturbed by that zero-word fence. */
