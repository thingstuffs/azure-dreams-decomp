#include "common.h"

extern s32 func_800A3B2C(void);
extern s32 func_800A3B80(void *);

s32 func_800A3B1C(void *arg0) {
    register u8 *state ASM_REG("$16") = arg0;
    register u8 *carrier2 ASM_REG("$6");
    register s32 carrier1 ASM_REG("$5");
    register s32 result ASM_REG("$3");

    ASM_KEEP(state);
    result = func_800A3B80(state);
    ASM_KEEP(result);
    if ((result << 0x10) != 0) {
        return (s16)result;
    }

    carrier2 = *(u8 **)(state - 8);
    if (carrier2 == 0) {
        ASM_KEEP(result);
        return (s16)result;
    }

    state = carrier2 + 0x20;
    carrier1 = *(s32 *)(carrier2 + 8);
    carrier2 = (u8 *)(u32)*(s32 *)(carrier2 + 0xC);
    ASM_KEEP(state);
    ASM_KEEP(carrier1);
    ASM_KEEP(carrier2);
    return func_800A3B2C();
}

/* MECHANISM: Guarded s0/v1 carriers fix the 24-byte prologue and preserve the first call result.
   A null-edge keep blocks zero substitution, retaining retail's second sll/sra conversion.
   The zero path fills the custom s0/a1/a2 ABI before the zero-argument sibling tail call. */
