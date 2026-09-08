#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800CBCA0_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CBCA0_0_pre;   /* the 0x14 bytes before arg0 in func_800CBCA0, addressed as arg0[-1] */


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
    register s32 divisor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 numerator;

    if (((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v == 0) {
        goto check_global;
    }
    if (!(((Rec_D_800E3D7C *)arg0)->unk_14.as_s32 & 0x4000)) {
        goto check_global;
    }
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    value = 1;
    goto done;

check_global:
    if (D_800E3D40 == 0) {
        numerator = (u16)func_800A6D30();
        divisor = ((Rec_D_800E3D7C *)arg0)->unk_00.at03_u8.v;
        if (divisor != 0) {
            value = divisor;
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
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
                               ((Rec_D_800E3D7C *)arg0)->unk_88.as_s16, arg0);
        if (result != 0) {
            if (((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v == 0) {
                func_80094E34();
                func_80099844(arg0, D_800E1AE6);
            }
        }
        return result != 0;
    }

    if (((Rec_D_800E3D7C *)arg0)->unk_10.at03_u8.v == 0) {
        func_800A6508();
    }
    return 1;

done:
    return value;
}

/* MECHANISM: Recover true-space joins and keep the early success block before its local j.
   Hold arg0/result in s0/s1; pin RNG value/divisor/numerator to v0/v1/a0 with explicit copies.
   At 2.8.1-G0 the destructive global lbu closes the final two-word register residue. */
