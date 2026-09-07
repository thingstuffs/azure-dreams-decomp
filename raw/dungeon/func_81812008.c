#include "common.h"

extern s32 func_80026EC0();
extern s32 func_80026F04();
extern s32 func_8004B404();
extern void strncpy();

typedef struct {
    u8 bytes[0x13];
} Entry19;

s32 func_80027008(s32 arg0, s32 arg1, s32 arg2) {
    register s32 held_arg0 ASM_REG("$22") = arg0;
    register s32 temp_a1 ASM_REG("$5");
    s32 temp_v0;
    s32 var_s0;
    s32 var_s1;
    register s32 var_s2 ASM_REG("$18");
    s32 var_s3;
    Entry19 *base;

    var_s0 = arg1;
    var_s0 /= 72;
    var_s3 = arg2;
    temp_v0 = func_8004B404(0x91);
    if (temp_v0 == 0) {
        goto end;
    }
    ASM_KEEP(temp_v0);
    temp_a1 = var_s0 * 8;
    ASM_KEEP(temp_a1);
    var_s3 -= temp_a1;
    if (var_s3 >= 9) {
        var_s3 = 8;
    }
    ASM_KEEP(held_arg0);
    var_s0 = func_80026EC0(held_arg0, temp_a1);
    var_s1 = 0;
    if (var_s3 > 0) {
        base = (Entry19 *)0x800157C0;
        var_s2 = temp_v0;
        ASM_KEEP(var_s2);
        do {
            strncpy(var_s2,
                          (u8 *)((u32)(var_s0 * 0x13) + (u32)base), 0x12);
            var_s0 = func_80026F04(held_arg0, var_s0 + 1);
            var_s1 += 1;
            var_s2 += 0x12;
        } while (var_s1 < var_s3);
    }
end:
    return temp_v0;
}

/* MECHANISM: The in-place /72 quotient forces the retail 0x30 frame and s0/s3/s6 argument holds.
   Exact callee arity plus guarded a1/s2 runtime roles reproduce the return-slot and loop coloring.
   Integer index-first addition preserves the retail addu a1,a1,s5 operand order. */
