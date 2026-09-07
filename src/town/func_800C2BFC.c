#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C035C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x6];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    s16 unk_12;
    u8 pad_14[0x8];
    void * unk_1C;
    u8 pad_20[0x28];
    s32 unk_48;
    s32 unk_4C;
    u8 pad_50[0x4];
    void * unk_54;
    s32 unk_58;
    s32 unk_5C;
} S_800C035C_0;   /* arg0 in func_800C035C */

typedef struct S_800C035C_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800C035C_1;   /* arg1 in func_800C035C */

typedef struct S_800C035C_2 {
    u8 pad_00[0x2E];
    u16 unk_2E;
    u8 pad_30[0x8];
    s16 unk_38;
    u8 pad_3A[0x2];
    s16 unk_3C;
} S_800C035C_2;   /* temp_s5 in func_800C035C */

typedef struct S_800C035C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xB4];
    union { s16 s; volatile s16 u; volatile u16 p; } unk_C8;   /* accessed as both */
} S_800C035C_3;   /* temp_s3 in func_800C035C */

typedef struct S_800C035C_4 {
    s16 unk_00;
    s16 unk_02;
} S_800C035C_4;   /* temp_s4 in func_800C035C */

typedef struct S_800C035C_5 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_5;   /* ((temp_v1_6 * 2) + (s8 *) temp_s5) in func_800C035C */

typedef struct S_800C035C_6 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_6;   /* ((temp_s0 * 2) + (s8 *) temp_s5) in func_800C035C */

typedef struct S_800C035C_7 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_800C035C_7;   /* ((temp_v1_9 * 2) + (s8 *) temp_s5) in func_800C035C */

typedef struct S_800C035C_8 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    s32 unk_2C;
} S_800C035C_8;   /* arg2 in func_800C035C */

typedef struct S_800C035C_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C035C_9;   /* &D_80100D98 in func_800C035C */

typedef struct S_800C035C_10 {
    u8 pad_00[0x30];
    s16 unk_30;
} S_800C035C_10;   /* ((((S_800C035C_4 *)temp_s4)->unk_00 * 2) + (s8 *) temp_s5) in func_800C035C */


typedef struct {
    s32 w[6];
} Blk24;

typedef struct {
    s32 w[5];
} Blk20;

M2C_UNK func_80022F34();              /* extern */
M2C_UNK func_800239A0();     /* extern */
M2C_UNK func_80033B9C();              /* extern */
M2C_UNK func_8003BAF8();                       /* extern */
M2C_UNK func_800489F4();     /* extern */
M2C_UNK func_80048AC8(void *, s32);             /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
M2C_UNK func_8008B550();     /* extern */
M2C_UNK func_8009539C();                      /* extern */
M2C_UNK func_800953D0();                      /* extern */
M2C_UNK func_800954F4();                      /* extern */
M2C_UNK func_80095910();                   /* extern */
M2C_UNK func_800A48B0();           /* extern */
M2C_UNK func_800ABD74();                      /* extern */
s16 func_800C2AE8();                      /* extern */
extern void *jtbl_80089978[];
__asm__(".set jtbl_80089978, 0x80089978");
extern s32 D_800135B4;
__asm__(".set D_800135B4, 0x800135B4");
extern M2C_UNK D_8006CCF8;
extern M2C_UNK D_80083160;
extern M2C_UNK D_80089960;
extern u8 D_800CFCEE;
extern M2C_UNK D_800FE490;
extern M2C_UNK D_80100D98;

void func_800C035C(void *arg0, S_800C035C_1 *arg1, S_800C035C_8 *arg2) {
    Blk24 sp10;
    Blk20 sp28;
    s32 temp_s0;
    s16 temp_v1;
    s32 temp_v1_6;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s16 var_s6;
    s16 var_v0_5;
    s32 base48;
    s32 temp_s0_2;
    s32 tA;
    s32 tB;
    s32 temp_v1_2;
    s32 temp_v1_5;
    s32 flags8;
    register s32 var_s0 ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 var_v0_4;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_9;
    u16 temp_v1_10;
    u16 var_v0_10;
    S_800C035C_3 *temp_s3;
    S_800C035C_4 *temp_s4;
    S_800C035C_2 *temp_s5;
    void *temp_v0;
    void *temp_v1_7;

    temp_s3 = &D_80083160;
    temp_s5 = ((S_800C035C_0 *)arg0)->unk_54;
    temp_s4 = (s8 *)arg0 + 0x50;
    func_800953D0(arg1);
    func_80095910(&D_800FE490);
    func_8009539C(arg1);
    arg1->unk_00 = (s32) (arg1->unk_00 + ((S_800C035C_0 *)arg0)->unk_58);
    arg1->unk_04 = (s32) (arg1->unk_04 + ((S_800C035C_0 *)arg0)->unk_5C);
    ((S_800C035C_0 *)arg0)->unk_58 = (s32) ((s32) ((S_800C035C_0 *)arg0)->unk_58 >> 1);
    ((S_800C035C_0 *)arg0)->unk_5C = (s32) ((s32) ((S_800C035C_0 *)arg0)->unk_5C >> 1);
    sp10 = *(Blk24 *) arg1;
    temp_v1 = temp_s5->unk_3C;
    if ((temp_v1 == 2) || (temp_v1 == 6)) {
        sp10.w[2] = 0xFE000000;
    }
    var_s6 = func_800C2AE8(&sp10);
    if ((var_s6 << 0x10) > 0) {
        var_s6 = 0;
    }
    if ((temp_s3->unk_10 & 0x20) && (((S_800C035C_0 *)arg0)->unk_48 <= 0x200000)) {
        func_800ABD74(arg1);
        ((S_800C035C_0 *)arg0)->unk_48 = (s32) (((S_800C035C_0 *)arg0)->unk_48 + 0x80000);
    }
    if (temp_s3->unk_10 & 0x40) {
        temp_v1_2 = ((S_800C035C_0 *)arg0)->unk_48;
        if (temp_v1_2 >= (s32) 0xFFE00000) {
            ((S_800C035C_0 *)arg0)->unk_48 = (s32) (temp_v1_2 + 0xFFF80000);
        }
    }
    flags8 = temp_s3->unk_08;
    if (flags8 & 0x20) {
        base48 = ((S_800C035C_0 *)arg0)->unk_48;
        if (base48 < 0) {
            ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 + 0x20000);
        } else if (base48 <= 0xFFFFF) {
            ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 + 0x18000);
        } else {
            goto have48;
        }
    } else if (flags8 & 0x40) {
        base48 = ((S_800C035C_0 *)arg0)->unk_48;
        if (base48 > 0) {
            ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 + 0xFFFE0000);
        } else if (base48 > (s32) 0xFFF00000) {
            ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 + 0xFFFE8000);
        } else {
            goto have48;
        }
    }
    base48 = ((S_800C035C_0 *)arg0)->unk_48;
have48:
    if (base48 < (s32) 0xFFFF0000) {
        ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 + 0x10000);
    } else if (base48 > 0x10000) {
        ((S_800C035C_0 *)arg0)->unk_48 = (s32) (base48 - 0x10000);
    } else {
        ((S_800C035C_0 *)arg0)->unk_48 = 0;
    }
    flags8 = temp_s3->unk_08;
    if (flags8 & 0x8000) {
        var_v0_4 = ((S_800C035C_0 *)arg0)->unk_10.s + 0x20;
        goto block_31;
    }
    if (flags8 & 0x2000) {
        var_v0_4 = ((S_800C035C_0 *)arg0)->unk_10.s + 0xFE0;
block_31:
        ((S_800C035C_0 *)arg0)->unk_10.s = (u16) (var_v0_4 & 0xFFF);
    }
    arg1->unk_0C = (s32) (func_800644B8((s16) ((S_800C035C_0 *)arg0)->unk_10.s) * ((s32) ((S_800C035C_0 *)arg0)->unk_48 >> 0xC));
    arg1->unk_10 = (s32) (func_80064584((s16) ((S_800C035C_0 *)arg0)->unk_10.s) * ((s32) ((S_800C035C_0 *)arg0)->unk_48 >> 0xC));
    tA = temp_s3->unk_C8.s - 0x800;
    tB = ((S_800C035C_0 *)arg0)->unk_10.u;
    var_s0 = tB - tA;
loop_33:
    if (var_s0 >= 0x801) {
        var_s0 -= 0x1000;
        goto loop_33;
    }
    if (var_s0 < -0x800) {
        var_s0 += 0x1000;
        goto loop_33;
    }
    temp_v1_2 = 0x30000;
    var_v0_4 = ((S_800C035C_0 *)arg0)->unk_48;
    temp_v1_2 |= 0xFFFF;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (var_v0_4 < 0) {
        var_v0_4 = 0 - var_v0_4;
    }
    temp_v1_2 = temp_v1_2 < var_v0_4;
    if (temp_v1_2 && (temp_s3->unk_08 & 0xA000)) {
        if (var_s0 < -0x180) {
            var_v0_5 = ((S_800C035C_0 *)arg0)->unk_10.s + 0x980;
        } else if (var_s0 >= 0x181) {
            var_v0_5 = ((S_800C035C_0 *)arg0)->unk_10.s + 0x680;
        } else if (var_s0 < 0) {
            var_v0_5 = (u16) temp_s3->unk_C8.s - 0x10;
        } else if (var_s0 > 0) {
            var_v0_5 = (u16) temp_s3->unk_C8.s + 0x10;
        } else {
            goto block_53;
        }
    } else {
        var_v0_6 = var_s0;
        if (var_s0 < 0) {
            var_v0_6 = 0 - var_v0_6;
        }
        if (var_v0_6 >= 8) {
            temp_v1_2 = var_s0 >> 3;
            var_v0_5 = (u16) temp_s3->unk_C8.s + temp_v1_2;
        } else {
block_53:
            var_v0_5 = ((S_800C035C_0 *)arg0)->unk_10.s + 0x800;
        }
    }
    temp_s3->unk_C8.s = var_v0_5;
    temp_s3->unk_C8.u = (s16) ((temp_s3->unk_C8.p + 0x1000) & 0xFFF);
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_v0_7 = var_s0;
    if (var_s0 < 0) {
        var_v0_7 = 0 - var_v0_7;
    }
    if (var_v0_7 >= 0xA0) {
        if (var_s6 <= (arg1->unk_08.at02.v + 2)) {
            if (((S_800C035C_0 *)arg0)->unk_48 > 0xC0000) {
                func_800ABD74(arg1);
            }
        }
    }
    if (D_800CFCEE != 0) {
        arg1->unk_14 = 0;
        func_800954F4(arg1);
    }
    if (arg1->unk_08.at02.v > var_s6) {
        arg1->unk_08.at02.v = var_s6;
        if (arg1->unk_14 >= 0) {
            arg1->unk_14 = 0;
        }
        if (((S_800C035C_0 *)arg0)->unk_4C & 1) {
            func_800ABD74(arg1);
        }
        temp_v1_2 = -2;
        var_v0_9 = ((S_800C035C_0 *)arg0)->unk_4C & temp_v1_2;
    } else {
        var_v0_9 = ((S_800C035C_0 *)arg0)->unk_4C | 1;
    }
    ((S_800C035C_0 *)arg0)->unk_4C = var_v0_9;
    if ((temp_s3->unk_10 & 0x10) && (var_s6 == arg1->unk_08.at02.v)) {
        arg1->unk_14 = -0x140000;
    }
    arg1->unk_14 = (s32) (arg1->unk_14 + 0x20000);
    {
        static void *const keepalive[] = {&&sw0, &&sw1, &&sw2, &&sw3, &&sw4};
        (void) keepalive;
        temp_v1_5 = ((S_800C035C_0 *)arg0)->unk_08;
        if ((u32) temp_v1_5 < 5) {
            goto *jtbl_80089978[temp_v1_5];
        }
        goto sw_end;
    }
    {
sw0:
        ((S_800C035C_0 *)arg0)->unk_10.s = 0xC00U;
        arg1->unk_08.at00.v = 0;
        temp_s4->unk_02 = 0;
        temp_s4->unk_00 = 0;
        temp_s3->unk_C8.s = 0xC00;
        goto block_78;
sw1:
        temp_s3->unk_C8.s = (s16) (((0x20 - temp_s5->unk_2E) << 5) + 0xC00);
        ((S_800C035C_0 *)arg0)->unk_10.s = 0xC00U;
        goto block_78;
sw2:
        temp_s3->unk_C8.s = (s16) ((0x10 - temp_s5->unk_2E) << 5);
        temp_v1_6 = temp_s4->unk_00;
        if (temp_v1_6 < 4) {
            ((S_800C035C_5 *)(((temp_v1_6 * 2) + (s8 *) temp_s5)))->unk_30 =
                (u16) (((S_800C035C_5 *)(((temp_v1_6 * 2) + (s8 *) temp_s5)))->unk_30 + 1);
        }
block_78:
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        goto sw_end;
sw3:
        temp_s0 = temp_s4->unk_00;
        func_80022F34(arg1, temp_s4);
        func_800239A0(temp_s5, temp_s4, 0);
        if (temp_s4->unk_00 != temp_s0) {
            s32 *best;

            best = (s32 *)0x800135B4;
            ASM_KEEP(best);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            temp_v1_8 = ((S_800C035C_6 *)(((temp_s0 * 2) + (s8 *) temp_s5)))->unk_30;
            if (temp_v1_8 < *best) {
                *best = (s32) temp_v1_8;
                temp_s5->unk_38 = temp_v1_8;
                func_80033B9C(0x596, best);
            }
        }
        temp_v1_9 = temp_s4->unk_00;
        if (temp_v1_9 < 4) {
            temp_v1_10 = ((S_800C035C_7 *)(((temp_v1_9 * 2) + (s8 *) temp_s5)))->unk_30;
            ((S_800C035C_7 *)(((temp_v1_9 * 2) + (s8 *) temp_s5)))->unk_30 = (u16) (temp_v1_10 + 1);
            if ((s16) temp_v1_10 >= 0x7530) {
                ((S_800C035C_10 *)(((temp_s4->unk_00 * 2) + (s8 *) temp_s5)))->unk_30 = 0x7530;
            }
        }
        goto sw_end;
sw4:
        sp28 = *(Blk20 *) &D_80089960;
        func_8008B550(2);
        func_8003BAF8(&sp28);
        ((S_800C035C_0 *)arg0)->unk_08 = (s16) ((u16) ((S_800C035C_0 *)arg0)->unk_08 + 1);
    }
sw_end:
    {
        register s32 tail_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
        tA = (s32) ((S_800C035C_0 *)arg0)->unk_10.u - 0x1500;
        tB = temp_s3->unk_C8.s;
        tail_v1 = tB - tA;
        temp_s0_2 = (tail_v1 & 0xFFF) >> 9;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
    ((S_800C035C_0 *)arg0)->unk_10.s = (u16) ((((S_800C035C_0 *)arg0)->unk_10.s + 0x2000) & 0xFFF);
    if (((S_800C035C_0 *)arg0)->unk_12 != temp_s0_2) {
        if (arg2->unk_2C != 0) {
            func_800489F4(arg2, ((u8 *)((S_800C035C_0 *)arg0)->unk_1C)[temp_s0_2], arg2->unk_04, 0);
        }
        ((S_800C035C_0 *)arg0)->unk_12 = (s16) temp_s0_2;
    }
    if (((u8 *)&D_8006CCF8)[temp_s0_2] != 0) {
        var_v0_10 = arg2->unk_14 | 1;
    } else {
        var_v0_10 = arg2->unk_14 & 0xFFFE;
    }
    arg2->unk_14 = var_v0_10;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    func_80048AC8(arg2, 0);
    func_800A48B0(&D_80100D98, arg1);
    ((S_800C035C_9 *)(&D_80100D98))->unk_08 = 0;
}
