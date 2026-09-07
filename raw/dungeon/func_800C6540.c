#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80094E34(void);
extern void func_80099844(void *, void *);
extern void func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800CBB98(u8, u8, s16, void *);
extern u8 D_800E1AE6[];
extern u8 D_800E3D40;

s32 func_800CBCA0(void *arg0)
{
    void *parent;
    s32 result;
    register s32 value ASM_REG("$2");
    register s32 divisor ASM_REG("$3");
    register s32 numerator ASM_REG("$4");

    if (FIELD(arg0, u8, 0x13) == 0) {
        goto check_global;
    }
    if (!(FIELD(arg0, s32, 0x14) & 0x4000)) {
        goto check_global;
    }
    ASM_KEEP(arg0);
    value = 1;
    goto done;

check_global:
    if (D_800E3D40 == 0) {
        numerator = (u16)func_800A6D30();
        divisor = FIELD(arg0, u8, 3);
        if (divisor != 0) {
            value = divisor;
            ASM_KEEP(value);
            divisor = numerator % value;
            value = divisor;
            goto value_ready;
        }
    }
    value = 0;
value_ready:

    if (value < 0x30) {
        parent = FIELD(arg0, void *, -0x14);
        result = func_800CBB98(FIELD(parent, u8, 0x24),
                               FIELD(parent, u8, 0x25),
                               FIELD(arg0, s16, 0x88), arg0);
        if (result != 0) {
            if (FIELD(arg0, u8, 0x13) == 0) {
                func_80094E34();
                func_80099844(arg0, D_800E1AE6);
            }
        }
        return result != 0;
    }

    if (FIELD(arg0, u8, 0x13) == 0) {
        func_800A6508();
    }
    return 1;

done:
    return value;
}

/* MECHANISM: Recover true-space joins and keep the early success block before its local j.
   Hold arg0/result in s0/s1; pin RNG value/divisor/numerator to v0/v1/a0 with explicit copies.
   At 2.8.1-G0 the destructive global lbu closes the final two-word register residue. */
