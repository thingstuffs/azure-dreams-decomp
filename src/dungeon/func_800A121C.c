/* rowbase_unblock_20260814b: reissue of func_800A121C.func_800A697C.c under a fresh
   candidate identity — the 20260814b synth for the original bytes completed exact but
   its frozen compile geometry predates the worktree build/toolchain materialization,
   so its gate can never bind; the exhausted identity is retired, not reused. */
#include "common.h"

extern s32 func_800A6928(s32, s32);

s16 func_800A697C(s32 arg0, s32 arg1) {
    s32 val = arg0 << 8;
    s32 count;
    s32 key;
    u16 *entry;

    val |= arg1 & 0xFF;
    count = 0x3F;
    key = val & 0xFFFF;
    entry = (u16 *)0x8001207C;

    while (1) {
        if (*entry == key)
            return 1;
        if (--count < 0)
            break;
        entry -= 2;
    }
    return func_800A6928(arg0 & 0xFF, arg1 & 0xFF);
}
