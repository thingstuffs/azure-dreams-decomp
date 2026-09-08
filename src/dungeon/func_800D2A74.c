#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D81D4_0_pre {
    u16 unk_00;
} S_800D81D4_0_pre;   /* the 0x2 bytes before arg0 in func_800D81D4, addressed as arg0[-1] */

typedef struct S_800D81D4_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x8];
    u16 unk_18;
    u8 pad_1A[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x1C];
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    s16 unk_4A;
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_800D81D4_0;   /* arg0 in func_800D81D4 */

typedef struct S_800D81D4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D81D4_1;   /* p1 in func_800D81D4 */

typedef struct S_800D81D4_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
} S_800D81D4_2;   /* p2 in func_800D81D4 */

typedef struct S_800D81D4_3 {
    s32 unk_00;
} S_800D81D4_3;   /* &D_800814A0 in func_800D81D4 */


extern void *D_80089474[];
void func_800478B8(void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 func_80064710(s32);
s32 func_80069EF8(void);
extern M2C_UNK D_800814A0;

/* Updates a rotating effect's motion, color, and lifetime. */
void func_800D81D4(S_800D81D4_0 *effect, void *motion_data, void *primitive_data) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    s32 phase_index;
    M2C_UNK height_offset;
    register u16 phase ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_800D81D4_1 *motion = motion_data;
    register S_800D81D4_2 *primitive ASM_REG("$17") = primitive_data;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    effect->unk_48.s = (s16) (effect->unk_48.s - 1);
    func_800478B8(primitive);
    phase_index = effect->unk_4C.s;
    if ((u32) phase_index >= 7U) {
        goto update_position;
    }
    (void)jt_keep; goto *D_80089474[phase_index];
jt_c0:
    effect->unk_48.s = 0x10U;
    height_offset = (func_80069EF8() % 96) - 0x30;
    motion->unk_14.at00.v = (s32) ((s32) (height_offset << 0x10) / (s16) effect->unk_48.s);
    effect->unk_28 = (s32) ((s32) (func_80064710(0x900 - (height_offset * height_offset)) << 0x10) / (s16) effect->unk_48.s);
    effect->unk_18 = func_80069EF8();
    effect->unk_4C.s = (s16) ((u16) effect->unk_4C.s + 1);
jt_c1: {
    register s32 motion_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 motion_step;
    register s32 color_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14.at00.v);
    motion_value = effect->unk_1C.at00.v;
    motion_step = effect->unk_28;
    color_step = 0x40000;
    effect->unk_1C.at00.v = motion_value + motion_step;
    motion_value = primitive->unk_0C;
    color_step |= 0x404;
    primitive->unk_0C = motion_value + color_step;
    motion_step = effect->unk_48.u;
    motion_value = 0x20 - motion_step;
    motion_step = effect->unk_4A;
    motion_value <<= 3;
    effect->unk_18 = (u16) (effect->unk_18 + (motion_value * motion_step));
    if ((s16) effect->unk_48.s >= 0) {
        goto update_position;
    }
}
    phase = effect->unk_4C.u;
    effect->unk_48.s = 0x14U;
    goto advance_phase;
jt_c2:
    effect->unk_18 = (u16) (effect->unk_18 + (effect->unk_4A * 0x140));
    if ((s16) effect->unk_48.s > 0) {
        goto update_position;
    }
    phase = effect->unk_4C.u;
    effect->unk_48.s = 0x1CU;
    goto advance_phase;
jt_c3:
    motion->unk_08 = (s32) (motion->unk_08 - ((s32) motion->unk_14.at00.v >> 1));
    effect->unk_1C.at00.v = (s32) (effect->unk_1C.at00.v - ((s32) effect->unk_28 >> 1));
    primitive->unk_0C = (s32) (primitive->unk_0C + 0x30303);
    effect->unk_18 = (u16) (effect->unk_18 + ((((0x1C - (s16) effect->unk_48.s) * 8) + 0x140) * effect->unk_4A));
    if ((s16) effect->unk_48.s > 0) {
        goto update_position;
    }
    phase = effect->unk_4C.u;
    effect->unk_48.s = 0U;
    goto advance_phase;
jt_c4:
    effect->unk_18 = (u16) (effect->unk_18 + ((((0 - (s16) effect->unk_48.s) * 0x10) + 0x1E0) * effect->unk_4A));
    primitive->unk_0C = (s32) (primitive->unk_0C + 0x40404);
    if ((u8) primitive->unk_0C < 0xF1U) {
        goto update_position;
    }
    primitive->unk_10 = 0x60;
    motion->unk_14.at02.v = (s16) (0 - (func_80069EF8() & 3));
    goto load_phase;
jt_c5:
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14.at00.v);
    motion->unk_14.at00.v = (s32) (motion->unk_14.at00.v - ((func_80069EF8() & 0xFFF) << 6));
    effect->unk_1C.at00.v = (s32) (effect->unk_1C.at00.v - 0x8000);
    effect->unk_18 = (u16) (effect->unk_18 + ((((0 - (s16) effect->unk_48.s) * 0x10) + 0x1E0) * effect->unk_4A));
    primitive->unk_0C = (s32) (primitive->unk_0C + 0xFFE7E7E8);
    if ((u8) primitive->unk_0C >= 0x18U) {
        goto update_position;
    }
load_phase:
    phase = effect->unk_4C.u;
advance_phase:
    effect->unk_4C.s = (s16) (phase + 1);
    goto update_position;
jt_c6:
    ((S_800D81D4_0_pre *)effect)[-1].unk_00 = (u16) (((S_800D81D4_0_pre *)effect)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((S_800D81D4_3 *)(&D_800814A0))->unk_00 | 0x8000);
update_position:
    motion->unk_02 = (s16) (effect->unk_0C + ((s32) (func_800644B8((s16) effect->unk_18) * effect->unk_1C.at02.v) >> 0xC));
    motion->unk_06 = (s16) (effect->unk_0E + ((s32) (func_80064584((s16) effect->unk_18) * effect->unk_1C.at02.v) >> 0xC));
    return;
}
