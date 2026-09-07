#include "common.h"

typedef struct S_80095840_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x1A];
    union { void * s; s32 u; } unk_2C;   /* accessed as both */
} S_80095840_0;   /* out in func_80095840 */

typedef struct S_80095840_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x1A];
    u8 unk_3A;
} S_80095840_1;   /* in in func_80095840 */

typedef struct S_80095840_2 {
    u8 pad_00[0x14];
    u8 unk_14;
    u8 pad_15[0x7];
    s32 unk_1C;
    u8 pad_20[0x1A];
    u8 unk_3A;
} S_80095840_2;   /* (void *)work in func_80095840 */

typedef struct S_80095840_3 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80095840_3;   /* entry in func_80095840 */



extern s32 D_800D0484[8];
extern void func_80095908(void) __attribute__((noreturn));

s32 func_80095840(void *arg0, void *arg1)
{
    S_80095840_0 *out;
    void *in;
    register s32 work ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 value;
    u8 kind;

    out = arg0;
    in = arg1;
    value = out->unk_10;
    work = value + 0x100;
    if (work >= 0) {
        work >>= 7;
    } else {
        work = (value + 0x2FF) >> 7;
    }

    value = (s32)D_800D0484;
    work &= 0x1C;
    work += value;
    value = *(s32 *)work;
    if (value == -1) {
        goto none;
    }

    work = ((S_80095840_1 *)in)->unk_3A;
    if (work != 0) {
        register void *entry ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

        work = ((S_80095840_1 *)in)->unk_1C;
        ((S_80095840_1 *)in)->unk_18 = 0;
        ((S_80095840_1 *)in)->unk_10 = work;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        entry = (void *)work;
        ASM_KEEP(entry);   /* MATCH pin: retail register colouring depends on it */
        kind = ((S_80095840_2 *)((void *)work))->unk_14;
        if ((kind == 1) || (kind == 3)) {
            goto none;
        }
        work = 2;
        ASM_KEEP(work);   /* MATCH pin: retail delay-slot contents depend on it */
        out->unk_2C.s = entry;
        func_80095908();
    }

    work = (s32)in + value;
    if (((S_80095840_2 *)((void *)work))->unk_3A != 0) {
        register void *entry ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */

        work = value * 4;
        work += (s32)in;
        work = ((S_80095840_2 *)((void *)work))->unk_1C;
        ((S_80095840_1 *)in)->unk_18 = value;
        ((S_80095840_1 *)in)->unk_10 = work;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        entry = (void *)work;
        kind = ((S_80095840_3 *)entry)->unk_14;
        if ((kind != 1) && (kind != 3)) {
            work = 1;
            ASM_KEEP(work);   /* MATCH pin: retail delay-slot contents depend on it */
            out->unk_2C.s = entry;
            func_80095908();
        }
    }

none:
    out->unk_2C.u = 0;
    return 0;
}

/* MECHANISM: Frameless leaf; v0 carries quotient/address/entry/selector and block-local a2 copies.
   The shared v1 value and v0 work lifetimes preserve the unscaled masked table-access sequence.
   Zero-word barriers keep both field stores ahead of their a2 copies; CFG shares the zero return. */
