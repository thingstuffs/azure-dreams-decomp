#include "common.h"
#include "m2c_compat.h"

s32 func_800C1C68();                  /* extern */
s32 func_800C1DC8();                                /* extern */
extern M2C_UNK D_8006ADBC;
extern M2C_UNK D_800D4640;
extern M2C_UNK D_800D4658;
extern M2C_UNK D_800D4660;

s32 func_800C1D44(s32 arg0) {
    s8 *base;
    s32 result;

    base = (s8 *)&D_8006ADBC;
    arg0 &= 0x3FFF;
    if (*(s16 *)(base + 0x18) != 0xC) {
        func_800C1C68(arg0, &D_800D4640);
        return func_800C1DC8();
    }
    if (*(s16 *)(base + 0x1A) == 0xD) {
        if (func_800C1C68(arg0, &D_800D4658) == 0) {
            goto return_zero;
        }
        {
            register s32 dead_value ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            dead_value = 6;
            ASM_KEEP(dead_value);   /* MATCH pin: load-bearing for the whole function shape */
        }
        return func_800C1DC8();
    }
    if (*(s16 *)(base + 0x1A) == 0x2A) {
        if (func_800C1C68(arg0, &D_800D4660) != 0) {
            return 7;
        }
    }
return_zero:
    result = 0;
    return result;
}

/* MECHANISM: A held D_8006ADBC byte base and in-place arg mask preserve the
   0x18-byte ra-only frame and retail register lifetimes. A scoped guarded $v0
   dead-value keep places li v0,6 in the beqz delay slot before the tail call. */
