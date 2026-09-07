#include "common.h"

extern s32 func_8004A658();
extern s32 func_8004AC3C();
extern s32 func_800B5264();
extern s32 func_800B53BC();
extern s32 func_800B5918();

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_800B61C0(void *arg0, s32 arg1, s32 arg2)
{
    s32 sp18[4];
    s32 sp28[2];
    register s32 temp_s2 ASM_REG("$18");
    s32 temp_s3;
    register s32 temp_v0 ASM_REG("$5");
    s32 *temp_a1;
    void *temp_s0;

    temp_a1 = sp28;
    ASM_KEEP_NV(temp_a1);
    temp_v0 = func_8004AC3C(arg0, temp_a1);
    ASM_KEEP(temp_v0);
    do { temp_s2 = arg2 * 0x10; } while (0);
    temp_s3 = temp_s2 + 0xD8;
    temp_s0 = (void *)(arg2 * 4 + arg1);
    func_800B5264(FIELD(temp_s0, s32, 0x20), temp_v0, sp28[0], 0x58, temp_s3);
    func_800B53BC(FIELD(temp_s0, s32, 0x2C),
                  func_800B5918(arg0, sp18), 0, 0xA0, temp_s3);
    FIELD(FIELD(temp_s0, void *, 0x38), s32, 0) = func_8004A658(
        FIELD(arg0, u8, 1), FIELD(arg0, u8, 0));
    FIELD(FIELD(FIELD(temp_s0, void *, 0x38), void *, 4), s16, 8) = -0x30;
    FIELD(FIELD(FIELD(temp_s0, void *, 0x38), void *, 4), s16, 0xA) =
        (s16)(temp_s2 + 0x66);
    ASM_KEEP_NV(temp_s2);
}

/* MECHANISM: Sibling sp18/sp28 arrays produce the retail 0x48 frame; keeping the
   sp28 pointer live hoists sp+0x28 and lets the $s2 save fill the first jal slot.
   Guarded $s2/$a1 value pins restore the scaled-index role and immediate return copy. */
