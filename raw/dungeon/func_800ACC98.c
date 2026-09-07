#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

typedef s32 M2C_UNK;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800B22F0(void *, void *, void *, s16);
extern u8 D_80045340;
extern s32 D_80083498;
extern M2C_UNK D_800B274C;
extern M2C_UNK D_800B2A60;

void *func_800B23F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                    volatile s32 arg4)
{
    register s32 saved_arg0 ASM_REG("$20");
    register s32 saved_arg1 ASM_REG("$21");
    register long reg_s2 ASM_REG("$18");
    register long reg_s3 ASM_REG("$19");
    register s32 call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 kind ASM_REG("$4");
    register s32 test_v0 ASM_REG("$2");
    s32 left;
    s32 right;
    void *part_a;
    void *obj;
    register void *work ASM_REG("$17");
    register s16 call_arg3 ASM_REG("$22");

    saved_arg0 = arg0;
    work = 0;
    call_a0 = 0x112;
    saved_arg1 = arg1;
    call_a1 = &D_80083498;
    reg_s2 = arg3;
    reg_s3 = arg2;
    ASM_KEEP_NV(call_a0);
    ASM_KEEP_NV(call_a1);
    obj = func_8003FD64(call_a0, call_a1);
    if (obj != 0) {
        call_arg3 = saved_arg0;
        work = (u8 *)obj + 0x20;
        ASM_KEEP(call_arg3);
        ASM_KEEP(work);
        FIELD(obj, M2C_UNK *, 0x10) = &D_800B274C;
        FIELD(work, s8, 0x13) = 0x1E;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        kind = saved_arg0 & 3;
        FIELD(part_a, s16, 0xA) = (s16)reg_s2;
        ASM_KEEP(kind);
        reg_s2 = (long)FIELD(obj, void *, 0xC);
        test_v0 = 1;
        FIELD((void *)reg_s2, s8, 0x25) = (s8)reg_s3;
        reg_s3 = (long)work;
        ASM_KEEP(saved_arg0);
        ASM_KEEP(saved_arg1);
        FIELD((void *)reg_s2, s8, 0x24) = saved_arg1;

        if (kind == test_v0) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto write_kind;
        }
        test_v0 = kind < 2;
        if (test_v0) {
            goto post_kind;
        }
        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;
write_kind:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;

post_kind:
        func_800B22F0(obj, part_a, (void *)reg_s2, call_arg3);
        FIELD((void *)reg_s3, u8, 0x9A) = 0xFF;
        FIELD((void *)reg_s3, s8, 0x9C) = -1;
        FIELD((void *)reg_s3, M2C_UNK *, 0x8C) = &D_800B2A60;
        FIELD((void *)reg_s2, s32, 8) = arg4;
        ASM_KEEP(reg_s2);
        ASM_KEEP(reg_s3);
    }
    ASM_KEEP(work);
    return work;
}

/* MECHANISM: Guarded a0/a1 entry locals order retail's s4/s1/s5/s2/s3 saves;
   carrier pins split s2 arg3-to-part_b and s3 arg2-to-actor lifetimes.
   The u8 0xFF then s8 -1 stores preserve retail's distinct constant loads. */
