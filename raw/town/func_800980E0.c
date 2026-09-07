#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern s32 D_800D0484[8];
extern void func_80095908(void) __attribute__((noreturn));

s32 func_80095840(void *arg0, void *arg1)
{
    register void *out ASM_REG("$4");
    register void *in ASM_REG("$5");
    register s32 work ASM_REG("$2");
    register s32 value ASM_REG("$3");
    u8 kind;

    out = arg0;
    in = arg1;
    value = FIELD(out, s16, 0x10);
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

    work = FIELD(in, u8, 0x3A);
    if (work != 0) {
        register void *entry ASM_REG("$6");

        work = FIELD(in, s32, 0x1C);
        FIELD(in, s32, 0x18) = 0;
        FIELD(in, s32, 0x10) = work;
        ASM_SCHED_BARRIER();
        entry = (void *)work;
        ASM_KEEP(entry);
        kind = FIELD((void *)work, u8, 0x14);
        if ((kind == 1) || (kind == 3)) {
            goto none;
        }
        work = 2;
        ASM_KEEP(work);
        FIELD(out, void *, 0x2C) = entry;
        func_80095908();
    }

    work = (s32)in + value;
    if (FIELD((void *)work, u8, 0x3A) != 0) {
        register void *entry ASM_REG("$6");

        work = value * 4;
        work += (s32)in;
        work = FIELD((void *)work, s32, 0x1C);
        FIELD(in, s32, 0x18) = value;
        FIELD(in, s32, 0x10) = work;
        ASM_SCHED_BARRIER();
        entry = (void *)work;
        ASM_KEEP(entry);
        kind = FIELD(entry, u8, 0x14);
        if ((kind != 1) && (kind != 3)) {
            work = 1;
            ASM_KEEP(work);
            FIELD(out, void *, 0x2C) = entry;
            func_80095908();
        }
    }

none:
    FIELD(out, s32, 0x2C) = 0;
    return 0;
}

/* MECHANISM: Frameless leaf; v0 carries quotient/address/entry/selector and block-local a2 copies.
   The shared v1 value and v0 work lifetimes preserve the unscaled masked table-access sequence.
   Zero-word barriers keep both field stores ahead of their a2 copies; CFG shares the zero return. */
