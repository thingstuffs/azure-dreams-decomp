#include "common.h"
#include "m2c_compat.h"

typedef struct S_819AD81C_0_pre {
    u16 unk_00;
} S_819AD81C_0_pre;   /* the 0x2 bytes before arg0 in func_819AD81C, addressed as arg0[-1] */

typedef struct S_819AD81C_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x8];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x2];
    s16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x2];
    union { struct { s16 v; } at00; struct { s32 v; } at00u; struct { u16 v; } at00p; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_3C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_40;   /* overlapping accesses */
    u16 unk_44;
    union { s16 s; u16 u; } unk_46;   /* accessed as both */
    s16 unk_48;
} S_819AD81C_0;   /* arg0 in func_819AD81C */

typedef struct S_819AD81C_1 {
    s32 unk_00;
    s8 unk_04;
    u8 pad_05[0x7];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_819AD81C_1;   /* arg2 in func_819AD81C */

typedef struct S_819AD81C_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} S_819AD81C_2;   /* arg1 in func_819AD81C */

typedef struct S_819AD81C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_819AD81C_3_pre;   /* the 0x14 bytes before var_s0 in func_819AD81C, addressed as var_s0[-1] */

typedef struct S_819AD81C_3 {
    u8 pad_00[0x34];
    s16 unk_34;
    u8 pad_36[0x26];
    union { void * p; s32 i; } unk_5C;   /* accessed as both */
    u8 pad_60[0x28];
    s16 unk_88;
} S_819AD81C_3;   /* var_s0 in func_819AD81C */

typedef struct S_819AD81C_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x2];
    u8 unk_24;
    u8 unk_25;
} S_819AD81C_4;   /* temp_s1 in func_819AD81C */

typedef struct S_819AD81C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_819AD81C_5;   /* temp_a0 in func_819AD81C */

typedef struct S_819AD81C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819AD81C_6;   /* temp_v1_9 in func_819AD81C */


extern int D_800814A8[4];
extern s32 D_800814A0;
void func_8002512C(void) __attribute__((noreturn));
void func_80025410() __attribute__((noreturn));
void func_80025594(void) __attribute__((noreturn));
M2C_UNK func_800257D0();
M2C_UNK func_80025840();
M2C_UNK func_8002590C();
M2C_UNK func_8002593C();
M2C_UNK func_80025B78();
M2C_UNK func_80025FCC();
s32 func_800644B8();
s32 func_80064584();
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80065450();
M2C_UNK func_8009CE1C();
s32 func_800A07D0();
s32 func_800A45D8();
M2C_UNK func_800B653C();
extern s8 D_8002758C[];
extern u8 D_800287A2;
extern s32 D_800287A4;

void func_819AD81C(void *arg0_in, void *arg1_in, void *arg2_in) {
    typedef struct {
        s16 unk0;
        u16 unk2;
        s16 unk4;
        u16 unk6;
        s16 unk8;
        u16 unkA;
        s32 unkC;
        s32 unk10;
        s32 unk14;
    } Local20;
    typedef struct {
        s16 unk0;
        s16 unk2;
        s16 unk4;
    } Local38;
    Local20 sp20;
    Local38 sp38;
    M2C_UNK sp40;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v1_8;
    s32 temp_a1;
    s32 temp_v1_6;
    register s32 temp_v1_7 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_v0_2;
    s8 temp_a0_2;
    s8 temp_v1_10;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u16 saved_x;
    u16 saved_y;
    void *var_s0;
    void *temp_a0;
    void *temp_s1;
    void *list_root;
    void *temp_v1_9;
    void *arg0 = arg0_in;
    register void *arg1 ASM_REG("$19") = arg1_in;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *arg2 = arg2_in;

    temp_v1_9 = ((S_819AD81C_0 *)arg0)->unk_20;
    if (temp_v1_9 == 0) {
        temp_v0 = ((S_819AD81C_0 *)arg0)->unk_2C.s;
        if (temp_v0 == 0) {
            temp_v1_2 = ((S_819AD81C_1 *)arg2)->unk_0C.at00.v;
            temp_v1_3 = temp_v1_2 + ((s32) (0x80 - temp_v1_2) / ((S_819AD81C_0 *)arg0)->unk_30);
            ((S_819AD81C_1 *)arg2)->unk_0C.at00.v = temp_v1_3;
            ((S_819AD81C_1 *)arg2)->unk_0C.at01.v = temp_v1_3;
            ((S_819AD81C_1 *)arg2)->unk_0C.at02.v = temp_v1_3;
            temp_v0_2 = (u16) ((S_819AD81C_0 *)arg0)->unk_30 - 1;
            ((S_819AD81C_0 *)arg0)->unk_30 = temp_v0_2;
            if ((temp_v0_2 << 0x10) <= 0) {
                ((S_819AD81C_1 *)arg2)->unk_0C.at00u.v = 0x808080;
                ((S_819AD81C_0 *)arg0)->unk_2C.u = (u16) (((S_819AD81C_0 *)arg0)->unk_2C.u + 1);
                func_8002512C();
                return;
            }
            goto block_10;
        }
        if (temp_v0 >= 2) {
            temp_v1_4 = ((S_819AD81C_1 *)arg2)->unk_0C.at00.v;
            temp_v1_5 = temp_v1_4 - ((s32) temp_v1_4 / (s16) ((S_819AD81C_0 *)arg0)->unk_30);
            ((S_819AD81C_1 *)arg2)->unk_0C.at00.v = temp_v1_5;
            ((S_819AD81C_1 *)arg2)->unk_0C.at01.v = temp_v1_5;
            ((S_819AD81C_1 *)arg2)->unk_0C.at02.v = temp_v1_5;
            temp_v0_3 = (u16) ((S_819AD81C_0 *)arg0)->unk_30 - 1;
            ((S_819AD81C_0 *)arg0)->unk_30 = temp_v0_3;
            if ((temp_v0_3 << 0x10) <= 0) {
                ((S_819AD81C_1 *)arg2)->unk_0C.at00u.v = 0;
                func_80025410();
                return;
            }
            if (((S_819AD81C_0 *)arg0)->unk_2C.s < 3) {
                goto block_10;
            }
        } else {
block_10:
            ((S_819AD81C_2 *)arg1)->unk_0C.at00.v = (s32) (func_80064584(((S_819AD81C_0 *)arg0)->unk_34) << 8);
            ((S_819AD81C_2 *)arg1)->unk_10.at00.v = (s32) (func_800644B8(((S_819AD81C_0 *)arg0)->unk_34) << 8);
            temp_a0_2 = ((S_819AD81C_1 *)arg2)->unk_04;
            if (temp_a0_2 < 3) {
                temp_v1_6 = ((S_819AD81C_2 *)arg1)->unk_0C.at00.v;
                ((S_819AD81C_2 *)arg1)->unk_0C.at00.v = (s32) (temp_v1_6 - (temp_v1_6 >> (temp_a0_2 + 1)));
                temp_v1_7 = ((S_819AD81C_2 *)arg1)->unk_10.at00.v;
                ((S_819AD81C_2 *)arg1)->unk_10.at00.v = (s32) (temp_v1_7 - (temp_v1_7 >> (((S_819AD81C_1 *)arg2)->unk_04 + 1)));
            }
            ((S_819AD81C_2 *)arg1)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)arg1)->unk_08.at00.v - ((S_819AD81C_2 *)arg1)->unk_14);
            ((S_819AD81C_2 *)arg1)->unk_00.at00.v = (s32) (((S_819AD81C_2 *)arg1)->unk_00.at00.v + ((S_819AD81C_2 *)arg1)->unk_0C.at00.v);
            ((S_819AD81C_2 *)arg1)->unk_04.at00.v = (s32) (((S_819AD81C_2 *)arg1)->unk_04.at00.v + ((S_819AD81C_2 *)arg1)->unk_10.at00.v);
            ((S_819AD81C_2 *)arg1)->unk_08.at00.v = (s32) (((S_819AD81C_2 *)arg1)->unk_08.at00.v + ((S_819AD81C_2 *)arg1)->unk_14);
            ((S_819AD81C_1 *)arg2)->unk_16 = 0x400U;
            ((S_819AD81C_1 *)arg2)->unk_1A = (u16) (func_800A07D0(0, 0, ((S_819AD81C_2 *)arg1)->unk_0C.at02.v, ((S_819AD81C_2 *)arg1)->unk_10.at02.v) - 0x400);
            func_80025840(arg2, arg0 + 0x32, ((S_819AD81C_0 *)arg0)->unk_38, ((S_819AD81C_0 *)arg0)->unk_36);
            func_800257D0(arg0, ((S_819AD81C_1 *)arg2)->unk_00);
            if (((S_819AD81C_1 *)arg2)->unk_14 & 0x4000) {
                ((S_819AD81C_1 *)arg2)->unk_04 = 0;
            }
            if (((S_819AD81C_0 *)arg0)->unk_46.s > 0) {
                ((S_819AD81C_0 *)arg0)->unk_3C.at00.v = (s16) ((s16) ((S_819AD81C_2 *)arg1)->unk_00.at02.v / 64);
                temp_a1 = (s16) ((S_819AD81C_2 *)arg1)->unk_04.at02.v / 64;
                ((S_819AD81C_0 *)arg0)->unk_3C.at02.v = (s16) temp_a1;
                if (((S_819AD81C_0 *)arg0)->unk_40.at00.v != ((S_819AD81C_0 *)arg0)->unk_3C.at00u.v) {
                    if ((func_800A45D8(((((S_819AD81C_0 *)arg0)->unk_3C.at00.v << 6) + 0x20) & 0xFFE0, ((temp_a1 << 6) + 0x20) & 0xFFE0, ((S_819AD81C_2 *)arg1)->unk_08.at02.v) << 0x10) != 0) {
                        ((S_819AD81C_0 *)arg0)->unk_30 = 4;
                        ((S_819AD81C_0 *)arg0)->unk_2C.s = 3;
                        func_80025594();
                        return;
                    }
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    var_s0 = (void *) D_800814A8[0];
                    list_root = var_s0;
                    temp_v1_9 = ((S_819AD81C_3 *)var_s0)->unk_5C.p;
                    var_s0 = temp_v1_9 + 0x20;
                    if (var_s0 != list_root) {
                        do {
                            temp_s1 = ((S_819AD81C_3_pre *)var_s0)[-1].unk_00;
                            if (((S_819AD81C_4 *)temp_s1)->unk_24 == ((S_819AD81C_0 *)arg0)->unk_3C.at00.v) {
                                if (((S_819AD81C_4 *)temp_s1)->unk_25 == ((S_819AD81C_0 *)arg0)->unk_3C.at02.v) {
                                    var_v0_2 = ((S_819AD81C_3 *)var_s0)->unk_88;
                                    temp_v1_7 = ((S_819AD81C_2 *)arg1)->unk_08.at02.v;
                                    var_v0_2 -= temp_v1_7;
                                    if (var_v0_2 < 0) {
                                        var_v0_2 = 0 - var_v0_2;
                                    }
                                    if (var_v0_2 < 0x40) {
                                        func_8009CE1C(var_s0, 0xC, D_800287A2, 0xA, (s32) (s16) (((S_819AD81C_0 *)arg0)->unk_44 << 9), D_800287A4, 2);
                                    }
                                }
                            }
                            var_s0 = ((S_819AD81C_3 *)var_s0)->unk_5C.i + 0x20;
                        } while (var_s0 != (void *) D_800814A8[0]);
                    }
                    saved_x = ((S_819AD81C_0 *)arg0)->unk_3C.at00p.v;
                    temp_v1_8 = ((S_819AD81C_0 *)arg0)->unk_46.u;
                    saved_y = ((S_819AD81C_0 *)arg0)->unk_3C.at02u.v;
                    temp_v1_8 -= 1;
                    ((S_819AD81C_0 *)arg0)->unk_46.s = temp_v1_8;
                    ((S_819AD81C_0 *)arg0)->unk_40.at00u.v = saved_x;
                    ((S_819AD81C_0 *)arg0)->unk_40.at02.v = saved_y;
                    if ((temp_v1_8 << 0x10) <= 0) {
                        ((S_819AD81C_0 *)arg0)->unk_30 = 4;
                        ((S_819AD81C_0 *)arg0)->unk_2C.s = (s16) ((u16) ((S_819AD81C_0 *)arg0)->unk_2C.s + 1);
                    }
                    goto cleanup;
                }
                goto cleanup;
            }
cleanup:
            func_80025FCC(((S_819AD81C_2 *)arg1)->unk_00.at02.v, ((S_819AD81C_2 *)arg1)->unk_04.at02.v, ((S_819AD81C_2 *)arg1)->unk_08.at02.v, ((S_819AD81C_0 *)arg0)->unk_34);
            func_80025B78(arg0, arg1, arg2);
            func_80025594();
        }
    } else {
        temp_a0 = (void *) ((s32) temp_v1_9 | 0x80000000);
        if (((S_819AD81C_5 *)temp_a0)->unk_1E & 0x8000) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_819AD81C_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0 |= 0x8000;
            func_80025594();
            return;
        }
        temp_v1_9 = ((S_819AD81C_5 *)temp_a0)->unk_08;
        temp_s1 = ((S_819AD81C_5 *)temp_a0)->unk_0C;
        ((S_819AD81C_2 *)arg1)->unk_00.at02.v = (s16) ((S_819AD81C_6 *)temp_v1_9)->unk_02;
        ((S_819AD81C_2 *)arg1)->unk_04.at02.v = (s16) ((S_819AD81C_6 *)temp_v1_9)->unk_06;
        ((S_819AD81C_2 *)arg1)->unk_08.at02.v = (s16) ((S_819AD81C_6 *)temp_v1_9)->unk_0A;
        ((S_819AD81C_1 *)arg2)->unk_16 = (u16) ((S_819AD81C_4 *)temp_s1)->unk_16;
        ((S_819AD81C_1 *)arg2)->unk_18 = (u16) ((S_819AD81C_4 *)temp_s1)->unk_18;
        ((S_819AD81C_1 *)arg2)->unk_1A = (u16) ((S_819AD81C_4 *)temp_s1)->unk_1A;
        ((S_819AD81C_1 *)arg2)->unk_1C = (u16) ((S_819AD81C_4 *)temp_s1)->unk_1C;
        ((S_819AD81C_1 *)arg2)->unk_1E = (u16) ((S_819AD81C_4 *)temp_s1)->unk_1E;
        ((S_819AD81C_1 *)arg2)->unk_20 = (u16) ((S_819AD81C_4 *)temp_s1)->unk_20;
        ((S_819AD81C_1 *)arg2)->unk_0C.at00u.v = ((S_819AD81C_4 *)temp_s1)->unk_0C;
        temp_v1_10 = D_8002758C[((S_819AD81C_0 *)arg0)->unk_48];
        var_s0 = temp_a0 + 0x20;
        if ((temp_v1_10 >= 0) && (((S_819AD81C_4 *)temp_s1)->unk_04 == temp_v1_10)) {
            func_800649A0(temp_a0);
            func_8002593C(arg0, arg1, arg2);
            sp38.unk0 = 0;
            sp38.unk2 = 0;
            sp38.unk4 = 0;
            func_80065450(&sp38, arg1 + 0xC, &sp40);
            func_80064A40();
            sp20.unk2 = (u16) ((S_819AD81C_2 *)arg1)->unk_0C.at00.v;
            sp20.unk6 = (u16) ((S_819AD81C_2 *)arg1)->unk_10.at00.v;
            sp20.unkA = (u16) ((S_819AD81C_2 *)arg1)->unk_14;
            sp20.unkC = func_80064584(((S_819AD81C_3 *)var_s0)->unk_34) * 0x10;
            sp20.unk10 = func_800644B8(((S_819AD81C_3 *)var_s0)->unk_34) * 0x10;
            sp20.unk14 = 0;
            func_800B653C(&sp20, ((S_819AD81C_3 *)var_s0)->unk_34);
        }
        func_8002590C(arg2, ((S_819AD81C_4 *)temp_s1)->unk_04);
        func_800257D0(arg0, ((S_819AD81C_1 *)arg2)->unk_00);
    }
}
