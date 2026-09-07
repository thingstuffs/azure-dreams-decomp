#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

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

void func_800C035C(void *arg0, void *arg1, void *arg2) {
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
    register s32 var_s0 ASM_REG("$16");
    s32 var_v0_4;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_9;
    u16 temp_v1_10;
    u16 var_v0_10;
    void *temp_s3;
    register void *temp_s4 ASM_REG("$20");
    void *temp_s5;
    void *temp_v0;
    void *temp_v1_7;

    temp_s3 = &D_80083160;
    temp_s5 = M2C_FIELD(arg0, void **, 0x54);
    temp_s4 = (s8 *)arg0 + 0x50;
    func_800953D0(arg1);
    func_80095910(&D_800FE490);
    func_8009539C(arg1);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x58));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x5C));
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x58) >> 1);
    M2C_FIELD(arg0, s32 *, 0x5C) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0x5C) >> 1);
    sp10 = *(Blk24 *) arg1;
    temp_v1 = M2C_FIELD(temp_s5, s16 *, 0x3C);
    if ((temp_v1 == 2) || (temp_v1 == 6)) {
        sp10.w[2] = 0xFE000000;
    }
    var_s6 = func_800C2AE8(&sp10);
    if ((var_s6 << 0x10) > 0) {
        var_s6 = 0;
    }
    if ((M2C_FIELD(temp_s3, s32 *, 0x10) & 0x20) && (M2C_FIELD(arg0, s32 *, 0x48) <= 0x200000)) {
        func_800ABD74(arg1);
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + 0x80000);
    }
    if (M2C_FIELD(temp_s3, s32 *, 0x10) & 0x40) {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x48);
        if (temp_v1_2 >= (s32) 0xFFE00000) {
            M2C_FIELD(arg0, s32 *, 0x48) = (s32) (temp_v1_2 + 0xFFF80000);
        }
    }
    flags8 = M2C_FIELD(temp_s3, s32 *, 8);
    if (flags8 & 0x20) {
        base48 = M2C_FIELD(arg0, s32 *, 0x48);
        if (base48 < 0) {
            M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 + 0x20000);
        } else if (base48 <= 0xFFFFF) {
            M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 + 0x18000);
        } else {
            goto have48;
        }
    } else if (flags8 & 0x40) {
        base48 = M2C_FIELD(arg0, s32 *, 0x48);
        if (base48 > 0) {
            M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 + 0xFFFE0000);
        } else if (base48 > (s32) 0xFFF00000) {
            M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 + 0xFFFE8000);
        } else {
            goto have48;
        }
    }
    base48 = M2C_FIELD(arg0, s32 *, 0x48);
have48:
    if (base48 < (s32) 0xFFFF0000) {
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 + 0x10000);
    } else if (base48 > 0x10000) {
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) (base48 - 0x10000);
    } else {
        M2C_FIELD(arg0, s32 *, 0x48) = 0;
    }
    flags8 = M2C_FIELD(temp_s3, s32 *, 8);
    if (flags8 & 0x8000) {
        var_v0_4 = M2C_FIELD(arg0, u16 *, 0x10) + 0x20;
        goto block_31;
    }
    if (flags8 & 0x2000) {
        var_v0_4 = M2C_FIELD(arg0, u16 *, 0x10) + 0xFE0;
block_31:
        M2C_FIELD(arg0, u16 *, 0x10) = (u16) (var_v0_4 & 0xFFF);
    }
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0x10)) * ((s32) M2C_FIELD(arg0, s32 *, 0x48) >> 0xC));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (func_80064584((s16) M2C_FIELD(arg0, u16 *, 0x10)) * ((s32) M2C_FIELD(arg0, s32 *, 0x48) >> 0xC));
    tA = M2C_FIELD(temp_s3, s16 *, 0xC8) - 0x800;
    tB = M2C_FIELD(arg0, s16 *, 0x10);
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
    var_v0_4 = M2C_FIELD(arg0, s32 *, 0x48);
    temp_v1_2 |= 0xFFFF;
    ASM_SCHED_BARRIER();
    if (var_v0_4 < 0) {
        var_v0_4 = 0 - var_v0_4;
    }
    temp_v1_2 = temp_v1_2 < var_v0_4;
    if (temp_v1_2 && (M2C_FIELD(temp_s3, s32 *, 8) & 0xA000)) {
        if (var_s0 < -0x180) {
            var_v0_5 = M2C_FIELD(arg0, u16 *, 0x10) + 0x980;
        } else if (var_s0 >= 0x181) {
            var_v0_5 = M2C_FIELD(arg0, u16 *, 0x10) + 0x680;
        } else if (var_s0 < 0) {
            var_v0_5 = (u16) M2C_FIELD(temp_s3, s16 *, 0xC8) - 0x10;
        } else if (var_s0 > 0) {
            var_v0_5 = (u16) M2C_FIELD(temp_s3, s16 *, 0xC8) + 0x10;
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
            var_v0_5 = (u16) M2C_FIELD(temp_s3, s16 *, 0xC8) + temp_v1_2;
        } else {
block_53:
            var_v0_5 = M2C_FIELD(arg0, u16 *, 0x10) + 0x800;
        }
    }
    M2C_FIELD(temp_s3, s16 *, 0xC8) = var_v0_5;
    M2C_FIELD(temp_s3, volatile s16 *, 0xC8) = (s16) ((M2C_FIELD(temp_s3, volatile u16 *, 0xC8) + 0x1000) & 0xFFF);
    ASM_SCHED_BARRIER();
    var_v0_7 = var_s0;
    if (var_s0 < 0) {
        var_v0_7 = 0 - var_v0_7;
    }
    if (var_v0_7 >= 0xA0) {
        if (var_s6 <= (M2C_FIELD(arg1, s16 *, 0xA) + 2)) {
            if (M2C_FIELD(arg0, s32 *, 0x48) > 0xC0000) {
                func_800ABD74(arg1);
            }
        }
    }
    if (D_800CFCEE != 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        func_800954F4(arg1);
    }
    if (M2C_FIELD(arg1, s16 *, 0xA) > var_s6) {
        M2C_FIELD(arg1, s16 *, 0xA) = var_s6;
        if (M2C_FIELD(arg1, s32 *, 0x14) >= 0) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
        }
        if (M2C_FIELD(arg0, s32 *, 0x4C) & 1) {
            func_800ABD74(arg1);
        }
        temp_v1_2 = -2;
        var_v0_9 = M2C_FIELD(arg0, s32 *, 0x4C) & temp_v1_2;
    } else {
        var_v0_9 = M2C_FIELD(arg0, s32 *, 0x4C) | 1;
    }
    M2C_FIELD(arg0, s32 *, 0x4C) = var_v0_9;
    if ((M2C_FIELD(temp_s3, s32 *, 0x10) & 0x10) && (var_s6 == M2C_FIELD(arg1, s16 *, 0xA))) {
        M2C_FIELD(arg1, s32 *, 0x14) = -0x140000;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x20000);
    {
        static void *const keepalive[] = {&&sw0, &&sw1, &&sw2, &&sw3, &&sw4};
        (void) keepalive;
        temp_v1_5 = M2C_FIELD(arg0, s16 *, 8);
        if ((u32) temp_v1_5 < 5) {
            goto *jtbl_80089978[temp_v1_5];
        }
        goto sw_end;
    }
    {
sw0:
        M2C_FIELD(arg0, u16 *, 0x10) = 0xC00U;
        M2C_FIELD(arg1, s32 *, 8) = 0;
        M2C_FIELD(temp_s4, s16 *, 2) = 0;
        M2C_FIELD(temp_s4, s16 *, 0) = 0;
        M2C_FIELD(temp_s3, s16 *, 0xC8) = 0xC00;
        goto block_78;
sw1:
        M2C_FIELD(temp_s3, s16 *, 0xC8) = (s16) (((0x20 - M2C_FIELD(temp_s5, u16 *, 0x2E)) << 5) + 0xC00);
        M2C_FIELD(arg0, u16 *, 0x10) = 0xC00U;
        goto block_78;
sw2:
        M2C_FIELD(temp_s3, s16 *, 0xC8) = (s16) ((0x10 - M2C_FIELD(temp_s5, u16 *, 0x2E)) << 5);
        temp_v1_6 = M2C_FIELD(temp_s4, s16 *, 0);
        if (temp_v1_6 < 4) {
            M2C_FIELD(((temp_v1_6 * 2) + (s8 *) temp_s5), u16 *, 0x30) =
                (u16) (M2C_FIELD(((temp_v1_6 * 2) + (s8 *) temp_s5), u16 *, 0x30) + 1);
        }
block_78:
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        goto sw_end;
sw3:
        temp_s0 = M2C_FIELD(temp_s4, s16 *, 0);
        func_80022F34(arg1, temp_s4);
        func_800239A0(temp_s5, temp_s4, 0);
        if (M2C_FIELD(temp_s4, s16 *, 0) != temp_s0) {
            register s32 *best ASM_REG("$5");

            best = (s32 *)0x800135B4;
            ASM_KEEP(best);
            temp_v1_8 = M2C_FIELD(((temp_s0 * 2) + (s8 *) temp_s5), s16 *, 0x30);
            if (temp_v1_8 < *best) {
                *best = (s32) temp_v1_8;
                M2C_FIELD(temp_s5, s16 *, 0x38) = temp_v1_8;
                func_80033B9C(0x596, best);
            }
        }
        temp_v1_9 = M2C_FIELD(temp_s4, s16 *, 0);
        if (temp_v1_9 < 4) {
            temp_v1_10 = M2C_FIELD(((temp_v1_9 * 2) + (s8 *) temp_s5), u16 *, 0x30);
            M2C_FIELD(((temp_v1_9 * 2) + (s8 *) temp_s5), u16 *, 0x30) = (u16) (temp_v1_10 + 1);
            if ((s16) temp_v1_10 >= 0x7530) {
                M2C_FIELD(((M2C_FIELD(temp_s4, s16 *, 0) * 2) + (s8 *) temp_s5), s16 *, 0x30) = 0x7530;
            }
        }
        goto sw_end;
sw4:
        sp28 = *(Blk20 *) &D_80089960;
        func_8008B550(2);
        func_8003BAF8(&sp28);
        M2C_FIELD(arg0, s16 *, 8) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 8) + 1);
    }
sw_end:
    {
        register s32 tail_v1 ASM_REG("$3");
        tA = (s32) M2C_FIELD(arg0, s16 *, 0x10) - 0x1500;
        tB = M2C_FIELD(temp_s3, s16 *, 0xC8);
        tail_v1 = tB - tA;
        ASM_KEEP_NV(tail_v1);
        temp_s0_2 = (tail_v1 & 0xFFF) >> 9;
        ASM_SCHED_BARRIER();
    }
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) ((M2C_FIELD(arg0, u16 *, 0x10) + 0x2000) & 0xFFF);
    if (M2C_FIELD(arg0, s16 *, 0x12) != temp_s0_2) {
        if (M2C_FIELD(arg2, s32 *, 0x2C) != 0) {
            func_800489F4(arg2, ((u8 *)M2C_FIELD(arg0, void **, 0x1C))[temp_s0_2], M2C_FIELD(arg2, s8 *, 4), 0);
        }
        M2C_FIELD(arg0, s16 *, 0x12) = (s16) temp_s0_2;
    }
    if (((u8 *)&D_8006CCF8)[temp_s0_2] != 0) {
        var_v0_10 = M2C_FIELD(arg2, u16 *, 0x14) | 1;
    } else {
        var_v0_10 = M2C_FIELD(arg2, u16 *, 0x14) & 0xFFFE;
    }
    M2C_FIELD(arg2, u16 *, 0x14) = var_v0_10;
    ASM_SCHED_BARRIER();
    func_80048AC8(arg2, 0);
    func_800A48B0(&D_80100D98, arg1);
    M2C_FIELD(&D_80100D98, s32 *, 8) = 0;
}
