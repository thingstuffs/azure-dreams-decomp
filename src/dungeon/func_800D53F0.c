#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800DAB50_0_pre {
    u16 unk_00;
} S_800DAB50_0_pre;   /* the 0x2 bytes before var_s2 in func_800DAB50, addressed as var_s2[-1] */

typedef struct S_800DAB50_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { u16 s; volatile u16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    s32 unk_0C;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    u8 pad_14[0xC];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
} S_800DAB50_0;   /* var_s2 in func_800DAB50 */

typedef struct S_800DAB50_1 {
    u8 pad_00[0x28];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
} S_800DAB50_1;   /* p in func_800DAB50 */


typedef struct WorkBlock {
    s16 *unk0;
    s16 *unk4;
    s32 unk8;
    u16 unkC;
    s32 unk10;
    s32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
} WorkBlock;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];
extern s32 func_800644B8();
extern s32 func_80066460();
extern void func_800DBA90(WorkBlock *);
extern void func_800DABB0();
extern void func_800DAD60();
extern void func_800DADE4();
extern void func_800DAE18();

void func_800DAB50(void *arg0) {
    WorkBlock work;
    void *var_s2 = arg0;
    register s32 var_s0 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 var_a0_2 ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 var_a1_2;
    s32 temp_shifted;
    register s32 temp_v0_2 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_v1;

    work.unk28 = 0;
    work.unk20 = 0;
    if (((S_800DAB50_0 *)var_s2)->unk_08 != 0) {
        work.unk22 = 0x30;
        work.unk2A = ((S_800DAB50_0 *)var_s2)->unk_02.s + 0x30;
        func_800DABB0();
        return;
    }
    temp_v0_2 = ((S_800DAB50_0 *)var_s2)->unk_02.s;
    work.unk2A = 0x30;
    work.unk22 = (temp_v0_2 * 2) + 0x40;
    var_s0 = 0;
    work.unk24 = (s16)(func_800644B8(((s16)((S_800DAB50_0 *)var_s2)->unk_02.s - 0x20) << 6) >> 6);
    work.unk0 = &work.unk20;
    work.unk2C = 0;
    work.unk18 = 2;
    temp_v0_2 = ((S_800DAB50_0 *)var_s2)->unk_0A.s;
    var_s1 = 0x28;
    work.unk8 = 0;
    work.unk14 = 0;
    work.unk10 = 0;
    work.unk1A = 0;
    work.unkC = temp_v0_2;
    do {
        work.unk4 = (s16 *)((s8 *)var_s2 + var_s1);
        func_800DBA90(&work);
        temp_v0_2 = work.unkC;
        ASM_KEEP(temp_v0_2);   /* MATCH pin: keeps a statement from moving across a call/branch */
        var_s0 += 1;
        work.unkC = temp_v0_2 + 0x200;
        var_s1 += 0x10;
    } while (var_s0 < 2);

    var_s0 = 3;
    {
        register s16 *p ASM_REG("$4") = (s16 *)((s8 *)var_s2 + 0x18);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        do {
            ((S_800DAB50_1 *)p)->unk_28 = (u16)(((S_800DAB50_1 *)p)->unk_28 + ((S_800DAB50_0 *)var_s2)->unk_20);
            ((S_800DAB50_1 *)p)->unk_2A = (u16)(((S_800DAB50_1 *)p)->unk_2A + ((S_800DAB50_0 *)var_s2)->unk_22);
            var_s0 -= 1;
            ((S_800DAB50_1 *)p)->unk_2C = (u16)(((S_800DAB50_1 *)p)->unk_2C + ((S_800DAB50_0 *)var_s2)->unk_24);
            p -= 4;
        } while (var_s0 >= 0);
    }

    temp_v1 = ((S_800DAB50_0 *)var_s2)->unk_00.s;
    if (temp_v1 != 1) {
        if (temp_v1 < 2) {
            if (temp_v1 != 0) {
                func_800DADE4();
                return;
            }
            goto state_0;
        }
        if (temp_v1 != 2) {
            if (temp_v1 != 3) {
                func_800DADE4();
                return;
            }
            goto state_3;
        }
        goto state_2;
    }
    goto state_1;

state_0:
    ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = 0;
    ((S_800DAB50_0 *)var_s2)->unk_04 = func_80066460(0, 1, 0x2C0, 0x100);
    ((S_800DAB50_0 *)var_s2)->unk_0C = 0x242424;
    ((S_800DAB50_0 *)var_s2)->unk_00.s = (s16)((u16)((S_800DAB50_0 *)var_s2)->unk_00.s + 1);
    goto state_1;

state_1:
    ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = ((S_800DAB50_0 *)var_s2)->unk_10.at00.v + ((S_800DAB50_0 *)var_s2)->unk_0C;
    var_a0_2 = 0;
    if (((S_800DAB50_0 *)var_s2)->unk_10.at03.v != 0) {
        func_80066460(0, 3, 0x2C0, 0x100);
        func_800DAD60(var_a0_2, 0xFFFFFF);
        return;
    }
    goto block_27;

state_2:
    ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = ((S_800DAB50_0 *)var_s2)->unk_10.at00.v - ((S_800DAB50_0 *)var_s2)->unk_0C;
    var_a0_2 = 0;
    if ((u8)((S_800DAB50_0 *)var_s2)->unk_10.at00.v == 0x7F) {
        temp_v0_2 = func_80066460(0, 3, 0x2C0, 0x100);
        var_a1_2 = 0xA0A0A0;
        var_a0_2 = 0x101010;
        temp_v1 = ((S_800DAB50_0 *)var_s2)->unk_00.u;
        ((S_800DAB50_0 *)var_s2)->unk_04 = temp_v0_2;
        ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = var_a1_2;
        ASM_KEEP(var_a1_2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_800DAB50_0 *)var_s2)->unk_0C = var_a0_2;
        temp_v1 += 1;
        ((S_800DAB50_0 *)var_s2)->unk_00.s = temp_v1;
        func_800DADE4((void *)var_a0_2, var_a1_2);
        return;
    }
    goto block_27;

state_3:
    var_a0_2 = ((S_800DAB50_0 *)var_s2)->unk_0C;
    var_a1_2 = var_a0_2;
    temp_shifted = ((S_800DAB50_0 *)var_s2)->unk_10.at00.v - var_a0_2;
    ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = temp_shifted;
    if (var_a1_2 > 0x80808) {
        ((S_800DAB50_0 *)var_s2)->unk_0C = var_a1_2 + 0xFFFEFEFF;
    }
    if (((S_800DAB50_0 *)var_s2)->unk_10.at00.v < 0) {
        ((S_800DAB50_0 *)var_s2)->unk_10.at00.v = 0;
        ((S_800DAB50_0_pre *)var_s2)[-1].unk_00 = (u16)(((S_800DAB50_0_pre *)var_s2)[-1].unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }

block_27:
    temp_v0_2 = ((S_800DAB50_0 *)var_s2)->unk_02.u;
    temp_v0_2 <<= 0x10;
    temp_shifted = temp_v0_2 >> 0xE;
    temp_v0_2 >>= 0x11;
    var_s0 = temp_shifted + temp_v0_2;
    temp_v0_2 = ((S_800DAB50_0 *)var_s2)->unk_08;
    temp_shifted = ((S_800DAB50_0 *)var_s2)->unk_0A.u;
    if (temp_v0_2 == 0) {
        temp_shifted -= var_s0;
        ASM_TAILSLOT_PIN(temp_shifted);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800DAE18(var_a0_2);
        return;
    }
    temp_shifted += var_s0;
    ASM_KEEP(temp_shifted);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_v0_2 = ((S_800DAB50_0 *)var_s2)->unk_02.u;
    ((S_800DAB50_0 *)var_s2)->unk_0A.s = temp_shifted;
    ((S_800DAB50_0 *)var_s2)->unk_02.s = temp_v0_2 - 1;
}
