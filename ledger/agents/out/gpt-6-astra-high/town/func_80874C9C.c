#include "common.h"

extern s32 func_807018AC(s16 value);
extern u8 D_80700000[];
extern s16 D_80700BAC[];
extern u8 D_80700BB4[];

/* Returns whether the indexed secondary check passes while both primary checks fail. */
s32 func_80874C9C(s32 value_index) {
    volatile s32 frame_pad;
    register s16 *primary_values ASM_REG("$16");   /* MATCH pin: retail immediate-load split depends on it */
    s32 byte_offset;
    s32 passes;

    primary_values = D_80700BAC;
    byte_offset = value_index * 2;
    passes = 0;
    if (func_807018AC(*(s16 *)(D_80700000 + byte_offset + 0xBAC)) == 0) {
        passes = 0;
        if (func_807018AC(primary_values[0]) == 0) {
            passes = func_807018AC(*(s16 *)(D_80700BB4 + byte_offset)) != 0;
        }
    }
    return passes;
}
