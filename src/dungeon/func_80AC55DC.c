#include "common.h"

typedef struct S_80AC55DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80AC55DC_0;   /* node in func_80AC55DC */

typedef struct S_80AC55DC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80AC55DC_1;   /* arg0 in func_80AC55DC */

typedef struct S_80AC55DC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    volatile s32 unk_40;
    volatile s32 unk_44;
    volatile s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC55DC_2;   /* work in func_80AC55DC */

typedef struct S_80AC55DC_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80AC55DC_3;   /* source in func_80AC55DC */

typedef struct S_80AC55DC_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80AC55DC_4;   /* sprite in func_80AC55DC */

typedef struct S_80AC55DC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80AC55DC_5;   /* ((S_80AC55DC_0 *)node)->unk_08 in func_80AC55DC */

typedef struct S_80AC55DC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC55DC_6;   /* ((S_80AC55DC_1 *)arg0)->unk_08 in func_80AC55DC */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80170A84[];

/* Creates a sprite effect offset from its origin and initializes its return motion. */
void func_80AC55DC(
    S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    void *node;
    S_80AC55DC_2 *work;
    S_80AC55DC_4 *sprite;
    S_80AC55DC_3 *origin_pos;
    u16 origin_z;
    u16 sprite_flags;
    s32 sprite_size;
    void *sprite_data;
    s32 duration_shifted;
    s32 offset_fixed;
    s32 duration_signed;
    register s32 duration_eighth ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 step_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 step_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 step_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_80AC55DC_0 *)node)->unk_10 = D_80170A84;

        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_02 =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_02 + offset_x;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_06 =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_06 + offset_y;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_0A =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_0A + offset_z - 0x14;

        work = (u8 *)node + 0x20;
        work->unk_36 = ((S_80AC55DC_6 *)(origin->unk_08))->unk_02;
        work->unk_38 = ((S_80AC55DC_6 *)(origin->unk_08))->unk_06;
        duration_shifted = duration << 16;
        origin_pos = origin->unk_08;
        duration_signed = duration_shifted >> 16;
        origin_z = origin_pos->unk_0A;
        duration_eighth = duration_signed;
        work->unk_3A = origin_z;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        offset_fixed = offset_x << 16;
        offset_fixed = -offset_fixed;
        if (duration_signed < 0) {
            duration_eighth = duration_signed + 7;
        }
        duration_eighth >>= 3;

        step_x = offset_fixed / duration_eighth;
        work->unk_40 = step_x / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        offset_fixed = offset_y << 16;
        offset_fixed = -offset_fixed;
        step_y = offset_fixed / duration_eighth;
        work->unk_44 = step_y / 2;
        ASM_KEEP(duration_eighth);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        step_z = -(offset_z << 16) / duration_eighth;
        work->unk_48 = step_z / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        work->unk_4C = step_x / 4;
        ASM_KEEP(step_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work->unk_50 = step_y / 4;
        ASM_KEEP(step_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(step_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work->unk_54 = step_z / 4;

        work->unk_14 = effect_id;
        work->unk_32 = duration;
        work->unk_34 = duration;
        func_8004491C(node, &D_80045340);

        sprite_data = D_800DEC70;
        ASM_KEEP(sprite_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sprite = ((S_80AC55DC_0 *)node)->unk_0C;
        sprite_size = 0x20;
        sprite_flags = sprite->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        sprite->unk_10 = sprite_size;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_14 = sprite_flags | 0xC;
        ((S_80AC55DC_0 *)node)->unk_20 = effect_value;
        work->unk_08 = effect_value;
        func_8003DB94(sprite, sprite_data, 0);
    }
}

/* MECHANISM: The seven live arguments naturally produce the retail 0x38 frame and saved-register order.
   Split pinned $v0 numerators from $a2/$a1/$v1 quotients; narrow barriers preserve each mflo/round/store seam.
   A one-read flags RMW plus held $a1 data pointer fixes the final li/lhu/zero-argument schedule. */
