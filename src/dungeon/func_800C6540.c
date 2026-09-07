#include "common.h"

typedef struct S_800CBCA0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CBCA0_0_pre;   /* the 0x14 bytes before arg0 in func_800CBCA0, addressed as arg0[-1] */

typedef struct S_800CBCA0_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x70];
    s16 unk_88;
} S_800CBCA0_0;   /* arg0 in func_800CBCA0 */

typedef struct S_800CBCA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CBCA0_1;   /* parent in func_800CBCA0 */



extern void func_80094E34(void);
extern void func_80099844(void *, void *);
extern void func_800A6508(void);
extern s32 func_800A6D30(void);
extern s32 func_800CBB98(u8, u8, s16, void *);
extern u8 D_800E1AE6[];
extern u8 D_800E3D40;

s32 func_800CBCA0(void *arg0)
{
    S_800CBCA0_1 *parent;
    s32 result;
    s32 value;
    register s32 divisor ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 numerator;

    if (((S_800CBCA0_0 *)arg0)->unk_13 == 0) {
        goto check_global;
    }
    if (!(((S_800CBCA0_0 *)arg0)->unk_14 & 0x4000)) {
        goto check_global;
    }
    ASM_KEEP(arg0);   /* MATCH pin: retail branch polarity depends on it */
    value = 1;
    goto done;

check_global:
    if (D_800E3D40 == 0) {
        numerator = (u16)func_800A6D30();
        divisor = ((S_800CBCA0_0 *)arg0)->unk_03;
        if (divisor != 0) {
            value = divisor;
            ASM_KEEP(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            divisor = numerator % value;
            value = divisor;
            goto value_ready;
        }
    }
    value = 0;
value_ready:

    if (value < 0x30) {
        parent = ((S_800CBCA0_0_pre *)arg0)[-1].unk_00;
        result = func_800CBB98(parent->unk_24,
                               parent->unk_25,
                               ((S_800CBCA0_0 *)arg0)->unk_88, arg0);
        if (result != 0) {
            if (((S_800CBCA0_0 *)arg0)->unk_13 == 0) {
                func_80094E34();
                func_80099844(arg0, D_800E1AE6);
            }
        }
        return result != 0;
    }

    if (((S_800CBCA0_0 *)arg0)->unk_13 == 0) {
        func_800A6508();
    }
    return 1;

done:
    return value;
}

/* MECHANISM: Recover true-space joins and keep the early success block before its local j.
   Hold arg0/result in s0/s1; pin RNG value/divisor/numerator to v0/v1/a0 with explicit copies.
   At 2.8.1-G0 the destructive global lbu closes the final two-word register residue. */
