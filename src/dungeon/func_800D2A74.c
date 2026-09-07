#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A0.h"

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



extern void *D_80089474[];
void func_800478B8(void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
s32 func_80064710(s32);
s32 func_80069EF8(void);
extern M2C_UNK D_800814A0;

void func_800D81D4(void *arg0, void *arg1, void *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6 };
    s32 temp_v1;
    M2C_UNK temp_v0;
    register u16 phase ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    S_800D81D4_1 *p1 = arg1;
    register S_800D81D4_2 *p2 ASM_REG("$17") = arg2;   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(p1);   /* MATCH pin: retail schedule: same instructions, different order without it */

    ((S_800D81D4_0 *)arg0)->unk_48.s = (s16) (((S_800D81D4_0 *)arg0)->unk_48.s - 1);
    func_800478B8(p2);
    temp_v1 = ((S_800D81D4_0 *)arg0)->unk_4C.s;
    if ((u32) temp_v1 >= 7U) {
        goto block_15;
    }
    (void)jt_keep; goto *D_80089474[temp_v1];
jt_c0:
    ((S_800D81D4_0 *)arg0)->unk_48.s = 0x10U;
    temp_v0 = (func_80069EF8() % 96) - 0x30;
    p1->unk_14.at00.v = (s32) ((s32) (temp_v0 << 0x10) / (s16) ((S_800D81D4_0 *)arg0)->unk_48.s);
    ((S_800D81D4_0 *)arg0)->unk_28 = (s32) ((s32) (func_80064710(0x900 - (temp_v0 * temp_v0)) << 0x10) / (s16) ((S_800D81D4_0 *)arg0)->unk_48.s);
    ((S_800D81D4_0 *)arg0)->unk_18 = func_80069EF8();
    ((S_800D81D4_0 *)arg0)->unk_4C.s = (s16) ((u16) ((S_800D81D4_0 *)arg0)->unk_4C.s + 1);
jt_c1: {
    register s32 pos ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 speed;
    register s32 color ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */

    p1->unk_08 = (s32) (p1->unk_08 + p1->unk_14.at00.v);
    pos = ((S_800D81D4_0 *)arg0)->unk_1C.at00.v;
    speed = ((S_800D81D4_0 *)arg0)->unk_28;
       /* MATCH pin: retail schedule: same instructions, different order without it */
    color = 0x40000;
    ((S_800D81D4_0 *)arg0)->unk_1C.at00.v = pos + speed;
    pos = p2->unk_0C;
    color |= 0x404;
    p2->unk_0C = pos + color;
    speed = ((S_800D81D4_0 *)arg0)->unk_48.u;
    pos = 0x20 - speed;
    speed = ((S_800D81D4_0 *)arg0)->unk_4A;
    pos <<= 3;
    ((S_800D81D4_0 *)arg0)->unk_18 = (u16) (((S_800D81D4_0 *)arg0)->unk_18 + (pos * speed));
    if ((s16) ((S_800D81D4_0 *)arg0)->unk_48.s >= 0) {
        goto block_15;
    }
}
    phase = ((S_800D81D4_0 *)arg0)->unk_4C.u;
    ((S_800D81D4_0 *)arg0)->unk_48.s = 0x14U;
    goto block_13;
jt_c2:
    ((S_800D81D4_0 *)arg0)->unk_18 = (u16) (((S_800D81D4_0 *)arg0)->unk_18 + (((S_800D81D4_0 *)arg0)->unk_4A * 0x140));
    if ((s16) ((S_800D81D4_0 *)arg0)->unk_48.s > 0) {
        goto block_15;
    }
    phase = ((S_800D81D4_0 *)arg0)->unk_4C.u;
    ((S_800D81D4_0 *)arg0)->unk_48.s = 0x1CU;
    goto block_13;
jt_c3:
    p1->unk_08 = (s32) (p1->unk_08 - ((s32) p1->unk_14.at00.v >> 1));
    ((S_800D81D4_0 *)arg0)->unk_1C.at00.v = (s32) (((S_800D81D4_0 *)arg0)->unk_1C.at00.v - ((s32) ((S_800D81D4_0 *)arg0)->unk_28 >> 1));
    p2->unk_0C = (s32) (p2->unk_0C + 0x30303);
    ((S_800D81D4_0 *)arg0)->unk_18 = (u16) (((S_800D81D4_0 *)arg0)->unk_18 + ((((0x1C - (s16) ((S_800D81D4_0 *)arg0)->unk_48.s) * 8) + 0x140) * ((S_800D81D4_0 *)arg0)->unk_4A));
    if ((s16) ((S_800D81D4_0 *)arg0)->unk_48.s > 0) {
        goto block_15;
    }
    phase = ((S_800D81D4_0 *)arg0)->unk_4C.u;
    ((S_800D81D4_0 *)arg0)->unk_48.s = 0U;
    goto block_13;
jt_c4:
    ((S_800D81D4_0 *)arg0)->unk_18 = (u16) (((S_800D81D4_0 *)arg0)->unk_18 + ((((0 - (s16) ((S_800D81D4_0 *)arg0)->unk_48.s) * 0x10) + 0x1E0) * ((S_800D81D4_0 *)arg0)->unk_4A));
    p2->unk_0C = (s32) (p2->unk_0C + 0x40404);
    if ((u8) p2->unk_0C < 0xF1U) {
        goto block_15;
    }
    p2->unk_10 = 0x60;
    p1->unk_14.at02.v = (s16) (0 - (func_80069EF8() & 3));
    goto block_12;
jt_c5:
    p1->unk_08 = (s32) (p1->unk_08 + p1->unk_14.at00.v);
    p1->unk_14.at00.v = (s32) (p1->unk_14.at00.v - ((func_80069EF8() & 0xFFF) << 6));
    ((S_800D81D4_0 *)arg0)->unk_1C.at00.v = (s32) (((S_800D81D4_0 *)arg0)->unk_1C.at00.v - 0x8000);
    ((S_800D81D4_0 *)arg0)->unk_18 = (u16) (((S_800D81D4_0 *)arg0)->unk_18 + ((((0 - (s16) ((S_800D81D4_0 *)arg0)->unk_48.s) * 0x10) + 0x1E0) * ((S_800D81D4_0 *)arg0)->unk_4A));
    p2->unk_0C = (s32) (p2->unk_0C + 0xFFE7E7E8);
    if ((u8) p2->unk_0C >= 0x18U) {
        goto block_15;
    }
block_12:
    phase = ((S_800D81D4_0 *)arg0)->unk_4C.u;
block_13:
    ((S_800D81D4_0 *)arg0)->unk_4C.s = (s16) (phase + 1);
    goto block_15;
jt_c6:
    ((S_800D81D4_0_pre *)arg0)[-1].unk_00 = (u16) (((S_800D81D4_0_pre *)arg0)[-1].unk_00 | 0x8000);
    (*(s32 *)&D_800814A0) = (s32) (((Rec_D_800814A0 *)(&D_800814A0))->unk_00 | 0x8000);
block_15:
    p1->unk_02 = (s16) (((S_800D81D4_0 *)arg0)->unk_0C + ((s32) (func_800644B8((s16) ((S_800D81D4_0 *)arg0)->unk_18) * ((S_800D81D4_0 *)arg0)->unk_1C.at02.v) >> 0xC));
    p1->unk_06 = (s16) (((S_800D81D4_0 *)arg0)->unk_0E + ((s32) (func_80064584((s16) ((S_800D81D4_0 *)arg0)->unk_18) * ((S_800D81D4_0 *)arg0)->unk_1C.at02.v) >> 0xC));
    return;
}
