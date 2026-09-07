#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80024204();
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern u8 D_80024048[9];
extern u8 D_80045340[9];
extern u8 D_800DE8E8[9];

s32 func_80024130(s32 arg0, void *arg1)
{
    s32 temp_v1;
    s32 var_v0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1_2;
    register s32 temp_a0 ASM_REG("$4");
    register void *temp_ret ASM_REG("$2");

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        FIELD(temp_v0, void *, 0x10) = D_80024048;
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_v0, s32, 0x2C) = arg0;
        FIELD(temp_s0, u8, 0xE) = 0x80;
        FIELD(temp_s0, u8, 0xD) = 0x80;
        FIELD(temp_s0, u8, 0xC) = 0x80;
        func_8003DB94(temp_s0, D_800DE8E8, 0);
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        FIELD(temp_s0, s16, 0x1A) = temp_v1 - ((var_v0 >> 0xC) << 0xC);
        func_8004491C(temp_v0, D_80045340);
        temp_v1_2 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v1_2, u16, 2) = FIELD(arg1, u16, 2);
        FIELD(temp_v1_2, u16, 6) = FIELD(arg1, u16, 6);
        temp_a0 = FIELD(arg1, u16, 0xA);
        ASM_KEEP(temp_a0);
        temp_ret = temp_v0;
        ASM_KEEP(temp_ret);
        FIELD(temp_v1_2, u16, 0xA) = temp_a0;
        return func_80024204(temp_a0);
    }
    return 0;
}

/* MECHANISM: The 0x28 frame follows from holding arg0/arg1 and the two object bases in s3/s2/s1/s0.
   Guarded a0 and v0 carriers retain the final halfword copy and object result across the dispatcher.
   LEAD 22 then emits j with the sh delay slot; u8 color fields preserve the +0x80 materialization. */
