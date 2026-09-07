#include "common.h"

extern s32 func_807018AC(s16 value);
extern u8 D_80700000[];
extern s16 D_80700BAC[];
extern u8 D_80700BB4[];

s32 func_80874C9C(s32 arg0) {
    volatile s32 frame_pad;
    register s16 *base ASM_REG("$16");
    s32 offset;
    s32 result;

    base = D_80700BAC;
    offset = arg0 * 2;
    result = 0;
    if (func_807018AC(*(s16 *)(D_80700000 + offset + 0xBAC)) == 0) {
        result = 0;
        if (func_807018AC(base[0]) == 0) {
            result = func_807018AC(*(s16 *)(D_80700BB4 + offset)) != 0;
        }
    }
    return result;
}
