#include "common.h"

extern s32 func_800A3B2C(void);
extern s32 func_800A3B80(void *);

s32 func_800A3B1C(void *arg0) {
    u8 *state = arg0;
    register u8 *carrier2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 carrier1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    result = func_800A3B80(state);
    if ((result << 0x10) != 0) {
        return (s16)result;
    }

    carrier2 = *(u8 **)(state - 8);
    if (carrier2 == 0) {
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        return (s16)result;
    }

    state = carrier2 + 0x20;
    carrier1 = *(s32 *)(carrier2 + 8);
    carrier2 = (u8 *)(u32)*(s32 *)(carrier2 + 0xC);
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(carrier1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(carrier2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return func_800A3B2C();
}

/* MECHANISM: Guarded s0/v1 carriers fix the 24-byte prologue and preserve the first call result.
   A null-edge keep blocks zero substitution, retaining retail's second sll/sra conversion.
   The zero path fills the custom s0/a1/a2 ABI before the zero-argument sibling tail call. */
